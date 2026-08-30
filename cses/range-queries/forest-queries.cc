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

void solve() {
  int n, q;
  cin >> n >> q;
  v<string> grid(n);
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
  }

  v<v<int>> prefix(n + 1, v<int>(n + 1, 0));

  for (int i = 0; i < n; ++i) {
    prefix[1][i + 1] = prefix[1][i] + (grid[0][i] == '*');
  }

  for (int i = 1; i < n; ++i) {
    prefix[i + 1][1] = prefix[i][1] + (grid[i][0] == '*');
    for (int j = 1; j < n; ++j) {
      prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] -
                             prefix[i][j] + (grid[i][j] == '*');
    }
  }

  while (q--) {
    int y1, x1, y2, x2;
    cin >> y1 >> x1 >> y2 >> x2;
    cout << prefix[y2][x2] - prefix[y2][x1 - 1] - prefix[y1 - 1][x2] +
                prefix[y1 - 1][x1 - 1]
         << endl;
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
