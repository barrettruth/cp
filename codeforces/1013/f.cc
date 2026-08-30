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

constexpr static i64 MOD = 998244353;

void solve() {
  int n, m;
  f128 d;
  cin >> n >> m >> d;
  i64 d_squared = i64(d * d + 0.5);  // Round to nearest integer

  auto dist = [](pair<i64, i64> p1, pair<i64, i64> p2) {
    return (p1.first - p2.first) * (p1.first - p2.first) +
           (p1.second - p2.second) * (p1.second - p2.second);
  };

  vector<string> grid(n);
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
  }

  reverse(grid.begin(), grid.end());

  vector<vector<pair<i64, i64>>> holds(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == 'X') {
        holds[i].emplace_back(j, i);
      }
    }
  }

  // Check if starting level has holds
  if (holds[0].empty()) {
    cout << "0\n";
    return;
  }

  vector<i64> prev(holds[0].size(), 1);
  for (int level = 1; level < n; ++level) {
    if (holds[level].empty()) {
      cout << "0\n";
      return;
    }
    vector<i64> dp1(holds[level].size(), 0);
    vector<i64> dp2(holds[level].size(), 0);
    // First pass: transition from previous level
    int l = 0, r = 0;
    i64 total = 0;
    for (int i = 0; i < holds[level].size(); ++i) {
      auto& h = holds[level][i];
      // Expand r to include holds with dist <= d_squared
      while (r < prev.size() && dist(holds[level - 1][r], h) <= d_squared) {
        total = (total + prev[r]) % MOD;
        r++;
      }
      // Shrink l to exclude holds with dist > d_squared
      while (l < r && dist(holds[level - 1][l], h) > d_squared) {
        total = (total - prev[l] + MOD) % MOD;
        l++;
      }
      dp1[i] = total;
    }
    // Second pass: same-level transitions (pairs)
    l = 0, r = 0;
    total = 0;
    for (int i = 0; i < holds[level].size(); ++i) {
      auto& h = holds[level][i];
      // Expand r to include holds with dist <= d_squared
      while (r < holds[level].size() && dist(holds[level][r], h) <= d_squared) {
        total = (total + dp1[r]) % MOD;
        r++;
      }
      // Shrink l to exclude holds with dist > d_squared
      while (l < r && dist(holds[level][l], h) > d_squared) {
        total = (total - dp1[l] + MOD) % MOD;
        l++;
      }
      // Subtract dp1[i] to avoid self-pairing
      dp2[i] = (total - dp1[i] + MOD) % MOD;
    }
    // Combine dp1 and dp2
    for (int i = 0; i < holds[level].size(); ++i) {
      dp1[i] = (dp1[i] + dp2[i]) % MOD;
    }
    prev = dp1;
  }

  i64 ans = accumulate(prev.begin(), prev.end(), 0LL) % MOD;
  cout << ans << "\n";
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
