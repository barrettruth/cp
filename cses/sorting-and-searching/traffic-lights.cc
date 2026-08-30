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
using ve = std::vector<T>;
template <typename T, size_t N>
using ar = std::array<T, N>;
template <typename T1, typename T2>
using pa = std::pair<T1, T2>;
template <typename... Ts>
using tu = std::tuple<Ts...>;
template <typename... Ts>
using dq = std::deque<Ts...>;
template <typename... Ts>
using qu = std::queue<Ts...>;
template <typename... Ts>
using pq = std::priority_queue<Ts...>;
template <typename... Ts>
using st = std::stack<Ts...>;

#define ff first
#define ss second
#define eb emplace_back
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
//  }}}

// NOTE: i'm getting to the point where more complex dsa
// indeed may be needed
// I faded out like "no, no way i need two DSA", even though
// a) that would def work, might as well

// NOTE: do not know the apis

void solve() {
  int n, q;
  cin >> n >> q;

  ve<int> lights(q);
  set<int> pts{0, n};
  for (auto& e : lights) {
    cin >> e;
    pts.insert(e);
  }

  // NOTE: this was horrible
  int maximum = 0;
  int last = 0;
  for (int x : pts) {
    maximum = max(maximum, x - last);
    last = x;
  }

  ve<int> ans(q, 0);
  ans[q - 1] = maximum;
  for (int i = q - 1; i > 0; --i) {
    pts.erase(lights[i]);
    auto it = pts.upper_bound(lights[i]);
    int high = *it;
    int low = *(--it);
    maximum = max(maximum, high - low);
    ans[i - 1] = maximum;
  }

  for (int i = 0; i < q - 1; ++i)
    cout << ans[i] << ' ';
  cout << ans[q - 1];

  // set<int> lights{0, n};
  // multiset<int> segments{n};
  // int light;
  // while (q--) {
  //   cin >> light;
  //
  //   auto upper = lights.upper_bound(light);
  //   auto lower = upper;
  //   --lower;
  //
  //   segments.erase(segments.find(*upper - *lower));
  //
  //   segments.insert(*upper - light);
  //   segments.insert(light - *lower);
  //
  //   lights.insert(light);
  //
  //   cout << *segments.rbegin() << endl;
  // }
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
