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

void backtrack(vec<int>& freq, string& cur, vector<string>& ans, int len) {
  if (sz<int>(cur) == len) {
    ans.eb(cur);
    return;
  }
  for (int i = 0; i < sz<int>(freq); ++i) {
    if (freq[i] == 0)
      continue;

    --freq[i];

    cur.push_back(i + 'a');
    backtrack(freq, cur, ans, len);
    cur.pop_back();

    ++freq[i];
  }
}

void solve() {
  string s;
  cin >> s;

  vec<int> m(26, 0);
  int len = s.size();
  for (auto c : s)
    ++m[c - 'a'];

  string cur = "";
  vec<string> ans;
  backtrack(m, cur, ans, len);
  cout << ans.size() << endl;
  for (auto& S : ans) {
    cout << S << endl;
  }
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);

  solve();

  return 0;
}
// }}}
