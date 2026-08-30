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

  vec<string> graph(n);
  for (auto& e : graph)
    cin >> e;

  auto dfs = [&](auto&& self, int i, int j) -> void {
    if (min(i, j) < 0 || i >= n || j >= m || graph[i][j] == '#') {
      return;
    }

    graph[i][j] = '#';

    self(self, i + 1, j);
    self(self, i - 1, j);
    self(self, i, j + 1);
    self(self, i, j - 1);
  };

  u32 ans = 0;

  for (u32 i = 0; i < n; ++i) {
    for (u32 j = 0; j < m; ++j) {
      if (graph[i][j] == '.') {
        dfs(dfs, i, j);
        ++ans;
      }
    }
  }

  cout << ans << '\n';
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
