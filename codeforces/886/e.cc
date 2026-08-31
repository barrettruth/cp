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
  i64 n, c;
  cin >> n >> c;
  i64 sum = 0, sumsq = 0;
  i64 s;
  for (int i = 0; i < n; ++i) {
    cin >> s;
    sum += s;
    sumsq += s * s;
  }

  f128 C = sumsq - c;

  f128 A = 4 * n;
  // NOTE: tbh, look back at solutions,m not sure what went exactly wrong here.
  // most definitely just not taking my time
  // NOTE: didn't check WHY round down/why is this right, just that it *looked* right in the examples
  // this logic is a surefire way to skip certainty and absolutely confuse yourself

  f128 B = 4 * sum;

  i64 root = (-B + sqrtl(B * B - 4 * A * C)) / (2 * A);
  prln("{}", root);

  // NOTE: tbh, look back at solutions,m not sure what went exactly wrong here.
  // most definitely just not taking my time
  // NOTE: didn't check WHY round down/why is this right, just that it *looked* right in the examples
  // this logic is a surefire way to skip certainty and absolutely confuse yourself

  /*
     p ez, if anything should've just been locked and written the equation
     division and long double - fucked

     say paintings are a, b, c

     ax^2+bx+c

     area c= (a + 2w) ^ 2 + ...
    =a^2+4w^2+4aw + ...

     c = a^2+b^2+...+4(a+b+...) * w + 4nw^2
     0 = sumsq - c


     a^2+b^2+c^2=sum of painting area
     (a+2w)^2+(b+2w)^2+...= c; find w quickly

      a^2+2aw+4w^2+...

      c = = a^2 + 4w^2+2aw + ...
      =a^2+b^2+c^2 + ... 2aw + 2bw + 2cw + ... + 4nw^2
      0 = sumsq + 4nw^2 + 2w(a+b+c+d+....) - c
      quadratic formula
      = 4nw^2+2w(a+b+c+d)
      = 4nw^2+2w(a+b+...) - c +a^2+b^2+c^2+...
     */
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
