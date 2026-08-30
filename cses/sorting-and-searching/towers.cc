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

void solve() {
  int n;
  cin >> n;
  ve<int> cubes(n);
  for (auto& e : cubes)
    cin >> e;

  multiset<int> towers;
  /*
     tower only on smaller, minimize total
     <- stack highest possible

     a[i] >= a[i + 1] >= ...

     x > y
     x
     y

     stack blocks on the smallest accomodating block

     aka, for each cube, upper_bound it, and stack; if nothing, then add new
     tower

     3,2,1 8,5
NOTE: forgot that must be strictly greater

10 4 5 9 4 10 2 7 4 6

NOTE: didn't use multiset, + erasewd at *it instead of it
NOTE: didn't think explicitly about above example

if 10 and need to add 4, doing 10 4 vs 10,4 is the same
because  alarger number can either next be:

10,4 9 or 10,9 4 (NO DIFFFERENCE)
     */

  for (auto cube : cubes) {
    auto it = towers.upper_bound(cube);
    if (it != towers.end()) {
      towers.erase(it);
    }
    towers.insert(cube);
  }

  cout << towers.size() << endl;
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
