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
  ll n, m, k;
  cin >> n >> m >> k;
  vec<ll> requests(n);
  for (auto& e : requests)
    cin >> e;
  vec<ll> sizes(m);
  for (auto& e : sizes)
    cin >> e;
  sort(all(requests));
  sort(all(sizes));

  ll ans = 0;
  int size = 0;
  for (int request = 0; request < n && size < m; ++request) {
    while (size < m && sizes[size] + k < requests[request]) {
      ++size;
    }
    if (sizes[size] - k <= requests[request] &&
        requests[request] <= sizes[size] + k) {
      ++ans;
      ++size;
    }
  }
  cout << ans << endl;
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);

  solve();

  return 0;
}
// }}}
