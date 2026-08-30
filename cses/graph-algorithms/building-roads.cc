#include <bits/stdc++.h>  // {{{

using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double;
using f128 = long double;

template <typename T>
constexpr T MIN = std::numeric_limits<T>::min();

template <typename T>
constexpr T MAX = std::numeric_limits<T>::max();

template <typename T, typename U>
[[nodiscard]] static T sc(U&& x) {
  return static_cast<T>(x);
}

template <typename T, typename U>
[[nodiscard]] static T sz(U&& x) {
  return static_cast<T>(x.size());
}

static void NO() {
  std::cout << "NO\n";
}

static void YES() {
  std::cout << "YES\n";
}

template <typename T>
using vec = std::vector<T>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define ff first
#define ss second

//  }}}

bitset<2 * 100000 + 1> seen;

void solve() {
  seen.reset();

  u32 n, m;
  cin >> n >> m;

  vec<vec<u32>> graph(n + 1);

  for (u32 i = 0; i < m; ++i) {
    u32 u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  auto dfs = [&](auto&& self, u32 u) {
    if (seen[u]) {
      return;
    }

    seen[u] = true;

    for (auto v : graph[u]) {
      self(self, v);
    }
  };

  vec<u32> component_roots;
  for (u32 u = 1; u <= n; ++u) {
    if (!seen[u]) {
      dfs(dfs, u);
      component_roots.push_back(u);
    }
  }

  cout << component_roots.size() - 1 << '\n';
  for (i32 i = 0; i < component_roots.size() - 1; ++i) {
    cout << component_roots[i] << ' ' << component_roots[i + 1] << '\n';
  }
}

int main() {  // {{{
  std::cin.exceptions(std::cin.failbit);

#ifdef LOCAL
  std::cerr.rdbuf(std::cout.rdbuf());
  std::cout.setf(std::ios::unitbuf);
  std::cerr.setf(std::ios::unitbuf);
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  u32 tc = 1;
  // std::cin >> tc;

  for (u32 t = 0; t < tc; ++t) {
    solve();
  }

  return 0;
}
// }}}
