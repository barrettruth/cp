cxx := "g++"
common_flags := "-std=c++23 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 -Wfloat-equal -Wundef -fdiagnostics-color=always -DLOCAL"
fast_flags := "-O2"
debug_flags := "-g3 -fsanitize=address,undefined -fno-omit-frame-pointer -fstack-protector-all -D_GLIBCXX_DEBUG"

run file:
    @cd "{{invocation_directory()}}"; stem="{{file}}"; stem="${stem%.cc}"; bin="${stem}.run"; \
      echo "> {{cxx}} {{common_flags}} {{fast_flags}} {{file}} -o ${bin}"; \
      {{cxx}} {{common_flags}} {{fast_flags}} {{file}} -o "${bin}" && \
      echo && echo "> ./${bin} < ${stem}.in" && \
      "./${bin}" < "${stem}.in"; code=$?; \
      echo && echo "= exit ${code}"; exit "${code}"

debug file:
    @cd "{{invocation_directory()}}"; stem="{{file}}"; stem="${stem%.cc}"; bin="${stem}.debug"; \
      echo "> {{cxx}} {{common_flags}} {{debug_flags}} {{file}} -o ${bin}"; \
      {{cxx}} {{common_flags}} {{debug_flags}} {{file}} -o "${bin}" && \
      echo && echo "> ./${bin} < ${stem}.in" && \
      "./${bin}" < "${stem}.in"; code=$?; \
      echo && echo "= exit ${code}"; exit "${code}"
