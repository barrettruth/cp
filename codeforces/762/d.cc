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

bitset<100000 + 1> friends;
void solve() {
  /*
     binary search on alpha

     how to know if i can choose at least n - 1 shops to give each guy a present
     basically, choose, out of all m shops, n shops, one gives each guy a
present (in the worst)

     hm - must dynamically, per bsearch query, filter arrays

     consider each array: if someone unset can be set, + 1 to count, update max
     if already set, take max of large value

challenge: n - 1 shops, not  all n
 take a step back:

 we have m arrays, each which set values offriend individually

 consider each friend separately - have multiple values of joy set to; filter to
>= mid alphaq

 not nec. choose ones that set most -> greedy

 ok - one shop per friend - per friend, iterate - find shop that sets their joy
>= alpha

 now, either < n (bad) or n shops - consider each friend as the "substitute"
candidate

 in other words, consider each friend, and iter AGAIN thru the shit - can we
find ANOTHER diff array setting this guy, as well as setting another friend?

 if so, done!
     */

  u32 m, n;
  cin >> m >> n;

  vec<vec<u64>> p(m, vec<u64>(n));
  u64 maxp = 0;
  for (auto& row : p) {
    for (auto& e : row) {
      cin >> e;
      maxp = max(maxp, e);
    }
  }

  u64 l = 1, r = maxp;

  auto ok = [&](u64 alpha) {
    friends.reset();
    bool both_covered = false;

    for (auto& shop : p) {
      u32 shop_count = 0;
      for (u32 i = 0; i < n; ++i) {
        if (shop[i] >= alpha) {
          ++shop_count;
          friends.set(i);
        }
      }
      both_covered |= shop_count > 1;
    }

    return friends.count() == n && both_covered;
  };

  while (l <= r) {
    u64 alpha = l + (r - l) / 2;

    if (ok(alpha)) {
      l = alpha + 1;
    } else {
      r = alpha - 1;
    }
  }

  println("{}", r);
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
