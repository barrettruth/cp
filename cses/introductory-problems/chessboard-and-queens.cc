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

constexpr static int N = 8;

vec<string> board(N);

// SC: O(n) for recursive space + queens
// TC: O(n*n*n) - every row every col check all queens

// NOTE: pruning
ll backtrack(vec<int> &queens) {
  if (queens.size() == N) {
    return 1;
  }

  ll r = queens.size();
  ll ans = 0;
  for (int C = 0; C < N; ++C) {
    if (board[r][C] == '*')
      continue;
    bool bad = false;
    for (int qr = 0; qr < sz<int>(queens); ++qr) {
      int qc = queens[qr];
      // Q: does it fall on the DIAGONAL?
      // for each line, is there an integer sol'n?
      // y - qr = x - qc -> x - qc + qr <- n queens
      // or y - qr = -x + qc -> y = -x + qc + qr
      if (qc == C || abs(r - qr) == abs(C - qc)) {
        bad = true;
        break;
      }
    }
    if (bad)
      continue;
    queens.eb(C);
    ans += backtrack(queens);
    queens.pop_back();
  }
  return ans;
}

void solve() {
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
  }

  vec<int> queens;
  ll ans = backtrack(queens);

  cout << ans << endl;
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);

  solve();

  return 0;
}
// }}}
