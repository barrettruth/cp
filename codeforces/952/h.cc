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

template <typename T = i32, typename U>
[[nodiscard]] constexpr T sz(const U& value) {
  return static_cast<T>(std::size(value));
}

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a))

struct union_find {
 public:
  union_find(size_t n) : par(n + 1), rank(n + 1, 0), size(n + 1, 0) {
    std::iota(par.begin(), par.end(), 0);
  };

  void join(int u, int v) {
    u = find(u), v = find(v);

    if (size[u] == 0)
      size[u] = 1;
    if (size[v] == 0)
      size[v] = 1;

    if (u == v)
      return;

    if (rank[u] < rank[v])
      std::swap(u, v);

    if (rank[u] == rank[v]) {
      ++rank[u];
    }
    size[u] += size[v];

    par[v] = u;
  }

  int find(int u) {
    if (u != par[u])
      par[u] = find(par[u]);
    return par[u];
  }

  size_t capacity;
  std::vector<int> par;
  std::vector<int> rank;
  std::vector<int> size;
};

vector<pair<int, int>> dirs;

vec<string> grid;

void solve() {
  int n, m;
  cin >> n >> m;
  vec<bool> seen(n * m + 1, false);

  grid.resize(n);

  union_find uf(m * n);

  auto index = [&m](int r, int c) {
    return r * m + c;
  };

  auto valid = [&](int r, int c) {
    return min(r, c) >= 0 && r < n && c < m;
  };

  FOR(r, 0, n) {
    cin >> grid[r];
  }

  FOR(r, 0, n) {
    FOR(c, 0, m) {
      if (grid[r][c] == '#') {
        uf.join(index(r, c), index(r, c));
        for (auto [dr, dc] : dirs) {
          int nr = r + dr, nc = c + dc;
          if (valid(nr, nc) && grid[nr][nc] == '#') {
            uf.join(index(r, c), index(nr, nc));
          }
        }
      }
    }
  }

  i64 ans = 0;

  FOR(r, 0, n) {
    i64 cur = 0;
    seen.assign(sz(seen), false);
    FOR(c, 0, m) {
      cur += grid[r][c] == '.';
      if (grid[r][c] == '.') {
      FOR(dr, -1, 2) {
        int nr = r + dr;
        int i;
        if (valid(nr, c) && !seen[i = uf.find(index(nr, c))]) {
          cur += uf.size[i];
          seen[i] = true;
        }
      }
    }
    }
    ans = max(ans, cur);
  }

  FOR(c, 0, m) {
    i64 cur = 0;
    seen.assign(sz(seen), false);
    FOR(r, 0, n) {
      cur += grid[r][c] == '.';
      FOR(dc, -1, 2) {
        int nc = c + dc;
        int i;
        if (valid(r, nc) && !seen[i = uf.find(index(r, nc))]) {
          cur += uf.size[i];
          seen[i] = true;
        }
      }
    }
    ans = max(ans, cur);
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

// {{{

  dirs.emplace_back(1, 0);
  dirs.emplace_back(-1, 0);
  dirs.emplace_back(0, 1);
  dirs.emplace_back(0, -1);

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
// }}}

// vim: foldmethod=marker foldlevel=0
