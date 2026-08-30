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

void solve() {
  u32 n, m, q;
  cin >> n >> m >> q;

  vec<vec<u64>> delta(n + 1, vec<u64>(n + 1, MAX<u64>));

  using Edge = pair<u64, u32>;

  vec<vec<Edge>> graph(n + 1);

  for (u32 i = 0; i < m; ++i) {
    u32 u, v;
    u64 w;
    cin >> u >> v >> w;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }

  for (u32 node = 1; node <= n; ++node) {
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.emplace(0, node);

    while (!pq.empty()) {
      auto [w, u] = pq.top();
      pq.pop();

      if (w >= delta[node][u]) {
        continue;
      }

      delta[node][u] = w;

      for (auto& [v, W] : graph[u]) {
        if (w + W < delta[node][v]) {
          pq.emplace(w + W, v);
        }
      }
    }
  }

  for (u32 i = 0; i < q; ++i) {
    u32 u, v;
    cin >> u >> v;

    cout << (delta[u][v] == MAX<u64> ? -1 : (i64)delta[u][v])
         << " \n"[i == q - 1];
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
