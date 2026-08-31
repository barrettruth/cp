#include <bits/stdc++.h> // {{{

#if __cplusplus >= 202002L && defined(__cpp_lib_ranges)
namespace rng = std::ranges;
namespace rv = rng::views;
#endif

template <typename T>
using vec = std::vector<T>;

template <typename T, std::size_t N>
using arr = std::array<T, N>;

template <typename T, typename C = std::less<T>>
using pq = std::priority_queue<T, std::vector<T>, C>;

template <typename T, typename C = std::less<T>>
using mset = std::multiset<T, C>;

template <typename T, typename H = std::hash<T>>
using uset = std::unordered_set<T, H>;

template <typename K, typename V, typename H = std::hash<K>>
using umap = std::unordered_map<K, V, H>;

template <typename T>
using cvrefless_t = std::remove_cv_t<std::remove_reference_t<T>>;

template <typename T, typename U, typename... Ts>
[[nodiscard]] constexpr auto min(T&& x, U&& y, Ts&&... xs) {
  using R = std::common_type_t<cvrefless_t<T>, cvrefless_t<U>, cvrefless_t<Ts>...>;
  const std::initializer_list<R> values{
      static_cast<R>(std::forward<T>(x)), static_cast<R>(std::forward<U>(y)),
      static_cast<R>(std::forward<Ts>(xs))...};
  return std::min(values);
}

template <typename T, typename U, typename... Ts>
[[nodiscard]] constexpr auto max(T&& x, U&& y, Ts&&... xs) {
  using R = std::common_type_t<cvrefless_t<T>, cvrefless_t<U>, cvrefless_t<Ts>...>;
  const std::initializer_list<R> values{
      static_cast<R>(std::forward<T>(x)), static_cast<R>(std::forward<U>(y)),
      static_cast<R>(std::forward<Ts>(xs))...};
  return std::max(values);
}

using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double;
using f128 = long double;

template <typename T>
constexpr T MIN = std::numeric_limits<T>::lowest();

template <typename T>
constexpr T MAX = std::numeric_limits<T>::max();

void YES() { std::cout << "YES\n"; }
void Yes() { std::cout << "Yes\n"; }
void yes() { std::cout << "yes\n"; }
void NO() { std::cout << "NO\n"; }
void No() { std::cout << "No\n"; }
void no() { std::cout << "no\n"; }

#if defined(__cpp_lib_print) && __cpp_lib_print >= 202207L
#define pr(...) std::print(__VA_ARGS__)
#define prln(...) std::println(__VA_ARGS__)
#endif
// }}}

void solve() {
  /*
     i=0->n, # opers (-1 if no)
 
 
     when impossible? mex MEX, cannot form 0, 1, 2, ... MEX - 1
 
     consider bf, needing to form mex MEX
     need MEX - 1 - take if there
     ow, need i; take from largest candidate x, i - x "pull" it up, b/c closest
 
     continue repeatedly - if not there, return -1
 
     for all n, n^2 bf
 
     is there a recursive structure?
 
     say i pull up for mex MEX, does this help with MEX + 1
     what's the challenge - pulling up to MEX, may need to pull up to MEX - 1,
etc. then the gap eventually filled (if solution)
 
     idea, as go L->R, pull up minimal for answer -> making 0->MEX; also pull up
 
     observation - say missing for mex MEX, need to poull up - repeatedly
hoisting each, to push up is same as pulling up from closest gap index; keep
track of gap indices, and pull from closest one?
 
     but is puling from closets optimal? -> yes, it is
 
     narrow down in on this
 
     also, you have to push elements away - i.e., for each element equal to the
mex, + 1 is the "extra" count
 
     so, for mex M; push freq[m] first
     then, pull for M - 1, and take max free unused #, M - it, + 1 to the prev
score (excluding the M count there)
 
subtleties: the equal count - if matching MEX - 1 required pushing, we don't
need to (we can ignore count) really, we just care about pulled for each in our
dependent calculations
 
let's be concrete
 
mex MEX, solved 0->MEX - 1
 
- sort a increasingly, and for each mex
1. push off ==MEX values
2. define pull[mex] as total cost of pulling to make 0->mex-1
   - if no pull[MEX-1], -1
   - else,
     pull from largest available value, adding MEX - 1 - value
        - pop used value
     push self
 
great, now, impl
 
we iter over array and mex from 0 to n - which order?
def iter over mex, then have freq map + available

AFTER: so many mistakes

only push f-1 elems, using 64-bit types, ease of implementation, breaking loop, using accumulator instead of deriving, etc.
     */
  u64 n;
  cin >> n;
  vec<i64> a(n);
  map<i64, i64> f;
  for (auto& e : a) {
    cin >> e;
    ++f[e];
  }

  vec<i64> available;
  vec<i64> ans(n + 1, -1);

  ans[0] = f[0];
  for (i64 i = 0; i < max((i64)0, f[0] - 1); ++i)
    available.push_back(0);

  for (i64 mex = 1; mex <= (i64)n; ++mex) {
    ans[mex] = ans[mex - 1] - f[mex - 1] + f[mex];

    if (f[mex - 1] == 0) {
      if (available.empty()) {
        ans[mex] = -1;
        break;
      }
      ans[mex] += (mex - 1 - available.back());
      available.pop_back();
    }

    for (i64 i = 0; i < max((i64)0, f[mex] - 1); ++i)
      available.push_back(mex);
  }

  for (u64 i = 0; i <= n; ++i)
    cout << ans[i] << " \n"[i == n];
}

int main() { // {{{
  std::cin.exceptions(std::cin.failbit);
#ifdef LOCAL
  std::cerr.rdbuf(std::cout.rdbuf());
  std::cout.setf(std::ios::unitbuf);
  std::cerr.setf(std::ios::unitbuf);
#else
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  u32 tc = 1;
  std::cin >> tc;
  for (u32 t = 0; t < tc; ++t) {
    solve();
  }
  return 0;
}
// }}}

// vim: foldmethod=marker foldlevel=0
