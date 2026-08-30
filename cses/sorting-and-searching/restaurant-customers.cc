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

  vec<pair<int, int>> events(2 * n);

  for (int i = 0; i < 2 * n; i += 2) {
    int x;
    cin >> x;
    events[i] = {x, 1};
    cin >> x;
    events[i + 1] = {x, -1};
  }

  sort(all(events));

  ll ans = 0, cum = 0;

  for (auto& [i, e] : events) {
    cum += e;
    ans = max(ans, cum);
  }

  cout << ans << endl;
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);

  solve();

  return 0;
}
// }}}
