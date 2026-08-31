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
  int n, a, b;
  cin >> n >> a >> b;
  vector<vector<pair<int, int>>> tree(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    tree[u].emplace_back(v, w);
    tree[v].emplace_back(u, w);
  }

  unordered_set<int> xor_values;
  vector<int> xor_a(n + 1, 0);
  vector<bool> visited(n + 1, false);
  bool found = false;
  int target_xor = -1;

  // First DFS to compute xor_a and check if direct a->b is 0
  function<void(int, int)> dfs1 = [&](int u, int parent) {
    visited[u] = true;
    for (auto &[v, w] : tree[u]) {
      if (v != parent && !visited[v]) {
        xor_a[v] = xor_a[u] ^ w;
        if (v == b) {
          target_xor = xor_a[v];
          if (target_xor == 0) {
            found = true;
          }
        }
        dfs1(v, u);
      }
    }
  };

  dfs1(a, -1);
  if (found) {
    cout << "YES\n";
    return;
  }

  // Second DFS to collect xor values from a, excluding b
  visited.assign(n + 1, false);
  function<void(int, int)> dfs2 = [&](int u, int parent) {
    visited[u] = true;
    if (u != b) {
      xor_values.insert(xor_a[u]);
    }
    for (auto &[v, w] : tree[u]) {
      if (v != parent && !visited[v]) {
        dfs2(v, u);
      }
    }
  };

  dfs2(a, -1);

  // Third DFS to check if any node in b's subtree (or elsewhere) has xor_a[u]
  // == target_xor
  visited.assign(n + 1, false);
  function<bool(int, int)> dfs3 = [&](int u, int parent) {
    visited[u] = true;
    if (u != a && u != b && xor_values.count(xor_a[u] ^ target_xor)) {
      return true;
    }
    for (auto &[v, w] : tree[u]) {
      if (v != parent && !visited[v]) {
        if (dfs3(v, u)) {
          return true;
        }
      }
    }
    return false;
  };

  if (dfs3(b, -1)) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
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
