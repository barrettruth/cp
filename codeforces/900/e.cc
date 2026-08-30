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

template <typename T>
struct segment_tree {
 public:
  explicit segment_tree(std::vector<T> const& ts) : n(ts.size()) {
    tree.resize(4 * n);
    build(1, 0, n - 1, ts);
  }

  [[nodiscard]] T const query(int const l, int const r) const {
    if (!(0 <= l && l <= r && r < static_cast<int>(n))) {
      throw std::out_of_range(
          "cannot query segment tree of size " + std::to_string(n) +
          " at range [" + std::to_string(l) + ", " + std::to_string(r) + "]");
    }

    return query(1, 0, n - 1, l, r);
  }

  void update(int i, T const& t) {
    if (!(0 <= i && i < static_cast<int>(n))) {
      throw std::out_of_range("cannot update segment tree of size " +
                              std::to_string(n) + " at index " +
                              std::to_string(i));
    }

    update(1, 0, n - 1, i, t);
  }

  [[nodiscard]] size_t lower_bound(T const& t) const noexcept {
    return lower_bound(1, 0, n - 1, t);
  }

  [[nodiscard]] size_t upper_bound(T const& t) const noexcept {
    return upper_bound(1, 0, n - 1, t);
  }

 private:
  inline T const sentinel() const noexcept {
    return -1LL;
  }

  inline T const merge(T const& x, T const& y) const noexcept {
    return x & y;
  }

  void build(size_t const node, size_t const l, size_t const r,
             std::vector<T> const& ts) noexcept {
    if (l == r) {
      tree[node] = ts[l];
    } else {
      int m = l + (r - l) / 2;
      build(2 * node, l, m, ts);
      build(2 * node + 1, m + 1, r, ts);
      tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
  }

  [[nodiscard]] T query(size_t const node, size_t const lower,
                        size_t const upper, size_t const l,
                        size_t const r) const noexcept {
    if (upper < l || r < lower) {
      return sentinel();
    }

    if (l <= lower && upper <= r) {
      return tree[node];
    }

    size_t m = lower + (upper - lower) / 2;

    return merge(query(2 * node, lower, m, l, r),
                 query(2 * node + 1, m + 1, upper, l, r));
  }

  void update(size_t const node, size_t const l, size_t const r, size_t const i,
              T const& t) noexcept {
    if (l == r) {
      tree[node] = t;
    } else {
      size_t m = l + (r - l) / 2;
      if (i <= m) {
        update(2 * node, l, m, i, t);
      } else {
        update(2 * node + 1, m + 1, r, i, t);
      }
      tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
  }

  [[nodiscard]] size_t lower_bound(size_t const node, size_t const l,
                                   size_t const r, T const& t) const noexcept {
    if (l == r) {
      return tree[node] >= t ? l : n;
    }

    size_t m = l + (r - l) / 2;
    if (tree[2 * node] >= t) {
      size_t res = lower_bound(2 * node, l, m, t);
      if (res < n)
        return res;
    }

    return lower_bound(2 * node + 1, m + 1, r, t);
  }

  [[nodiscard]] size_t upper_bound(size_t const node, size_t const l,
                                   size_t const r, T const& t) const noexcept {
    if (l == r) {
      return tree[node] > t ? l : n;
    }

    size_t m = l + (r - l) / 2;
    if (tree[2 * node] > t) {
      size_t res = upper_bound(2 * node, l, m, t);
      if (res < n)
        return res;
    }

    return upper_bound(2 * node + 1, m + 1, r, t);
  }

  size_t n;
  std::vector<T> tree;
};

void solve() {
  int n;
  cin >> n;
  vec<i64> a(n);
  for (auto& e : a)
    cin >> e;
  segment_tree<i64> st(a);
  int q;
  cin >> q;
  int L;
  i64 k;
  while (q--) {
    cin >> L >> k;
    --L;
    int l = L;
    int r = n - 1;

    while (l <= r) {
      int m = l + (r - l) / 2;

      if (st.query(L, m) >= k) {
        l = m + 1;
      } else {
        r = m - 1;
      }
    }

    // NOTE: messed up invalid queries, was confused
    // minor details of algorithms still cofnuse
    if (r < L)
      pr("-1 ");
    else
      pr("{} ", r + 1);

    // NOTE: would like to be able to use builtin lower bound but knowledge not
    // good enough
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
