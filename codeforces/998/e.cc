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

#define FOR(a, b, c) for (int a = (b); (a) < (c); ++(a))

struct union_find {
 public:
  union_find(size_t n = 0) : par(n + 1), rank(n + 1, 0) {
    for (size_t u = 0; u < n + 1; ++u)
      par[u] = u;
  };

  void join(int u, int v) {
    u = find(u), v = find(v);

    if (u == v)
      return;

    if (rank[u] < rank[v])
      std::swap(u, v);

    if (rank[u] == rank[v])
      ++rank[u];

    par[v] = u;
  }

  int find(int u) {
    if (u != par[u])
      par[u] = find(par[u]);
    return par[u];
  }

  void reset(size_t capacity) {
    par.resize(capacity);
    std::iota(par.begin(), par.end(), 0);
    rank.resize(capacity);
  }

  std::vector<int> par;
  std::vector<int> rank;
};

vec<unordered_set<int>> F, G;
union_find Fuf, Guf;
unordered_set<int> to_erase;

void solve() {
  int n, m1, m2;
  cin >> n >> m1 >> m2;

  F.clear();
  F.resize(n + 1);
  G.clear();
  G.resize(n + 1);

  Fuf.reset(n + 1);
  Guf.reset(n + 1);

  FOR(i, 0, m1) {
    int u, v;
    cin >> u >> v;
    F[u].insert(v);
    F[v].insert(u);
  }

  FOR(i, 0, m2) {
    int u, v;
    cin >> u >> v;
    G[u].insert(v);
    G[v].insert(u);
    Guf.join(u, v);
  }

  int ans = 0;

  FOR(u, 1, n + 1) {
    to_erase.clear();
    for (auto v : F[u]) {
      if (Guf.find(u) != Guf.find(v)) {
        to_erase.insert(v);
        F[v].erase(u);
      }
    }
    ans += to_erase.size();
    for (auto e : to_erase)
      F[u].erase(e);
  }

  FOR(u, 1, n + 1) {
    for (auto v : F[u])
      Fuf.join(u, v);
  }

  FOR(u, 1, n + 1) {
    for (auto v : G[u]) {
      if (Fuf.find(u) != Fuf.find(v)) {
        ++ans;
        Fuf.join(u, v);
      }
    }
  }

  prln("{}", ans);
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
