#include <bits/stdc++.h> // {{{

#include <iostream>
#include <limits>

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
//  }}}

void solve() {
  u32 n, q;
  cin >> n >> q;
  vector<u32> a(n), b(n);

  for (auto& e : a) cin >> e;
  for (auto& e : b) cin >> e;

  vector<u32> prefmax(n + 2, 0);

  for (u32 i = n; i >= 1; --i) {
    prefmax[i] = max(prefmax[i + 1], max(a[i - 1], b[i - 1]));
  }

  for (u32 i = 1; i <= n + 1; ++i) {
    prefmax[i] += prefmax[i - 1];
  }

  u32 l, r;
  for (u32 i = 0; i < q; ++i) {
    cin >> l >> r;

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

  u32 t;
  cin >> t;

  for (u32 i = 0; i < t; ++i) {
    solve();
  }
} // }}}
}
// vim: set foldmethod=manual foldmarker={{{,}}}
