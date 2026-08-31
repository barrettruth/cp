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

struct Seg {
  i64 L, R, PL, PR;
  int type;   // 0=interior, 1=left-edge, 2=right-edge
  i64 pos, key;
};

static void eval(Seg& s) {
  if (s.type == 1) {
    s.pos = s.L;
    s.key = s.PL - s.pos;
  } else if (s.type == 2) {
    s.pos = s.R;
    s.key = s.pos - s.PR;
  } else {
    i64 m = (s.PL + s.PR) / 2;
    if (m < s.L) m = s.L;
    if (m > s.R) m = s.R;
    s.pos = m;
    s.key = min(s.pos - s.PL, s.PR - s.pos);
  }
  if (s.key < 0) s.key = 0;
}

struct Cmp {
  bool operator()(const Seg& a, const Seg& b) const { return a.key < b.key; }
};

void solve() {
  int n; i64 k, X;
  cin >> n >> k >> X;
  vector<i64> A(n);
  for (auto& e : A) cin >> e;
  sort(A.begin(), A.end());

  priority_queue<Seg, vector<Seg>, Cmp> pq;

  if (A[0] > 0) {
    Seg s{0, A[0] - 1, A[0], 0, 1, 0, 0};
    eval(s); pq.push(s);
  }
  for (int i = 0; i + 1 < n; ++i) {
    if (A[i] + 1 <= A[i + 1] - 1) {
      Seg s{A[i] + 1, A[i + 1] - 1, A[i], A[i + 1], 0, 0, 0};
      eval(s); pq.push(s);
    }
  }
  if (A.back() < X) {
    Seg s{A.back() + 1, X, 0, A.back(), 2, 0, 0};
    eval(s); pq.push(s);
  }

  i64 printed = 0;
  while (printed < k && !pq.empty()) {
    Seg s = pq.top(); pq.pop();
    cout << s.pos << (printed + 1 == k ? '\n' : ' ');
    ++printed;
    if (s.L <= s.pos - 1) {
      Seg Ls{s.L, s.pos - 1, s.PL, s.PR, s.type, 0, 0};
      eval(Ls); pq.push(Ls);
    }
    if (s.pos + 1 <= s.R) {
      Seg Rs{s.pos + 1, s.R, s.PL, s.PR, s.type, 0, 0};
      eval(Rs); pq.push(Rs);
    }
  }

  i64 last = LLONG_MIN;
  for (int i = 0; printed < k && i < n; ++i) {
    if (A[i] == last) continue;
    last = A[i];
    cout << A[i] << (printed + 1 == k ? '\n' : ' ');
    ++printed;
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
  u32 tc = 1;
  std::cin >> tc;
  for (u32 t = 0; t < tc; ++t) {
    solve();
  }
  return 0;
}
// }}}

// vim: foldmethod=marker foldlevel=0
