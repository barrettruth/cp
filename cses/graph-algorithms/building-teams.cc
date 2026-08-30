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
  u32 n, m;
  cin >> n >> m;

  // -1/0/1 -> unset, c0, c1
  vector<i32> color(n + 1, -1);

  vec<vec<u32>> forest(n + 1);

  for (u32 i = 0; i < m; ++i) {
    u32 u, v;
    cin >> u >> v;
    forest[u].push_back(v);
    forest[v].push_back(u);
  }

  auto bfs = [&](u32 u) -> bool {
    queue<u32> q{{u}};
    color[u] = 0;

    while (!q.empty()) {
      u = q.front();
      q.pop();

      for (auto v : forest[u]) {
        if (color[v] == color[u]) {
          return false;
        }
        if (color[v] == -1) {
          color[v] = 1 - color[u];
          q.push(v);
        }
      }
    }

    return true;
  };

  for (u32 u = 1; u <= n; ++u) {
    if (color[u] == -1 && !bfs(u)) {
      cout << "IMPOSSIBLE\n";
      return;
    }
  }

  for (u32 i = 1; i <= n; ++i) {
    cout << color[i] + 1 << " \n"[i == n];
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
