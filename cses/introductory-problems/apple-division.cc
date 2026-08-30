#include <bits/stdc++.h>  // {{{

using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double;
using f128 = long double;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define ff first
#define ss second

//  }}}

void solve() {
  u32 n;
  cin >> n;
  vector<u64> a(n);
  for (auto& e : a)
    cin >> e;

  // auto dfs = [&](u32 i, u64 s1, auto&& self) -> u64 {
  //   if (i == n) {
  //     return max(s1, s2) - min(s1, s2);
  //   }
  //
  //   return min(self(i + 1, s1 + a[i], self),
  //              self(i + 1, s1,self));
  // };
  //
  // cout << dfs(0, 0, dfs) << '\n';

  u64 total = accumulate(all(a), 0LL);
  u64 ans = total;
  for (u64 mask = 0; mask < (1LL << n); ++mask) {
    u64 sum = 0;
    for (u64 bit = 0; bit < n; ++bit) {
      if (mask & (1LL << bit)) {
        sum += a[bit];
      }
    }
    ans = min(ans, max(total - sum, sum) - min(total - sum, sum));
  }
  cout << ans << '\n';
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit);

  u32 tc = 1;
  // cin >> tc;

  for (u32 t = 0; t < tc; ++t) {
    solve();
  }

  return 0;
}
// }}}
