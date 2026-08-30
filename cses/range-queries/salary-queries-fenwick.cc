#include <bits/stdc++.h>  // {{{

using namespace std;

template <typename T>
[[nodiscard]] static T MIN() {
  return std::numeric_limits<T>::min();
}

template <typename T>
[[nodiscard]] static T MAX() {
  return std::numeric_limits<T>::max();
}

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
  explicit fenwick_tree(size_t n) : tree(n) {
  }

  T const query(int i) const {
    if (!(0 <= i && i < static_cast<int>(tree.size()))) {
      throw std::out_of_range("cannot query fenwick tree of size " +
                              std::to_string(tree.size()) + " at index " +
                              std::to_string(i));
    }

    T t = sentinel();

    for (int j = static_cast<int>(i); j >= 0; j = h(j) - 1) {
      t = merge(t, tree[j]);
    }

    return t;
  };

  T const query(int l, int r) const {
    if (!(0 <= l && l <= r && r < static_cast<int>(tree.size()))) {
      throw std::out_of_range(
          "cannot query fenwick tree of size " + std::to_string(tree.size()) +
          " at range [" + std::to_string(l) + ", " + std::to_string(r) + "]");
    }

    if (l == 0) {
      return query(r);
    }

    return unmerge(query(r), query(l - 1));
  };

  void update(int i, T const& t) noexcept {
    assert(0 <= i && i < static_cast<int>(tree.size()));

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

  [[nodiscard]] inline size_t h(size_t i) const noexcept {
    return i & (i + 1);
  }

  std::vector<T> tree;
};

void solve() {
  int n, q;
  cin >> n >> q;

  v<int> coordinates;

  v<ll> salaries(n);
  for (auto& salary : salaries) {
    cin >> salary;
    coordinates.eb(salary);
  }

  v<tuple<char, int, int>> queries;

  while (q--) {
    char cmd;
    int l, r;
    cin >> cmd >> l >> r;
    queries.eb(cmd, l, r);
    if (cmd == '?') {
      coordinates.eb(l);
    }
    coordinates.eb(r);
  }

  sort(all(coordinates));
  coordinates.erase(unique(all(coordinates)), coordinates.end());

  auto index = [&](int salary) {
    return distance(coordinates.begin(), lower_bound(all(coordinates), salary));
  };

  fenwick_tree<int> fw(coordinates.size());
  for (auto salary : salaries) {
    fw.update(index(salary), 1);
  }

  for (auto& [cmd, a, b] : queries) {
    if (cmd == '?') {
      cout << fw.query(index(a), index(b)) << endl;
    } else {
      fw.update(index(salaries[a - 1]), -1);
      salaries[a - 1] = b;
      fw.update(index(salaries[a - 1]), 1);
    }
  }
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit);

  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
// }}}
