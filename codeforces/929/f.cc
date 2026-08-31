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

bitset<1000000 + 1> seen;

void solve() {
  seen.reset();

  i32 n, m;
  cin >> n >> m;
  vec<vec<u32>> grid(n, vec<u32>(m));
  for (auto& row : grid)
    for (auto& cell : row)
      cin >> cell;

  queue<pair<i32, i32>> q{{{0, 0}}};
  auto index = [&](i32 r, i32 c) {
    return r * m + c;
  };

  seen.set(index(0, 0));

  auto valid = [&](i32 r, i32 c) {
    return min(r, c) >= 0 && r < n && c < m;
  };

  i32 time = 0;
  i32 ans = MAX<i32>;
  while (!q.empty()) {
    auto qsize{q.size()};

    for (u32 i = 0; i < qsize; ++i) {
      auto [r, c] = q.front();
      q.pop();

      if (c == m - 1) {
        ans = min(ans, time + min(n - 1 - r, (r + 1) % n));
        continue;
      }

      i32 T = time % n;

      if (c < m - 1 && grid[(r + T + 1) % n][c + 1] == 0 &&
          !seen[index(r, c + 1)]) {
        q.emplace(r, c + 1);
        seen.set(index(r, c + 1));
      }

      if (grid[(r + T + 1) % n][c] == 0 && grid[(r + T + 2) % n][c] == 0 &&
          !seen[index((r + 1) % n, c)]) {
        q.emplace((r + 1) % n, c);
        seen.set(index((r + 1) % n, c));
      }
    }

    ++time;
  }

  println("{}", ans == MAX<i32> ? -1 : ans);
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
