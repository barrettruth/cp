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

#define all(x) (x).begin(), (x).end()

#define FOR(a, b, c) for (int a = (b); a < (c); ++a)

static constexpr int MOD = 1000000007;
static constexpr int MAX_N = 2 * 100000 + 1;

static vec<i64> fac(MAX_N + 1, 1);
bitset<MAX_N> seen;

void solve() {
  int n, k;
  cin >> n >> k;
  vec<int> a(n);
  seen.reset();
  for (auto &e : a) {
    cin >> e;
  }
  sort(all(a));

  i64 ans = 0;
  prln("----------------------");
  for (auto value : a) {
    pr("{} ", value);
  }
  prln();

  FOR(i, 0, n) {
    if (a[i] == 0 || seen[a[i]])
      continue;
    seen[a[i]] = true;
    // count <=, >=
    int lt = distance(a.begin(), lower_bound(all(a), a[i]));
    int gt = distance(upper_bound(all(a), a[i]), a.end());
    int eq = n - lt - gt - 1;

    if (lt + eq < k / 2)
      continue;
    eq -= max(0, k / 2 - lt);
    if (gt + eq < k / 2)
      continue;
    eq -= max(0, k / 2 - gt);

    prln("x={}, lt={}, gt={}, remaining eq={}", a[i], lt, gt, eq);
    ans = (ans + (max(1, lt) * max(1, gt)) % MOD) % MOD;

    // count =
    int left = eq;
    if (lt < k / 2)
      eq -= k / 2 - lt;
    if (gt < k / 2)
      eq -= k / 2 - gt;

    // - max(0, (k / 2 - lt)) - max(0, (k / 2 - gt)) + 1;
    //   dbgln("with element {}, have {} choices", a[i], left);
    //   FOR(i, 1, left) {
    //     i64 nci = fac[left] / (fac[i] * fac[left - i]);
    //     dbgln("n={} choose i={}, nci={}", n, i, nci);
    //     ans = (ans + nci) % MOD;
    //   }
    // }

    prln("{}", ans);
  }
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

  fac[0] = 1LL;
  FOR(i, 1, MAX_N + 1) {
    fac[i] = i * fac[i - 1];
  }

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
// }}}

// vim: foldmethod=marker foldlevel=0
