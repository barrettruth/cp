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

void solve() {
  u64 n, x;
  cin >> n >> x;
  vec<u64> c(n);

  for (auto& e : c)
    cin >> e;
  sort(all(c));

  vec<i64> make(x + 1, MAX<i64>);
  make[0] = 0;

  for (u64 i = 1; i <= x; ++i) {
    for (u32 j = 0; j < n && c[j] <= i; ++j) {
      if (make[i - c[j]] != MAX<i64>)
        make[i] = min(make[i], 1 + make[i - c[j]]);
    }
  }

  if (make[x] == MAX<i64>) {
    cout << "-1\n";
  } else {
    cout << make[x] << '\n';
  }
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
