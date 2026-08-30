#!/usr/bin/env python3

from __future__ import annotations

import argparse
import re
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
TEMPLATE = ROOT / "template.cc"
CODEFORCES = ROOT / "codeforces"

HEADER_END_RE = re.compile(r"(?m)^//\s*\}\}\}\s*$")
HEADER_OPEN_RE = re.compile(r"(?m)^//\s*\{\{\{\s*$")

TYPE_REPLACEMENTS = {
    "i16": "std::int16_t",
    "ll": "i64",
    "ld": "f128",
    "d64": "f64",
    "d128": "f128",
    "u4": "u32",
    "u16": "std::uint16_t",
}

ALIAS_REPLACEMENTS = {
    "v": "vec",
    "ve": "vec",
    "ar": "arr",
    "r": "arr",
    "pa": "std::pair",
    "pai": "std::pair",
    "p": "std::pair",
    "tu": "std::tuple",
    "dq": "std::deque",
    "qu": "std::queue",
    "st": "std::stack",
}

TOKEN_REPLACEMENTS = {
    "ff": "first",
    "ss": "second",
    "eb": "emplace_back",
    "pb": "push_back",
}

DISCARDED_MACROS = {
    "all",
    "rall",
    "db",
    "dbln",
    "dbg",
    "dbgln",
    "endl",
    "ff",
    "ld",
    "ll",
    "pb",
    "pr",
    "prln",
    "ss",
    "sz",
    "vec",
}

DEBUG_CALLS = {"db", "dbln", "dbg", "dbgln"}

COMMON_DECLARATIONS = {
    "MAX",
    "MIN",
    "NO",
    "No",
    "YES",
    "Yes",
    "all",
    "db",
    "dbln",
    "dbg",
    "dbgln",
    "max",
    "min",
    "no",
    "pr",
    "prln",
    "print",
    "println",
    "rall",
    "sc",
    "sz",
    "yes",
}

TYPE_WORDS = {
    "auto",
    "bool",
    "char",
    "const",
    "constexpr",
    "double",
    "float",
    "int",
    "long",
    "short",
    "signed",
    "size_t",
    "static",
    "std",
    "string",
    "struct",
    "template",
    "typename",
    "u32",
    "u64",
    "unsigned",
    "vector",
    "void",
}


@dataclass(frozen=True)
class Function:
    start: int
    body_start: int
    end: int


@dataclass
class Stats:
    sources: int = 0
    solve_sources: int = 0
    main_only_sources: int = 0
    marked_headers: int = 0
    inferred_headers: int = 0
    canonical_multi_mains: int = 0
    canonical_single_mains: int = 0
    preserved_mains: int = 0
    changed: int = 0


def mask_non_code(source: str) -> str:
    masked = list(source)
    state = "code"
    i = 0
    while i < len(source):
        if state == "code":
            if source.startswith("//", i):
                masked[i] = masked[i + 1] = " "
                i += 2
                state = "line_comment"
            elif source.startswith("/*", i):
                masked[i] = masked[i + 1] = " "
                i += 2
                state = "block_comment"
            elif source[i] == '"':
                masked[i] = " "
                i += 1
                state = "string"
            elif (
                source[i] == "'"
                and not (
                    i > 0
                    and i + 1 < len(source)
                    and source[i - 1].isdigit()
                    and source[i + 1].isdigit()
                )
            ):
                masked[i] = " "
                i += 1
                state = "character"
            else:
                i += 1
        elif state == "line_comment":
            if source[i] == "\n":
                state = "code"
            else:
                masked[i] = " "
            i += 1
        elif state == "block_comment":
            if source.startswith("*/", i):
                masked[i] = masked[i + 1] = " "
                i += 2
                state = "code"
            else:
                if source[i] != "\n":
                    masked[i] = " "
                i += 1
        else:
            quote = '"' if state == "string" else "'"
            if source[i] == "\\":
                masked[i] = " "
                i += 1
                if i < len(source) and source[i] != "\n":
                    masked[i] = " "
                i += 1
            elif source[i] == quote:
                masked[i] = " "
                i += 1
                state = "code"
            else:
                if source[i] != "\n":
                    masked[i] = " "
                i += 1
    return "".join(masked)


def find_function(source: str, name: str) -> Function | None:
    masked = mask_non_code(source)
    if name == "main":
        pattern = re.compile(r"\b(?:int|signed|int32_t)\s+main\s*\([^)]*\)\s*\{")
    else:
        pattern = re.compile(rf"\bvoid\s+{re.escape(name)}\s*\([^)]*\)\s*\{{")
    match = pattern.search(masked)
    if match is None:
        return None

    body_start = masked.find("{", match.start())
    depth = 0
    for i in range(body_start, len(masked)):
        if masked[i] == "{":
            depth += 1
        elif masked[i] == "}":
            depth -= 1
            if depth == 0:
                return Function(match.start(), body_start, i + 1)
    raise ValueError(f"unbalanced {name}()")


def canonical_header() -> str:
    source = TEMPLATE.read_text()
    solve = find_function(source, "solve")
    if solve is None:
        raise ValueError("template.cc has no solve()")
    marker = HEADER_END_RE.search(source, 0, solve.start)
    if marker is None:
        raise ValueError("template.cc has no header fold")
    return source[: marker.end()].rstrip() + "\n"


def macro_definitions(prefix: str) -> dict[str, str]:
    definitions: dict[str, str] = {}
    lines = prefix.splitlines()
    i = 0
    while i < len(lines):
        match = re.match(r"\s*#define\s+([A-Za-z_]\w*)\b", lines[i])
        if match is None:
            i += 1
            continue
        definition = [lines[i]]
        while definition[-1].endswith("\\") and i + 1 < len(lines):
            i += 1
            definition.append(lines[i])
        definitions[match.group(1)] = "\n".join(definition)
        i += 1
    return definitions


def has_alias(prefix: str, name: str) -> bool:
    return bool(
        re.search(rf"(?m)^\s*(?:template\s*<[^\n]+>\s*)?using\s+{name}\s*=", prefix)
        or re.search(rf"(?m)^\s*#define\s+{name}\b", prefix)
    )


def replace_function_calls(source: str, names: set[str], replacement: str) -> str:
    masked = mask_non_code(source)
    spans: list[tuple[int, int]] = []
    pattern = re.compile(rf"\b(?:{'|'.join(sorted(names, key=len, reverse=True))})\s*\(")
    for match in pattern.finditer(masked):
        opening = masked.find("(", match.start())
        depth = 0
        for i in range(opening, len(masked)):
            if masked[i] == "(":
                depth += 1
            elif masked[i] == ")":
                depth -= 1
                if depth == 0:
                    spans.append((match.start(), i + 1))
                    break
    for start, end in reversed(spans):
        source = source[:start] + replacement + source[end:]
    return source


def replace_output_calls(source: str, name: str, replacement: str) -> str:
    masked = mask_non_code(source)
    spans: list[tuple[int, int, str]] = []
    pattern = re.compile(rf"\b{re.escape(name)}\s*\(")
    for match in pattern.finditer(masked):
        if re.search(r"\b(?:auto|void)\s*$", masked[max(0, match.start() - 32) : match.start()]):
            continue
        opening = masked.find("(", match.start())
        depth = 0
        for i in range(opening, len(masked)):
            if masked[i] == "(":
                depth += 1
            elif masked[i] == ")":
                depth -= 1
                if depth == 0:
                    arguments = source[opening + 1 : i].strip()
                    if not arguments or arguments.startswith(('"', "R\"")):
                        call = f"{replacement}({arguments})"
                    else:
                        call = f'{replacement}("{{}}", {arguments})'
                    spans.append((match.start(), i + 1, call))
                    break
    for start, end, call in reversed(spans):
        source = source[:start] + call + source[end:]
    return source


def migrate_tokens(source: str, prefix: str) -> str:
    if has_alias(prefix, "ll"):
        source = re.sub(r"\bunsigned\s+ll\b", "u64", source)

    for old, new in TYPE_REPLACEMENTS.items():
        if has_alias(prefix, old):
            source = re.sub(rf"\b{old}\b", new, source)

    for old, new in ALIAS_REPLACEMENTS.items():
        if has_alias(prefix, old):
            source = re.sub(rf"\b{old}\s*(?=<)", new, source)

    if re.search(
        r"template\s*<\s*typename\.\.\.\s*Ts\s*>\s*using\s+pq\s*=\s*std::priority_queue<Ts\.\.\.>",
        prefix,
    ):
        source = re.sub(r"\bpq\s*(?=<)", "std::priority_queue", source)

    for old, new in TOKEN_REPLACEMENTS.items():
        if old in macro_definitions(prefix):
            source = re.sub(rf"\b{old}\b", new, source)

    if "endl" in macro_definitions(prefix):
        source = re.sub(r"\bendl\b", lambda _: "'\\n'", source)

    for name in ("MIN", "MAX"):
        if re.search(rf"\b{name}\s*\(\s*\)", prefix):
            source = re.sub(rf"\b{name}\s*(<[^;()]+>)\s*\(\s*\)", rf"{name}\1", source)

    source = source.replace("#if USE_AES", "#if defined(USE_AES) && USE_AES")

    definitions = macro_definitions(prefix)
    if DEBUG_CALLS & definitions.keys():
        source = replace_function_calls(source, DEBUG_CALLS, "((void)0)")
    else:
        source = replace_output_calls(source, "dbgln", "prln")
        source = replace_output_calls(source, "dbg", "pr")
    return source


def normalize_output_calls(source: str) -> str:
    for name in ("pr", "prln", "print", "println"):
        source = replace_output_calls(source, name, name)
    return source


def remove_answer_wrappers(source: str) -> str:
    for name in ("YES", "Yes", "yes", "NO", "No", "no"):
        source = re.sub(
            rf"(?ms)^\s*(?:inline\s+)?(?:static\s+)?void\s+{name}\s*\(\s*\)\s*\{{\s*"
            rf"(?:prln|println)\s*\(\s*\"{name}\"\s*\)\s*;\s*\}}\s*",
            "",
            source,
        )
    return source


def avoid_answer_name_collisions(source: str) -> str:
    for name in ("YES", "Yes", "yes", "NO", "No", "no"):
        declaration = re.search(
            rf"(?m)^\s*(?!void\b)(?:const\s+)?(?:auto|string|std::string)\s+{name}\b",
            source,
        )
        if declaration is not None:
            source = re.sub(rf"\b{name}\b", f"{name}_value", source)
    return source


def compatibility_prelude(source: str, prefix: str) -> str:
    definitions = macro_definitions(prefix)
    pieces: list[str] = []

    def defines(name: str) -> bool:
        return bool(re.search(rf"(?m)^\s*#define\s+{re.escape(name)}\b", source))

    if re.search(r"\bsc\s*<", source) and not re.search(
        r"\bconstexpr\s+T\s+sc\s*\(", source
    ):
        pieces.append(
            "template <typename T, typename U>\n"
            "[[nodiscard]] constexpr T sc(U&& value) {\n"
            "  return static_cast<T>(std::forward<U>(value));\n"
            "}"
        )

    if re.search(r"\bsz\s*(?:<[^>]+>)?\s*\(", source) and not re.search(
        r"\bconstexpr\s+T\s+sz\s*\(", source
    ):
        pieces.append(
            "template <typename T = i32, typename U>\n"
            "[[nodiscard]] constexpr T sz(const U& value) {\n"
            "  return static_cast<T>(std::size(value));\n"
            "}"
        )

    if "all" in definitions and not defines("all") and re.search(r"\ball\s*\(", source):
        pieces.append("#define all(x) (x).begin(), (x).end()")
    if "rall" in definitions and not defines("rall") and re.search(r"\brall\s*\(", source):
        pieces.append("#define rall(x) (x).rbegin(), (x).rend()")

    for name, definition in sorted(definitions.items()):
        if name in DISCARDED_MACROS:
            continue
        if not defines(name) and re.search(rf"\b{name}\b", source):
            pieces.append(migrate_tokens(definition, prefix))

    return "\n\n".join(dict.fromkeys(pieces))


def extract_pbds(prefix: str, body: str) -> str:
    if "<ext/pb_ds/" not in prefix:
        return ""
    if not re.search(
        r"\b(?:gp_hash_table|hashmap|hashset|hashtable|multitree|rbtree|tree(?:map|set|multimap|multiset)?)\s*<",
        body,
    ):
        return ""

    start = prefix.find("#include <ext/pb_ds/")
    end_candidates = [
        position
        for token in ("#define ff", "#define all", "template <typename... Args>")
        if (position := prefix.find(token, start)) != -1
    ]
    end = min(end_candidates, default=len(prefix))
    block = prefix[start:end]
    block = re.sub(r"(?m)^#pragma GCC (?:optimize|target).*\n", "", block)
    block = re.sub(r"(?m)^using namespace std;\n", "", block)
    block = block.replace("#if USE_AES", "#if defined(USE_AES) && USE_AES")
    return block.strip()


def custom_prefix(prefix: str, body: str) -> str:
    masked_prefix = mask_non_code(prefix)
    masked_body = mask_non_code(body)
    depth = 0
    offset = 0
    lines = prefix.splitlines(keepends=True)
    masked_lines = masked_prefix.splitlines(keepends=True)
    declarations: list[tuple[int, list[str]]] = []

    for index, (line, masked_line) in enumerate(zip(lines, masked_lines, strict=True)):
        stripped = masked_line.strip()
        if (
            depth == 0
            and stripped
            and not stripped.startswith(("#", "using "))
            and not (
                stripped.startswith("template ")
                and not re.search(r"\b(?:class|struct)\s+[A-Za-z_]\w*", stripped)
            )
        ):
            declared: list[str] = []
            type_match = re.search(r"\b(?:class|enum|struct)\s+([A-Za-z_]\w*)", stripped)
            function_match = re.search(
                r"\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*(?:\{|$)", stripped
            )
            if type_match is not None:
                declared.append(type_match.group(1))
            elif function_match is not None:
                declared.append(function_match.group(1))
            elif stripped.endswith(";"):
                declared.extend(
                    re.findall(r"\b([A-Za-z_]\w*)\s*(?=\[|=|,|;)", stripped)
                )
            declared = [
                name
                for name in declared
                if name not in TYPE_WORDS and name not in COMMON_DECLARATIONS
            ]
            looks_declarative = bool(
                re.search(r"\b(?:class|enum|struct)\s+[A-Za-z_]\w*", stripped)
                or re.search(r"\b[A-Za-z_]\w*\s*\([^;]*\)\s*(?:\{|$)", stripped)
                or stripped.endswith(";")
            )
            if declared and looks_declarative:
                start = offset
                previous = index - 1
                while previous >= 0 and not lines[previous].strip():
                    previous -= 1
                if previous >= 0 and lines[previous].lstrip().startswith("template <"):
                    start = sum(len(item) for item in lines[:previous])
                declarations.append((start, declared))

        depth += masked_line.count("{") - masked_line.count("}")
        offset += len(line)

    if not declarations:
        return ""

    start = len(prefix)
    references = masked_body
    while True:
        selected = [
            offset
            for offset, names in declarations
            if any(re.search(rf"\b{re.escape(name)}\b", references) for name in names)
        ]
        if not selected:
            break
        next_start = min(selected)
        if next_start >= start:
            break
        start = next_start
        references = masked_body + "\n" + masked_prefix[start:]

    return "" if start == len(prefix) else prefix[start:].strip()


def normalize_main_body(body: str) -> str:
    body = mask_non_code(body)
    body = re.sub(r"(?ms)^\s*#ifdef LOCAL\b.*?^\s*#endif\s*", " ", body)
    setup = [
        r"(?:std::)?cin\.tie\s*\([^;]+;",
        r"(?:std::)?ios(?:_base)?::sync_with_stdio\s*\([^;]+;",
        r"(?:std::)?cin\.exceptions\s*\([^;]+;",
        r"(?:std::)?cerr\.rdbuf\s*\([^;]+;",
        r"(?:std::)?(?:cout|cerr)\.setf\s*\([^;]+;",
    ]
    for pattern in setup:
        body = re.sub(pattern, " ", body)
    body = body.replace("std::", "")
    return re.sub(r"\s+", " ", body).strip()


def standard_main_kind(source: str, main: Function) -> str | None:
    body = normalize_main_body(source[main.body_start + 1 : main.end - 1])
    body = body.removeprefix(";").strip()

    while_match = re.fullmatch(
        r"(?:int|u32|i32|i64|long long) (?P<tc>\w+)(?: = 1)?; "
        r"(?:(?:cin >> (?P=tc);) )?"
        r"while \((?P=tc)--\) (?:\{ )?solve\(\);(?: \})? ?(?:return 0;)?",
        body,
    )
    if while_match is not None:
        return "multi" if re.search(rf"\bcin >> {while_match.group('tc')}\b", body) else "single"

    for_match = re.fullmatch(
        r"(?:int|u32|i32|i64|long long) (?P<tc>\w+)(?: = 1)?; "
        r"(?:(?:cin >> (?P=tc);) )?"
        r"for \((?:int|u32|i32|i64|long long) (?P<i>\w+) = 0; (?P=i) < (?P=tc); "
        r"(?:\+\+(?P=i)|(?P=i)\+\+)\) \{ solve\(\); \} ?(?:return 0;)?",
        body,
    )
    if for_match is not None:
        return "multi" if re.search(rf"\bcin >> {for_match.group('tc')}\b", body) else "single"

    if re.fullmatch(r"solve\(\); ?(?:return 0;)?", body):
        return "single"
    return None


def canonical_main(read_cases: bool) -> str:
    read = "  std::cin >> tc;\n" if read_cases else ""
    return (
        "int main() { // {{{\n"
        "  std::cin.exceptions(std::cin.failbit);\n"
        "#ifdef LOCAL\n"
        "  std::cerr.rdbuf(std::cout.rdbuf());\n"
        "  std::cout.setf(std::ios::unitbuf);\n"
        "  std::cerr.setf(std::ios::unitbuf);\n"
        "#else\n"
        "  std::ios::sync_with_stdio(false);\n"
        "  std::cin.tie(nullptr);\n"
        "#endif\n"
        "  u32 tc = 1;\n"
        f"{read}"
        "  for (u32 t = 0; t < tc; ++t) {\n"
        "    solve();\n"
        "  }\n"
        "  return 0;\n"
        "}\n"
        "// }}}\n\n"
        "// vim: foldmethod=marker foldlevel=0\n"
    )


def canonical_io_setup() -> str:
    return (
        "  std::cin.exceptions(std::cin.failbit);\n"
        "#ifdef LOCAL\n"
        "  std::cerr.rdbuf(std::cout.rdbuf());\n"
        "  std::cout.setf(std::ios::unitbuf);\n"
        "  std::cerr.setf(std::ios::unitbuf);\n"
        "#else\n"
        "  std::ios::sync_with_stdio(false);\n"
        "  std::cin.tie(nullptr);\n"
        "#endif"
    )


def preserved_main(source: str, main: Function) -> str:
    body = source[main.body_start + 1 : main.end - 1]
    body = HEADER_OPEN_RE.sub("", body)
    body = re.sub(r"(?ms)^\s*#ifdef LOCAL\s*$.*?^\s*#endif\s*$", "", body)
    body = re.sub(
        r"(?m)^\s*(?:std::)?cin\.tie\s*\([^;]+;\s*$|"
        r"^\s*(?:std::)?ios(?:_base)?::sync_with_stdio\s*\([^;]+;\s*$|"
        r"^\s*(?:std::)?cin\.exceptions\s*\([^;]+;\s*$",
        "",
        body,
    ).strip()
    function = "int main() { // {{{\n" + canonical_io_setup()
    if body:
        function += "\n\n" + body
    function += "\n}"
    return function + "\n// }}}\n\n// vim: foldmethod=marker foldlevel=0\n"


def trim_main_marker(source: str) -> str:
    source = source.rstrip()
    marker = HEADER_OPEN_RE.search(source)
    if marker is not None and not source[marker.end() :].strip():
        source = source[: marker.start()].rstrip()
    return source


def standardize(path: Path, header: str, stats: Stats) -> str:
    source = path.read_text()
    solve = find_function(source, "solve")
    main = find_function(source, "main")
    if main is None:
        raise ValueError(f"{path.relative_to(ROOT)} has no main()")

    stats.sources += 1
    entry = solve.start if solve is not None else main.start
    prefix = source[:entry]
    marker = HEADER_END_RE.search(prefix)

    if marker is not None:
        content_start = marker.end()
        stats.marked_headers += 1
    else:
        content_start = entry
        stats.inferred_headers += 1

    middle = trim_main_marker(source[content_start : main.start])
    if solve is None:
        stats.main_only_sources += 1
        middle = extract_pbds(prefix, source[main.start : main.end])
    else:
        stats.solve_sources += 1
        body = source[solve.start : main.end]
        if marker is None:
            inferred = custom_prefix(prefix, body)
            pbds = extract_pbds(prefix, body)
            preserved = "\n\n".join(part for part in (pbds, inferred) if part)
            middle = preserved + ("\n\n" if preserved else "") + source[solve.start : main.start]
        else:
            embedded = custom_prefix(prefix[: marker.start()], body)
            if embedded:
                middle = embedded + "\n\n" + middle

    middle = migrate_tokens(middle, prefix)
    middle = remove_answer_wrappers(middle)
    middle = avoid_answer_name_collisions(middle)
    middle = normalize_output_calls(middle).strip()
    compatibility = compatibility_prelude(middle, prefix)
    sections = [header.rstrip()]
    if compatibility:
        sections.append(compatibility)
    if middle:
        sections.append(middle)

    if solve is None:
        footer = preserved_main(source, main)
    else:
        kind = standard_main_kind(source, main)
        if kind == "multi":
            stats.canonical_multi_mains += 1
            footer = canonical_main(True)
        elif kind == "single":
            stats.canonical_single_mains += 1
            footer = canonical_main(False)
        else:
            stats.preserved_mains += 1
            footer = preserved_main(migrate_tokens(source, prefix), find_function(migrate_tokens(source, prefix), "main") or main)

    result = "\n\n".join(section.rstrip() for section in sections) + "\n\n" + footer
    result = re.sub(r"\n{4,}", "\n\n\n", result)
    if result != source:
        stats.changed += 1
    return result


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Standardize Codeforces C++ sources on template.cc")
    parser.add_argument("--write", action="store_true", help="rewrite sources in place")
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    header = canonical_header()
    stats = Stats()
    failures: list[str] = []

    for path in sorted(CODEFORCES.rglob("*.cc")):
        try:
            result = standardize(path, header, stats)
            if args.write and result != path.read_text():
                path.write_text(result)
        except ValueError as error:
            failures.append(str(error))

    print(f"sources: {stats.sources}")
    print(f"solve(): {stats.solve_sources}")
    print(f"main()-only: {stats.main_only_sources}")
    print(f"marked headers: {stats.marked_headers}")
    print(f"inferred headers: {stats.inferred_headers}")
    print(f"canonical multi-case mains: {stats.canonical_multi_mains}")
    print(f"canonical single-case mains: {stats.canonical_single_mains}")
    print(f"preserved custom mains: {stats.preserved_mains}")
    print(f"changed: {stats.changed}")
    if failures:
        raise SystemExit("\n".join(failures))


if __name__ == "__main__":
    main()
