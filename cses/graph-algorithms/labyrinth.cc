#include <bits/stdc++.h>  // {{{

using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double;
using f128 = long double;

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

template <typename T>
using vec = std::vector<T>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define ff first
#define ss second

//  }}}

unordered_map<char, pair<i32, i32>> dirs{
    {'L', {0, -1}}, {'R', {0, 1}}, {'U', {-1, 0}}, {'D', {1, 0}}};

void solve() {
  u32 n, m;
  cin >> n >> m;

  vec<string> grid(n);
  for (auto& e : grid)
    cin >> e;

  i32 sr, sc, er, ec;
  for (u32 r = 0; r < n; ++r) {
    for (u32 c = 0; c < m; ++c) {
      if (grid[r][c] == 'A') {
        sr = r;
        sc = c;
      } else if (grid[r][c] == 'B') {
        er = r;
        ec = c;
      }
    }
  }

  queue<pair<i32, i32>> q{{{sr, sc}}};
  vec<string> trace(n, string(m, ' '));

  auto print_trace = [&]() mutable -> void {
    string ans;
    i32 row = er, col = ec;

    while (grid[row][col] != 'A') {
      char step = trace[row][col];
      ans.push_back(step);
      row -= dirs.at(step).first;
      col -= dirs.at(step).second;
    }

    reverse(all(ans));
    cout << ans.size() << '\n' << ans << '\n';
  };

  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();

    if (r == er && c == ec) {
      cout << "YES\n";
      print_trace();
      return;
    }

    for (auto& [letter, dir] : dirs) {
      auto& [dr, dc] = dir;
      i32 nr = r + dr;
      i32 nc = c + dc;

      if (min(nr, nc) < 0 || nr >= n || nc >= m || grid[nr][nc] == '#' ||
          trace[nr][nc] != ' ') {
        continue;
      }

      trace[nr][nc] = letter;
      q.emplace(nr, nc);
    }
  }

  cout << "NO\n";
}

int main() {  // {{{
  std::cin.exceptions(std::cin.failbit);

#ifdef LOCAL
  std::cerr.rdbuf(std::cout.rdbuf());
  std::cout.setf(std::ios::unitbuf);
  std::cerr.setf(std::ios::unitbuf);
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  u32 tc = 1;
  // std::cin >> tc;

  for (u32 t = 0; t < tc; ++t) {
    solve();
  }

  return 0;
}
// }}}
