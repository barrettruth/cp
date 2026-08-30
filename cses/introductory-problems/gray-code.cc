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

vec<string> f(int n) {
  vec<string> gray{"0", "1"};

  while (--n) {
    vec<string> copy(gray);
    reverse(all(copy));
    gray.insert(gray.end(), all(copy));
    for (int i = 0; i < sz<int>(gray); ++i)
      gray[i].push_back('0' + (i >= sz<int>(gray) >> 1));
  }
  return gray;
}

void solve() {
  int n;
  cin >> n;

  vec<string> gray = f(n);
  for (auto s : gray) {
    cout << s << endl;
  }
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);

  solve();

  return 0;
}
// }}}
