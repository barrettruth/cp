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
#include <cstddef>
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

template <typename T>
using vec = std::vector<T>;

template <typename T, std::size_t N>
using arr = std::array<T, N>;

template <typename T, typename C = std::less<T>>
using pq = std::priority_queue<T, std::vector<T>, C>;

template <typename T, typename C = std::less<T>>
using mset = std::multiset<T, C>;

template <typename T, typename H = std::hash<T>>
using uset = std::unordered_set<T, H>;

template <typename K, typename V, typename H = std::hash<K>>
using umap = std::unordered_map<K, V, H>;

template <typename... Ts>
  requires(sizeof...(Ts) >= 2)
[[nodiscard]] constexpr auto min(Ts&&... xs) {
  using T = std::common_type_t<std::remove_cvref_t<Ts>...>;
  return std::ranges::min({static_cast<T>(xs)...});
}

template <typename... Ts>
  requires(sizeof...(Ts) >= 2)
[[nodiscard]] constexpr auto max(Ts&&... xs) {
  using T = std::common_type_t<std::remove_cvref_t<Ts>...>;
  return std::ranges::max({static_cast<T>(xs)...});
}

using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double;
using f128 = long double;

#if __cplusplus >= 202002L
template <typename T>
constexpr T MIN = std::numeric_limits<T>::min();

template <typename T>
constexpr T MAX = std::numeric_limits<T>::max();
#endif

void YES() { std::println("YES"); }
void Yes() { std::println("Yes"); }
void yes() { std::println("yes"); }
void NO() { std::println("NO"); }
void No() { std::println("No"); }
void no() { std::println("no"); }

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

  vec<u64> F(m + 2);
  for (u32 i = 0; i < n; ++i) {
    u32 a;
    cin >> a;
    ++F[a];
  }

  auto suf = F;
  for (u32 i = m; i > 0; --i) {
    suf[i] += suf[i + 1];
  }

  u64 ans = 0;
  for (u32 x = 1; x <= m; ++x) {
    ans = max(ans, suf[x] + (x * 2 <= m ? F[x * 2] : 0));
  }
  println("{}", ans);
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
