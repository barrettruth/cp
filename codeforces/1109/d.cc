#include <version> // {{{

#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <cctype>
#include <chrono>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <format>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numbers>
#include <numeric>
#include <optional>
#include <print>
#include <queue>
#include <random>
#include <set>
#include <span>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#if __has_include(<ranges>)
#include <ranges>
namespace rv = std::views;
namespace rs = std::ranges;
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("O2,unroll-loops")
#if defined(__x86_64__) || defined(__i386__)
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif
#endif

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
  u32 n, m;
  cin >> n >> m;

  vector<i64> a(n + 1), b(m);
  a[0] = 0;
  for (u32 i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (u32 i = 0; i < m; ++i) {
    cin >> b[i];
  }

  sort(begin(b), end(b));

  vector<i64> MAX(n + 1), MIN(n + 1);
  MAX[0] = MIN[0] = 0;
  u32 j = 0;
  i64 acc = 0;

  for (u32 i = 1; i <= n; ++i) {
    acc += a[i];
    if (j < b.size() && b[j] == i) {
      MIN[i] = min(MIN[i - 1] + a[i], -(MAX[i - 1] + a[i]));
      MAX[i] = max(MAX[i - 1] + a[i], -(MIN[i - 1] + a[i]));
      ++j;
    } else {
      MAX[i] = MAX[i - 1] + a[i];
      MIN[i] = MIN[i - 1] + a[i];
    }
  }

  println("{}", MAX[n]);
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
