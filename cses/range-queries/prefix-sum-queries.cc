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

void solve() {
  int n, q;
  cin >> n >> q;
  v<ll> a(n);
  for (auto& e : a) {
    cin >> e;
  }

  /*
     max prefix sum in range: segtree max()

update: prefixes @ and after change

have various prefix sums, and various deltas

[p1, p2, p3, p4, p5, p6]
[0, 1, -1, 2, -5, 3]

construct segtree: RMaxQ
update: everything after [a,] += delta
     */

  while (q--) {
    char cmd;
    cin >> cmd;
    int i, l, r;
    ll u;
    if (cmd == '1') {
      cin >> i >> u;
    } else {
      cin >> l >> r;
      --l;
      --r;
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
