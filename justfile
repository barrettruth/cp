cxx := env("CXX")
cxx_std := env("CXX_STD")
cxx_hardening_flags := env("CXX_HARDENING_FLAGS")
cxx_sanitizer_flags := env("CXX_SANITIZER_FLAGS")
python := "python"
common_flags := "-std=" + cxx_std + " -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 -Wfloat-equal -Wundef -fdiagnostics-color=always"
local_flags := "-DLOCAL"
local_env := "LOCAL=1"
fast_flags := "-O2"
debug_flags := "-g -fno-omit-frame-pointer -fstack-protector-all " + cxx_hardening_flags + " " + cxx_sanitizer_flags
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
        {{cxx}} {{common_flags}} {{local_flags}} {{debug_flags}} {{file}} -o "${bin}" && \
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
