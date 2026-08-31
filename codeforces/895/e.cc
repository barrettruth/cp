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

#include <stdexcept>
#include <vector>

template <typename T>
class segment_tree {
 public:
  explicit segment_tree(std::vector<T> const& data)
      : n(data.size()), tree(2 * n, sentinel()), lazy(n, sentinel()) {
    for (size_t i = 0; i < n; ++i)
      tree[i + n] = data[i];
    for (int i = n - 1; i > 0; --i)
      tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
  }

  void update(int l, int r, T const& t) noexcept {
    l += n, r += n + 1;
    push(l);
    push(r - 1);
    for (int L = l, R = r; L < R; L /= 2, R /= 2) {
      if (L & 1)
        apply(L++, t);
      if (R & 1)
        apply(--R, t);
    }
    for (l /= 2; l; l /= 2)
      tree[l] = merge(tree[l * 2], tree[l * 2 + 1]);
    for (r = (r - 1) / 2; r; r /= 2)
      tree[r] = merge(tree[r * 2], tree[r * 2 + 1]);
  }

  [[nodiscard]] T query(int l, int r) noexcept {
    l += n, r += n + 1;
    push(l);
    push(r - 1);
    T left = sentinel(), right = sentinel();
    for (; l < r; l /= 2, r /= 2) {
      if (l & 1)
        left = merge(left, tree[l++]);
      if (r & 1)
        right = merge(tree[--r], right);
    }
    return merge(left, right);
  }

 private:
  int n;
  std::vector<T> tree, lazy;

  [[nodiscard]] T merge(T const& a, T const& b) const {
    return a ^ b;
  }

  [[nodiscard]] inline T do_apply(T const& a, T const& b) const {
    return a & b;
  }

  [[nodiscard]] T sentinel() const {
    return 0;
  }

  void push(int i) {
    for (int h = __builtin_clz(n) - __builtin_clz(i); h > 0; --h) {
      int p = i >> h;
      if (lazy[p] != sentinel()) {
        apply(p * 2, lazy[p]);
        apply(p * 2 + 1, lazy[p]);
        lazy[p] = sentinel();
      }
    }
  }

  void apply(int i, T const& t) {
    tree[i] = do_apply(tree[i], t);
    if (i < n)
      lazy[i] = do_apply(lazy[i], t);
  }
};

void solve() {
  int n;
  cin >> n;
  vec<i64> a(n), prefix(n + 1, 0);
  for (auto& e : a) {
    cin >> e;
  }
  string s;
  cin >> s;

  arr<i64, 2> group{};
  for (int i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i] ^ a[i];
    group[s[i] - '0'] ^= a[i];
  }

  int q;
  cin >> q;
  int cmd, l, r, g;
  while (q--) {
    cin >> cmd;
    if (cmd == 1) {
      cin >> l >> r;
      --l;
      i64 range = prefix[r] ^ prefix[l];
      group[0] ^= range;
      group[1] ^= range;
    } else {
      cin >> g;
      pr("{} ", group[g]);
    }
  }
  prln();
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
