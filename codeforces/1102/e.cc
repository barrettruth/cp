#include <bits/stdc++.h>  // {{{

#include <version>
#ifdef __cpp_lib_ranges_enumerate
#include <ranges>
namespace rv = std::views;
namespace rs = std::ranges;
#endif

#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double;
using f128 = long double;

#if __cplusplus >= 202002L
template <typename T>
constexpr T MIN = std::numeric_limits<T>::min();

template <typename T>
constexpr T MAX = std::numeric_limits<T>::max();
#endif

#ifdef LOCAL
#define db(...) std::print(__VA_ARGS__)
#define dbln(...) std::println(__VA_ARGS__)
#else
#define db(...)
#define dbln(...)
#endif
//  }}}

constexpr i64 mod = 1'000'000'007;

vector<i64> fac;
vector<i64> inv;

i64 pw(i64 a, i64 e) {
  i64 r = 1;
  while (e) {
    if (e & 1) {
      r = r * a % mod;
    }
    a = a * a % mod;
    e >>= 1;
  }
  return r;
}

void init(i32 n) {
  fac.assign(n + 1, 1);
  inv.assign(n + 1, 1);
  for (i32 i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
  }
  inv[n] = pw(fac[n], mod - 2);
  for (i32 i = n; i > 0; --i) {
    inv[i - 1] = inv[i] * i % mod;
  }
}

i64 comb(i32 n, i32 k) {
  if (k < 0 || k > n) {
    return 0;
  }
  return fac[n] * inv[k] % mod * inv[n - k] % mod;
}

void solve() {
  i32 n;
  cin >> n;
  vector<i64> a(n + 1);
  for (i32 i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  i64 ans = 1;
  bool ok = true;
  vector<pair<i32, i32>> st{{1, n}};
  while (!st.empty() && ok) {
    auto [l, r] = st.back();
    st.pop_back();

    i32 root = 0;
    i32 x = l;
    i32 y = r;
    while (x <= y) {
      i64 lef = x - l + 1;
      i64 rig = r - x + 1;
      if (a[x] == lef * rig) {
        root = x;
        break;
      }
      if (x == y) {
        break;
      }
      lef = y - l + 1;
      rig = r - y + 1;
      if (a[y] == lef * rig) {
        root = y;
        break;
      }
      ++x;
      --y;
    }

    if (root == 0) {
      ok = false;
      break;
    }

    i32 len = r - l + 1;
    i32 cnt = root - l;
    ans = ans * comb(len - 1, cnt) % mod;
    if (l < root) {
      st.emplace_back(l, root - 1);
    }
    if (root < r) {
      st.emplace_back(root + 1, r);
    }
  }

  cout << (ok ? ans : 0) << '\n';
}

int main() {  // {{{
  init(500000);
  std::cin.exceptions(std::cin.failbit);
#ifdef LOCAL
  std::cerr.rdbuf(std::cout.rdbuf());
  std::cout.setf(std::ios::unitbuf);
  std::cerr.setf(std::ios::unitbuf);
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif
  u32 tc = 1;
  std::cin >> tc;
  for (u32 t = 0; t < tc; ++t) {
    solve();
  }
  return 0;
}  // }}}
