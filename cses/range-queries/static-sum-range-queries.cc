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
struct fenwick_tree {
 public:
  explicit fenwick_tree(std::vector<T> const& ts) : tree(ts.size()) {
    for (size_t i = 0; i < ts.size(); ++i) {
      tree[i] = ts[i];
    }
    for (size_t i = 0; i < tree.size(); ++i) {
      size_t j = g(i);
      if (j < tree.size()) {
        tree[j] += tree[i];
      }
    }
  }

  T const query(size_t i) const {
    if (!(0 <= i && i < tree.size())) {
      throw std::out_of_range("fenwick tree index out of range");
    }

    T t = sentinel();

    for (int j = static_cast<int>(i); j >= 0; j = h(j) - 1) {
      t = merge(t, tree[j]);
    }

    return t;
  };

  T const query(size_t l, size_t r) const {
    if (!(0 <= l && r < tree.size())) {
      throw std::out_of_range("fenwick tree range out of range");
    }

    if (l == 0) {
      return query(r);
    }

    return unmerge(query(r), query(l - 1));
  };

  void update(size_t i, T const& t) noexcept {
    assert(0 <= i && t < tree.size());

    for (size_t j = i; j < tree.size(); j = g(j)) {
      tree[j] = merge(tree[j], t);
    }
  }

 private:
  [[nodiscard]] inline T merge(T const& x, T const& y) const noexcept {
    return x + y;
  }

  [[nodiscard]] inline T unmerge(T const& x, T const& y) const noexcept {
    return x - y;
  }

  [[nodiscard]] inline T sentinel() const noexcept {
    return 0;
  }

  [[nodiscard]] inline size_t g(size_t i) const noexcept {
    return i | (i + 1);
  }

  [[nodiscard]] size_t h(size_t i) const noexcept {
    return i & (i + 1);
  }

  std::vector<T> tree;
};

void solve() {
  int n, q;
  cin >> n >> q;
  v<ll> a(n);
  for (auto& e : a)
    cin >> e;
  fenwick_tree<ll> fw(a);
  while (q--) {
    ll l, r;
    cin >> l >> r;
    --l;
    --r;
    cout << fw.query(l, r) << endl;
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
