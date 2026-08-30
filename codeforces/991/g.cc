#include <bits/stdc++.h> // {{{

#if __cplusplus >= 202002L && defined(__cpp_lib_ranges)
namespace rv = std::views;
namespace rs = std::ranges;
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

  unordered_map<int, vector<int>> graph;

  while (--n) {
    int u, v;
    cin >> u >> v;

    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  auto ans = MIN<int>;

  auto is_leaf = [&graph](int u) {
    return (u != 1 && graph[u].size() == 1) || (u == 1) && graph[u].empty();
  };

  auto dfs = [&](auto &dfs, int u, int parent) -> int {
    if (u == parent || is_leaf(u)) {
      return 0;
    }

    int first = 0, second = 0;

    for (auto v : graph[u]) {
      if (v == parent)
        continue;

      auto through = dfs(dfs, v, u);

      if (through > first) {
        second = through;
        swap(first, second);
      } else if (through > second) {
        second = through;
      }
    }

    int remove_u_and_one_child = sz(graph[u]) - (u != 1) - (first != 0) + first;
    int remove_through_u =
        sz(graph[u]) - (u != 1) - (first != 0) - (second != 0) + first + second;
    int no_remove_u = 1 + first;

    ans = max(ans, max(remove_through_u, no_remove_u));

    return remove_u_and_one_child;
  };

  std::cout << max(ans, dfs(dfs, 1, -1)) << '\n';
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
