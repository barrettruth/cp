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
struct sparse_table {
  sparse_table(std::vector<T> const& ts)
      : table(floor(__lg(max(1, static_cast<int>(ts.size())))) + 1,
              std::vector<T>(ts.size())) {
    for (size_t i = 0; i < ts.size(); ++i) {
      table[0][i] = ts[i];
    }

    for (size_t j = 1; j < table.size(); ++j) {
      for (size_t i = 0; i + (1 << (j - 1)) < ts.size(); ++i) {
        table[j][i] = merge(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  [[nodiscard]] T query(size_t const l, size_t const r) const {
    if (!(0 <= l && r < table[0].size())) {
      return 0;
    }

    int k = floor(__lg(r - l + 1));
    return merge(table[k][l], table[k][r - (1 << k) + 1]);
  }

 private:
  [[nodiscard]] inline T merge(T const& x, T const& y) const noexcept {
    return min(x, y);
  }

  std::vector<std::vector<T>> table;
};

void solve() {
  int n, q;
  cin >> n >> q;
  v<ll> a(n);
  for (auto& e : a)
    cin >> e;
  sparse_table<ll> st(a);
  while (q--) {
    int l, r;
    cin >> l >> r;
    --l;
    --r;
    cout << st.query(l, r) << endl;
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
