cxx := env("CXX", "g++")
debug_cxx := env("DEBUG_CXX", if os() == "macos" { "/usr/bin/clang++" } else { cxx })
python := env("PYTHON", "python")
hardening := if os() == "macos" { "-D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG" } else { "-D_GLIBCXX_DEBUG" }
common_flags := "-std=c++23 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 -Wfloat-equal -Wundef -fdiagnostics-color=always"
local_flags := "-DLOCAL"
local_env := "LOCAL=1"
fast_flags := "-O2"
debug_flags := "-g3 -fsanitize=address,undefined -fno-omit-frame-pointer -fstack-protector-all " + hardening
run_timeout := "2s"

run file:
    @cd "{{invocation_directory()}}"; stem="{{file}}"; \
      case "{{file}}" in \
      *.cc) stem="${stem%.cc}"; bin="${stem}.run"; \
        {{cxx}} {{common_flags}} {{local_flags}} {{fast_flags}} {{file}} -o "${bin}" && \
        timeout {{run_timeout}} "./${bin}" < "${stem}.in";; \
      *.py) stem="${stem%.py}"; \
        {{local_env}} timeout {{run_timeout}} {{python}} "{{file}}" < "${stem}.in";; \
      *) echo "error: {{file}}: expected a .cc or .py file" >&2; exit 2;; \
      esac

debug file:
    @cd "{{invocation_directory()}}"; stem="{{file}}"; \
      case "{{file}}" in \
      *.cc) stem="${stem%.cc}"; bin="${stem}.debug"; \
        {{debug_cxx}} {{common_flags}} {{local_flags}} {{debug_flags}} {{file}} -o "${bin}" && \
        timeout {{run_timeout}} "./${bin}" < "${stem}.in";; \
      *.py) stem="${stem%.py}"; \
        {{local_env}} timeout {{run_timeout}} {{python}} -X dev "{{file}}" < "${stem}.in";; \
      *) echo "error: {{file}}: expected a .cc or .py file" >&2; exit 2;; \
      esac

judge file:
    @cd "{{invocation_directory()}}"; stem="{{file}}"; \
      case "{{file}}" in \
      *.cc) stem="${stem%.cc}"; bin="${stem}.judge"; \
        {{cxx}} {{common_flags}} {{fast_flags}} {{file}} -o "${bin}" && \
        timeout {{run_timeout}} "./${bin}" < "${stem}.in";; \
      *.py) stem="${stem%.py}"; \
        timeout {{run_timeout}} {{python}} "{{file}}" < "${stem}.in";; \
      *) echo "error: {{file}}: expected a .cc or .py file" >&2; exit 2;; \
      esac
