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
using vec = std::vector<T>;
template <typename T, size_t N>
using arr = std::array<T, N>;

#define ff first
#define ss second
#define eb emplace_back
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
//  }}}

void solve() {
  int q;
  cin >> q;
  while (q--) {
    ll k;
    cin >> k;
    if (k <= 9) {
      cout << k << endl;
      continue;
    }

    ll exp = 1;
    while (true) {
      ll numbers_in_band = 9 * powl(10, exp - 1);
      ll per = numbers_in_band * exp;

      if (k <= per)
        break;

      k -= per;
      exp++;
    }

    ll i = (k - 1) / exp;
    ll index = k % exp;
    if (index == 0)
      index = exp;
    ll ans = powl(10, exp - 1) + i;
    ll offset = exp - index;
    while (offset--) {
      ans /= 10;
    }

    cout << ans % 10 << endl;
  }
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);

  solve();

  return 0;
}
// }}}
