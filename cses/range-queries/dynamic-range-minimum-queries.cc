#include <bits/stdc++.h>  // {{{

using namespace std;

template <typename T>
constexpr T MIN = std::numeric_limits<T>::min();

template <typename T>
constexpr T MAX = std::numeric_limits<T>::max();

template <typename T, typename U>
[[nodiscard]] static T sc(U&& x) {
  return static_cast<T>(x);
}

template <typename T, typename U>
[[nodiscard]] static T sz(U&& x) {
  return static_cast<T>(x.size());
}

using ll = long long;
using ld = long double;
template <typename T>
using v = std::vector<T>;
template <typename T, size_t N>
using r = std::array<T, N>;
template <typename T1, typename T2>
using p = std::pair<T1, T2>;

#define ff first
#define ss second
#define eb emplace_back
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
//  }}}

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

 private:
  inline T const sentinel() const noexcept {
    return MAX<T>;
  }

  inline T const merge(T const& x, T const& y) const noexcept {
    return min(x, y);
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

  size_t n;
  std::vector<T> tree;
};

void solve() {
  int n, q;
  cin >> n >> q;
  v<ll> a(n);
  for (auto& e : a) {
    cin >> e;
  }
  segment_tree<ll> st(a);

  while (q--) {
    char cmd;
    cin >> cmd;
    if (cmd == '1') {
      int i;
      ll u;
      cin >> i >> u;
      --i;
      st.update(i, u);
      a[i] = u;
    } else {
      int l, r;
      cin >> l >> r;
      --l;
      --r;
      cout << st.query(l, r) << endl;
    }
  }
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
// }}}
