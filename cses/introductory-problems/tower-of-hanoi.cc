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
  vec<pair<int, int>> ans;
  auto hanoi = [&](auto&& self, int src, int dest, int aux, int x) {
    if (x == 1) {
      ans.eb(src, dest);
      return;
    }
    self(self, src, aux, dest, x - 1);
    ans.eb(src, dest);
    self(self, aux, dest, src, x - 1);
  };
  hanoi(hanoi, 1, 3, 2, n);
  cout << ans.size() << endl;
  for (auto& [a, b] : ans) {
    cout << a << ' ' << b << endl;
  }
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);

  solve();

  return 0;
}
// }}}
