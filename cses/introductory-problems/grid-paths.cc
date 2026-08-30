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

bitset<7 * 7 + 1> seen;

vec<pair<int, int>> dirs;
unordered_map<char, pair<int, int>> dir_map{
    {'U', {-1, 0}}, {'D', {1, 0}}, {'L', {0, -1}}, {'R', {0, 1}}};

ll ans = 0;

string s;

void dfs(int r, int c, int i) {
  if (min(r, c) < 0 || max(r, c) > 6 || seen[r * 7 + c]) {
    return;
  }
  if (r == 6 && c == 0) {
    ans += i == 48;
    return;
  }
  seen[r * 7 + c] = true;
  bool up = (r > 0 && !seen[(r - 1) * 7 + c]);
  bool down = (r < 6 && !seen[(r + 1) * 7 + c]);
  bool left = (c > 0 && !seen[r * 7 + (c - 1)]);
  bool right = (c < 6 && !seen[r * 7 + (c + 1)]);

  if ((up && down && !left && !right) || (!up && !down && left && right)) {
    seen[r * 7 + c] = false;
    return;
  }
  int open_count = up + down + left + right;
    if (open_count == 1) {
        if (up) dfs(r - 1, c, i + 1);
        else if (down) dfs(r + 1, c, i + 1);
        else if (left) dfs(r, c - 1, i + 1);
        else if (right) dfs(r, c + 1, i + 1);
        
        seen[r * 7 + c] = false;
        return;
    }
  if (s[i] == '?') {
    for (auto& [dr, dc] : dirs) {
      dfs(r + dr, c + dc, i + 1);
    }
  } else {
    dfs(r + dir_map[s[i]].ff, c + dir_map[s[i]].ss, i + 1);
  }
  seen[r * 7 + c] = false;
}

void solve() {
  dirs.eb(1, 0);
  dirs.eb(0, 1);
  dirs.eb(-1, 0);
  dirs.eb(0, -1);
  cin >> s;

  dfs(0, 0, 0);

  cout << ans << endl;
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);

  solve();

  return 0;
}
// }}}
