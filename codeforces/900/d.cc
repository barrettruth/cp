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

string reverseIntervals(string s, vector<pair<int, int>>& intervals) {
  int n = s.length();
  vector<int> flip(n + 1, 0);

  for (auto& interval : intervals) {
    int start = interval.first, end = interval.second;
    if (start >= 0 && end < n && start <= end) {
      flip[start]++;
      flip[end + 1]--;
    }
  }

  int current = 0;
  for (int i = 0; i < n; ++i) {
    current += flip[i];
    if (current % 2 == 1) {
      int j = n - 1 - i;
      if (i < j) {
        swap(s[i], s[j]);
      }
    }
  }

  return s;
}

void solve() {
  int k, n;
  cin >> n >> k;
  string s;
  cin >> s;
  vec<int> L(k), R(k);
  for (auto& e : L)
    cin >> e;
  for (auto& e : R)
    cin >> e;
  int q;
  cin >> q;
  int x;
  vec<std::pair<int, int>> intervals;
  while (q--) {
    cin >> x;

    int l = 0, r = k - 1;

    while (l <= r) {
      int m = l + (r - l) / 2;
      if (L[m] <= x) {
        l = m + 1;
      } else {
        r = m - 1;
      }
    }

    int i = r;
    int left = min(x, R[i] + L[i] - x), right = max(x, R[i] + L[i] - x);

    prln("{} {}", left - 1, right - 1);
    intervals.emplace_back(left - 1, right - 1);
  }

  string ans = reverseIntervals(s, intervals);
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
