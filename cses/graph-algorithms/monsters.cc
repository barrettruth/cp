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

static map<char, pair<i32, i32>> dirs{
    {'R', {0, 1}}, {'L', {0, -1}}, {'D', {1, 0}}, {'U', {-1, 0}}};

void solve() {
  u32 n, m;
  cin >> n >> m;

  vec<string> graph(n);
  for (auto& e : graph)
    cin >> e;

  queue<pair<i32, i32>> mq, aq;

  u32 sr, sc;
  for (u32 r = 0; r < n; ++r) {
    for (u32 c = 0; c < m; ++c) {
      if (graph[r][c] == 'M') {
        mq.emplace(r, c);
        graph[r][c] = '#';
      } else if (graph[r][c] == 'A') {
        sr = r, sc = c;
        aq.emplace(r, c);
      }
    }
  }

  auto valid = [&n, &m](i32 r, i32 c) -> bool {
    return min(r, c) >= 0 && r < n && c < m;
  };

  vec<string> trace(n, string(m, ' '));
  auto print_trace = [&](i32 r, i32 c) -> void {
    vec<char> path;

    while (r != sr || c != sc) {
      path.push_back(trace[r][c]);
      auto dir = dirs.at(trace[r][c]);
      r -= dir.first;
      c -= dir.second;
    }

    reverse(all(path));
    cout << "YES\n" << path.size() << '\n';
    for (auto e : path)
      cout << e;
  };

  while (!aq.empty()) {
    u32 mcount = mq.size();
    for (u32 i = 0; i < mcount; ++i) {
      auto [r, c] = mq.front();
      mq.pop();

      for (auto& [_, dir] : dirs) {
        auto nr = r + dir.first, nc = c + dir.second;

        if (!valid(nr, nc) || graph[nr][nc] == '#') {
          continue;
        }

        graph[nr][nc] = '#';
        mq.emplace(nr, nc);
      }
    }

    u32 acount = aq.size();
    for (u32 i = 0; i < acount; ++i) {
      auto [r, c] = aq.front();
      aq.pop();

      if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
        print_trace(r, c);
        return;
      }

      for (auto& [letter, dir] : dirs) {
        auto nr = r + dir.first, nc = c + dir.second;

        if (!valid(nr, nc) || trace[nr][nc] != ' ' || graph[nr][nc] == '#') {
          continue;
        }

        trace[nr][nc] = letter;
        aq.emplace(nr, nc);
      }
    }
  }

  NO();
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
