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
  string s;
  cin >> s;

  unordered_map<char, int> m;
  for (auto c : s)
    ++m[c];

  int odd = 0;

  string ans(s.size(), 'A');

  int l = 0;

  for (auto& [k, v] : m) {
    if (v & 1) {
      if (++odd == 2) {
        cout << "NO SOLUTION";
        return;
      }
      ans[ans.size() / 2] = k;
      --v;
    }
    while (v) {
      ans[l++] = k;
      ans[ans.size() - l] = k;
      v -= 2;
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
