#include <bits/stdc++.h>  // {{{

using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using d64 = double;
using d128 = long double;
template <typename T>
using vec = std::vector<T>;
template <typename T, size_t N>
using arr = std::array<T, N>;
template <typename T1, typename T2>
using pai = std::pair<T1, T2>;

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

static void NO() {
  std::cout << "NO\n";
}

static void YES() {
  std::cout << "YES\n";
}

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

//  }}}

static constexpr u64 MOD = 1e9 + 7;

void solve() {
  u64 n;
  cin >> n;
  vec<string> board(n);
  for (auto& e : board)
    cin >> e;

  vec<u64> moves(n + 1, 0);
  moves[1] = board[0][0] == '.';

  for (u64 r = 1; r <= n; ++r) {
    for (u64 c = 1; c <= n; ++c) {
      if (board[r - 1][c - 1] == '*') {
        moves[c] = 0;
      } else {
        moves[c] = (moves[c - 1] + moves[c]) % MOD;
      }
    }
  }

  cout << moves[n] << '\n';
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit);

  int tc = 1;
  // cin >> tc;

  for (int t = 0; t < tc; ++t) {
    solve();
  }

  return 0;
}
// }}}
