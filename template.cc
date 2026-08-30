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

template <typename T, typename = void>
struct print_is_range : std::false_type {};

template <typename T>
struct print_is_range<
    T, std::void_t<decltype(std::begin(std::declval<const T&>())),
                   decltype(std::end(std::declval<const T&>()))>> : std::true_type {};

template <typename T>
void write_one(std::ostream& out, const T& value);

template <typename T, typename U>
void write_one(std::ostream& out, const std::pair<T, U>& value) {
  out << '(';
  write_one(out, value.first);
  out << ", ";
  write_one(out, value.second);
  out << ')';
}

template <typename T>
void write_one(std::ostream& out, const T& value) {
  constexpr bool is_string = std::is_convertible_v<const T&, std::string_view>;
  if constexpr (print_is_range<T>::value && !is_string) {
    out << '[';
    bool first = true;
    for (const auto& element : value) {
      if (!first) out << ", ";
      first = false;
      write_one(out, element);
    }
    out << ']';
  } else {
    out << value;
  }
}

template <typename... Ts>
void write_many(std::ostream& out, Ts&&... xs) {
  if constexpr (sizeof...(Ts) > 0) {
    bool first = true;
    auto write = [&](auto&& x) {
      if (!first) out << ' ';
      first = false;
      write_one(out, x);
    };
    (write(std::forward<Ts>(xs)), ...);
  }
}

#if defined(__cpp_lib_print) && __cpp_lib_print >= 202207L
#define pr(...) std::print(__VA_ARGS__)
#define prln(...) std::println(__VA_ARGS__)
#else
template <typename... Ts>
void pr(Ts&&... xs) {
  write_many(std::cout, std::forward<Ts>(xs)...);
}

template <typename... Ts>
void prln(Ts&&... xs) {
  pr(std::forward<Ts>(xs)...);
  std::cout << '\n';
}
#endif

#ifdef LOCAL
template <typename... Ts>
void debug_write(Ts&&... xs) {
  write_many(std::cerr, std::forward<Ts>(xs)...);
}

template <typename... Ts>
void debug_writeln(Ts&&... xs) {
  debug_write(std::forward<Ts>(xs)...);
  std::cerr << '\n';
}

#define db(...) debug_write(__VA_ARGS__)
#define dbln(...) debug_writeln(__VA_ARGS__)
#else
#define db(...)
#define dbln(...)
#endif
// }}}

void solve() {
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
