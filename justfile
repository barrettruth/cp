cxx := env("CXX", "g++")
debug_cxx := env("DEBUG_CXX", if os() == "macos" { "/usr/bin/clang++" } else { cxx })
hardening := if os() == "macos" { "-D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG" } else { "-D_GLIBCXX_DEBUG" }
common_flags := "-std=c++23 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 -Wfloat-equal -Wundef -fdiagnostics-color=always -DLOCAL"
fast_flags := "-O2"
debug_flags := "-g3 -fsanitize=address,undefined -fno-omit-frame-pointer -fstack-protector-all " + hardening
run_timeout := "2s"

run file:
    @cd "{{invocation_directory()}}"; stem="{{file}}"; stem="${stem%.cc}"; bin="${stem}.run"; \
      echo "> {{cxx}} {{common_flags}} {{fast_flags}} {{file}} -o ${bin}"; \
      {{cxx}} {{common_flags}} {{fast_flags}} {{file}} -o "${bin}" && \
      echo && echo "> timeout {{run_timeout}} ./${bin} < ${stem}.in" && \
      timeout {{run_timeout}} "./${bin}" < "${stem}.in"; code=$?; \
      echo && echo "= exit ${code}"; exit "${code}"

debug file:
    @cd "{{invocation_directory()}}"; stem="{{file}}"; stem="${stem%.cc}"; bin="${stem}.debug"; \
      echo "> {{debug_cxx}} {{common_flags}} {{debug_flags}} {{file}} -o ${bin}"; \
      {{debug_cxx}} {{common_flags}} {{debug_flags}} {{file}} -o "${bin}" && \
      echo && echo "> timeout {{run_timeout}} ./${bin} < ${stem}.in" && \
      timeout {{run_timeout}} "./${bin}" < "${stem}.in"; code=$?; \
      echo && echo "= exit ${code}"; exit "${code}"
