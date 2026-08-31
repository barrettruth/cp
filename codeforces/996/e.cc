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

#define rall(x) (x).rbegin(), (x).rend()

#define FORI(a, b, c) for (int a = (b); a < (c); ++a)

void fill(vec<vec<i64>>& matrix, vec<int>& a, int k) {
  int n = matrix.size();
  int m = matrix[0].size();

  vec<vec<int>> extra(n, vec<int>(m));

  FORI(i, 0, n) {
    FORI(j, 0, m) {
      int top = max(0, i - (k - 1));
      int left = max(0, j - (k - 1));
      int bottom = min(n - k, i);
      int right = min(m - k, j);
      extra[i][j] = (bottom - top + 1) * (right - left + 1);
    }
  }

  vec<pair<int, pair<int, int>>> cells;
  FORI(i, 0, n) {
    FORI(j, 0, m) {
      cells.push_back({extra[i][j], {i, j}});
    }
  }

  sort(rall(cells));

  FORI(i, 0, min(n * m, sz<int>(a))) {
    auto [x, y] = cells[i].second;
    matrix[x][y] = a[i];
  }
}

long long sums(vector<vector<i64>>& matrix, int k) {
  int n = matrix.size(), m = matrix[0].size();

  vec<vec<i64>> prefix(n + 1, vec<i64>(m + 1, 0));
  FORI(i, 1, n + 1) {
    FORI(j, 1, m + 1) {
      prefix[i][j] = matrix[i - 1][j - 1] + prefix[i - 1][j] +
                     prefix[i][j - 1] - prefix[i - 1][j - 1];
    }
  }
  auto get = [&](int r1, int c1, int r2, int c2) -> i64 {
    return prefix[r2 + 1][c2 + 1] - prefix[r2 + 1][c1] - prefix[r1][c2 + 1] +
           prefix[r1][c1];
  };
  i64 ans = 0;
  FORI(i, 0, n - k + 1) {
    FORI(j, 0, m - k + 1) {
      ans += get(i, j, i + k - 1, j + k - 1);
    }
  }
  return ans;
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  int w;
  cin >> w;
  vec<int> a(w);
  for (auto& e : a)
    cin >> e;
  sort(rall(a));

  vector<vector<i64>> matrix(n, vector<i64>(m, 0));

  fill(matrix, a, k);

  prln("{}", sums(matrix, k));
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
