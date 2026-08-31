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

void solve() {
  u32 n, q;
  cin >> n >> q;

  vec<vec<u64>> grid(n, vec<u64>(n));

  for (auto& r : grid)
    for (auto& c : r)
      cin >> c;

  vec<vec<u64>> one(n + 1, vec<u64>(n + 1, 0));
  auto colwise = one;
  auto rowwise = one;

  for (u32 i = 1; i <= n; ++i) {
    for (u32 j = 1; j <= n; ++j) {
      one[i][j] = grid[i - 1][j - 1] + one[i - 1][j] + one[i][j - 1] -
                  one[i - 1][j - 1];
    }
  }

  for (u32 i = 1; i <= n; ++i) {
    for (u32 j = 1; j <= n; ++j) {
      colwise[i][j] = i * grid[i - 1][j - 1] + colwise[i][j - 1] +
                      colwise[i - 1][j] - colwise[i - 1][j - 1];
    }
  }

  for (u32 i = 1; i <= n; ++i) {
    for (u32 j = 1; j <= n; ++j) {
      rowwise[i][j] = j * grid[i - 1][j - 1] + rowwise[i][j - 1] +
                      rowwise[i - 1][j] - rowwise[i - 1][j - 1];
    }
  }

  u64 x1, y1, x2, y2;
  for (u32 i = 0; i < q; ++i) {
    cin >> x1 >> y1 >> x2 >> y2;

    auto s =
        one[x2][y2] - one[x2][y1 - 1] - one[x1 - 1][y2] + one[x1 - 1][y1 - 1];
    auto sr = colwise[x2][y2] - colwise[x2][y1 - 1] - colwise[x1 - 1][y2] +
              colwise[x1 - 1][y1 - 1];
    auto sc = rowwise[x2][y2] - rowwise[x2][y1 - 1] - rowwise[x1 - 1][y2] +
              rowwise[x1 - 1][y1 - 1];

    u64 w = y2 - y1 + 1;

    u64 ans = w * (sr - (u64)x1 * s) + (sc - (u64)y1 * s) + s;

    cout << ans << " \n"[i == q - 1];
  }
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
