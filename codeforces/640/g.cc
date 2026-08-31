#include <bits/stdc++.h> // {{{

#if __cplusplus >= 202002L && defined(__cpp_lib_ranges)
namespace rng = std::ranges;
namespace rv = rng::views;
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

template <typename T>
using cvrefless_t = std::remove_cv_t<std::remove_reference_t<T>>;

template <typename T, typename U, typename... Ts>
[[nodiscard]] constexpr auto min(T&& x, U&& y, Ts&&... xs) {
  using R = std::common_type_t<cvrefless_t<T>, cvrefless_t<U>, cvrefless_t<Ts>...>;
  const std::initializer_list<R> values{
      static_cast<R>(std::forward<T>(x)), static_cast<R>(std::forward<U>(y)),
      static_cast<R>(std::forward<Ts>(xs))...};
  return std::min(values);
}

template <typename T, typename U, typename... Ts>
[[nodiscard]] constexpr auto max(T&& x, U&& y, Ts&&... xs) {
  using R = std::common_type_t<cvrefless_t<T>, cvrefless_t<U>, cvrefless_t<Ts>...>;
  const std::initializer_list<R> values{
      static_cast<R>(std::forward<T>(x)), static_cast<R>(std::forward<U>(y)),
      static_cast<R>(std::forward<Ts>(xs))...};
  return std::max(values);
}

using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double;
using f128 = long double;

template <typename T>
constexpr T MIN = std::numeric_limits<T>::lowest();

template <typename T>
constexpr T MAX = std::numeric_limits<T>::max();

void YES() { std::cout << "YES\n"; }
void Yes() { std::cout << "Yes\n"; }
void yes() { std::cout << "yes\n"; }
void NO() { std::cout << "NO\n"; }
void No() { std::cout << "No\n"; }
void no() { std::cout << "no\n"; }

#if defined(__cpp_lib_print) && __cpp_lib_print >= 202207L
#define pr(...) std::print(__VA_ARGS__)
#define prln(...) std::println(__VA_ARGS__)
#endif
// }}}

template <typename T = i32, typename U>
[[nodiscard]] constexpr T sz(const U& value) {
  return static_cast<T>(std::size(value));
}

void solve() {
  int n;
  cin >> n;

  /*

     1, 4, 2, 5, 3, 6, 9, 7, 10, 8

1: 5, 7, 3, 6 -> pop -> 2, -4, 3
2: 5, 7, 3, 6, 8
3: 3, 7, 9, 6, 8 -> +4, +2, -3, +2
4: 3, -2, 3, -2

     1, 4, 2, 5, 3, 7, 9, 6, 8

     n = 4 -> 2 4 1 3


     +1, +3, -2, +3, -2, +3, +3, -2, +3, -2

   */

  if (n < 4) {
    println("{}", -1);
    return;
  }

  if (n == 4) {
    println("2 4 1 3");
    return;
  }

  vec<int> ans{1};
  int prev = 1;
  --n;
  while (n >= 5) {
    for (auto diff : {3, -2, 3, -2, 3}) {
      prev += diff;
      ans.push_back(prev);
    }
    n -= 5;
  }

  vec<int> diff;
  switch (n) {
    case 1:
      ans.pop_back();
      ans.pop_back();
      diff = {2, -4, 3};
      break;
    case 2:
      ans.pop_back();
      ans.pop_back();
      diff = {2, -4, 3, 2};
      break;
    case 3:
      ans.pop_back();
      diff = {4, 2, -3, 2};
      break;
    case 4:
      diff = {3, -2, 3, -2};
      break;
  }
  for (auto d : diff) ans.push_back(ans[sz(ans) - 1] + d);

  for (auto e : ans) cout << e << ' ';
  println();
}

int main() { // {{{
  std::cin.exceptions(std::cin.failbit);
#ifdef LOCAL
  std::cerr.rdbuf(std::cout.rdbuf());
  std::cout.setf(std::ios::unitbuf);
  std::cerr.setf(std::ios::unitbuf);
#else
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
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
