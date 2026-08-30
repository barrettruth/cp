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
  u32 n, m;
  cin >> n >> m;
  vec<i64> a(n);
  for (auto& e : a)
    cin >> e;

  vec<i64> prev(m + 1, 0);
  if (a[0] != 0) {
    prev[a[0]] = 1;
  } else {
    for (u32 i = 1; i <= m; ++i)
      prev[i] = 1;
  }

  for (u32 i = 2; i <= n; ++i) {
    vec<i64> cur(m + 1, 0);
    if (a[i - 1] == 0) {
      for (u32 x = 1; x <= m; ++x) {
        for (i64 delta = -1; delta <= 1; ++delta) {
          if (1 <= x + delta && x + delta <= m)
            cur[x] = (cur[x] + prev[x + delta]) % MOD;
        }
      }
    } else {
      for (i64 delta = -1; delta <= 1; ++delta) {
        if (1 <= a[i - 1] + delta && a[i - 1] + delta <= m)
          cur[a[i - 1]] = (cur[a[i - 1]] + prev[a[i - 1] + delta]) % MOD;
      }
    }
    prev = cur;
  }

  i64 ans = 0;
  for (auto e : prev) {
    ans = (ans + e) % MOD;
  }
  cout << ans << '\n';
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
