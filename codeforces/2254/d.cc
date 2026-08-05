#include <bits/stdc++.h> // {{{

#include <version>
#ifdef __cpp_lib_ranges_enumerate
#include <ranges>
namespace rv = std::views;
namespace rs = std::ranges;
#endif

#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double;
using f128 = long double;

#if __cplusplus >= 202002L
template <typename T> constexpr T MIN = std::numeric_limits<T>::min();

template <typename T> constexpr T MAX = std::numeric_limits<T>::max();
#endif

#ifdef LOCAL
#define db(...) std::print(__VA_ARGS__)
#define dbln(...) std::println(__VA_ARGS__)
#else
#define db(...)
#define dbln(...)
#endif
// }}}

void solve() {
  u32 n;
  cin >> n;

  vector<i64> b(n);
  map<i64, i64> cnt;

  for (auto &e : b) {
    cin >> e;
    ++cnt[e];
  }

  bool ok = begin(cnt)->first == 0;
  i64 prev = 0;

  for (auto it = begin(cnt); it != end(cnt); ++it) {
    if (!ok) {
      println("-1");
      return;
    }
    i64 v = prev + 1;

    auto nxt = next(it);
    if (nxt != end(cnt)) {
      i64 gap = nxt->first - it->first;

      ok = gap % it->second == 0;
      v = gap / it->second;
    }

    ok = ok && v > prev;

    it->second = v, prev = v;
  }

  if (ok) {
    // ??
    for (i64 e : b) {
      print("{} ", cnt[e]);
    }

    println();
  } else {
    println("-1");
  }
}

int main() { // {{{
  std::cin.exceptions(std::cin.failbit);
#ifdef LOCAL
  std::cerr.rdbuf(std::cout.rdbuf());
  std::cout.setf(std::ios::unitbuf);
  std::cerr.setf(std::ios::unitbuf);
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif
  u32 tc = 1;
  std::cin >> tc;
  for (u32 t = 0; t < tc; ++t) {
    solve();
  }
  return 0;
}
// }}}

// vim: foldmethod=marker foldlevel=0
