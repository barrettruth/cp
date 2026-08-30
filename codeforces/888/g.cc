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

#define all(x) (x).begin(), (x).end()

template <typename T>
struct union_find {
 public:
  explicit union_find(size_t capacity)
      : par(capacity + 1, 0), rank(capacity + 1, 0) {
    std::iota(par.begin(), par.end(), 0);
  };

  void join(T u, T v) noexcept {
    u = find(u), v = find(v);

    if (u == v)
      return;

    if (rank[u] < rank[v])
      std::swap(u, v);

    if (rank[u] == rank[v])
      ++rank[u];

    par[v] = u;
  }

  [[nodiscard]] T find(T const& u) noexcept {
    if (u != par[u])
      par[u] = find(par[u]);
    return par[u];
  }

  std::vector<T> par;
  std::vector<int> rank;
};

void solve() {
  int n, m;
  cin >> n >> m;

  vec<i64> heights(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> heights[i];

  vec<arr<i64, 3>> roads(m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    if (heights[u] > heights[v]) {
      roads.push_back({heights[u] - heights[v], u, v});
    } else {
      roads.push_back({heights[v] - heights[v], v, u});
    }
  }

  sort(all(roads));
  union_find<int> uf(n);

  int q;
  cin >> q;
  vec<arr<i64, 5>> queries(q);
  for (int i = 0; i < q; ++i) {
    i64 a, b, e;
    cin >> a >> b >> e;
    queries[i] = {heights[a] + e, a, b, e, i};
  }
  sort(all(queries));

  vec<bool> ans(n, false);

  for (auto& [hab, a, b, e, i] : queries) {
    while (i < m && roads[i][0] <= hab && roads[i][1] <= hab) {
      uf.join(a, roads[0][1]);
      uf.join(a, roads[0][2]);
      ++i;
    }

    ans[i] = uf.find(a) == uf.find(b);
  }

  for (auto e : ans) {
    e ? YES() : NO();
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
