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
  int n;
  cin >> n;
  /*
     n= 5;
     1 4 2 5 3
     1 4 2 5 3 6
     1 7 2 6 3 5 4

     41325
     */

  if (n == 1) {
    cout << 1 << endl;
  } else if (n <= 3) {
    cout << "NO SOLUTION\n";
  } else {
    for (int cur = n & 1 ? n - 1 : n; cur > 4; cur -= 2) {
      cout << cur << ' ';
    }
    cout << "2 4";
    for (int cur = 1; cur <= n; cur += 2) {
      cout << ' ' << cur;
    }
  }
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);

  solve();

  return 0;
}
// }}}
