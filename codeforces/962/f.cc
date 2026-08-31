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

void solve() {
  i64 n, k;
  cin >> n >> k;
  vector<i64> a(n), b(n);
  for (auto& e : a)
    cin >> e;
  for (auto& e : b)
    cin >> e;

  i64 l = 0, r = *max_element(a.begin(), a.end());
  vector<i64> last_a(n);
  i64 ans = 0, operations = 0;

  while (l <= r) {
    i64 m = l + (r - l) / 2, s = 0, o = 0;

    for (u32 i = 0; i < n; ++i) {
      if (a[i] >= m) {
        i64 O = (a[i] - m) / b[i] + 1;
        s += O * a[i] - b[i] * O * (O - 1) / 2;
        o += O;
      }
    }

    if (o <= k) {
      ans = s;
      operations = o;
      for (u32 i = 0; i < n; ++i) {
        i64 O = (a[i] - m) / b[i] + 1;
        if (a[i] >= m) {
          last_a[i] = a[i] - O * b[i];
        }
      }
      r = m - 1;
    } else
      l = m + 1;
  }

  auto brute_force = [&]() {
    set<pair<i64, i64>> tree;
    i64 ans = 0;
    for (i64 i = 0; i < n; ++i)
      if (last_a[i] > 0)
        tree.emplace(last_a[i], i);
    for (i64 _ = 0; _ < k && !tree.empty(); ++_) {
      auto it = prev(tree.end());
      auto [score, i] = *it;
      tree.erase(it);
      ans += score;
      if (score > b[i])
        tree.emplace(score - b[i], i);
    }
    return ans;
  };

  k -= operations;
  if (k > 0)
    ans += brute_force();
  cout << ans << '\n';
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
