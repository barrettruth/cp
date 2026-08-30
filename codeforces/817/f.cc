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

bitset<50 * 50 + 1> visited;

void solve() {
  const i32 dr8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const i32 dc8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
  u32 n, m;
  cin >> n >> m;
  vec<string> g(n);
  for (auto& s : g)
    cin >> s;
  vec<vec<u32>> vis(n, vec<u32>(m, 0));
  bool ok = true;
  for (i32 r = 0; r < (i32)n && ok; ++r)
    for (i32 c = 0; c < (i32)m && ok; ++c)
      if (g[r][c] == '*' && !vis[r][c]) {
        vec<pair<i32, i32>> comp;
        vec<pair<i32, i32>> q = {{r, c}};
        vis[r][c] = 1;
        for (i32 qi = 0; qi < (i32)q.size(); ++qi) {
          auto [x, y] = q[qi];
          comp.push_back({x, y});
          for (i32 d = 0; d < 8; ++d) {
            i32 nx = x + dr8[d], ny = y + dc8[d];
            if (0 <= nx && nx < (i32)n && 0 <= ny && ny < (i32)m &&
                g[nx][ny] == '*' && !vis[nx][ny]) {
              vis[nx][ny] = 1;
              q.push_back({nx, ny});
            }
          }
        }
        if (comp.size() != 3) {
          ok = false;
          break;
        }
        vec<i32> rows, cols;
        for (auto [x, y] : comp) {
          rows.push_back(x);
          cols.push_back(y);
        }
        sort(rows.begin(), rows.end());
        rows.erase(unique(rows.begin(), rows.end()), rows.end());
        sort(cols.begin(), cols.end());
        cols.erase(unique(cols.begin(), cols.end()), cols.end());
        if (rows.size() != 2 || cols.size() != 2) {
          ok = false;
          break;
        }
        i32 cnt = 0;
        for (i32 i = 0; i < 2; ++i)
          for (i32 j = 0; j < 2; ++j)
            for (auto [x, y] : comp)
              if (x == rows[i] && y == cols[j])
                ++cnt;
        if (cnt != 3) {
          ok = false;
          break;
        }
      }
  if (ok)
    YES();
  else
    NO();
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
