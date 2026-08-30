#include <bits/stdc++.h>  // {{{

using namespace std;

template <typename T>
[[nodiscard]] static T MIN() {
  return std::numeric_limits<T>::min();
}

template <typename T>
[[nodiscard]] static T MAX() {
  return std::numeric_limits<T>::max();
}

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
using v = std::vector<T>;
template <typename T, size_t N>
using r = std::array<T, N>;
template <typename T1, typename T2>
using p = std::pair<T1, T2>;

#define ff first
#define ss second
#define eb emplace_back
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
//  }}}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// https://mirror.codeforces.com/blog/entry/124683

namespace hashing {
using i64 = std::int64_t;
using u64 = std::uint64_t;
static const u64 FIXED_RANDOM =
    std::chrono::steady_clock::now().time_since_epoch().count();

#if USE_AES
std::mt19937 rd(FIXED_RANDOM);
const __m128i KEY1{(i64)rd(), (i64)rd()};
const __m128i KEY2{(i64)rd(), (i64)rd()};
#endif

template <class T, class D = void>
struct custom_hash {};

template <class T>
inline void hash_combine(u64 &seed, T const &v) {
  custom_hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b97f4a7c15 + (seed << 12) + (seed >> 4);
};

template <class T>
struct custom_hash<T,
                   typename std::enable_if<std::is_integral<T>::value>::type> {
  u64 operator()(T _x) const {
    u64 x = _x;
#if USE_AES
    __m128i m{i64(u64(x) * 0xbf58476d1ce4e5b9u64), (i64)FIXED_RANDOM};
    __m128i y = _mm_aesenc_si128(m, KEY1);
    __m128i z = _mm_aesenc_si128(y, KEY2);
    return z[0];
#else
    x += 0x9e3779b97f4a7c15 + FIXED_RANDOM;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
#endif
  }
};

template <class T>
struct custom_hash<T, std::void_t<decltype(std::begin(std::declval<T>()))>> {
  u64 operator()(T const &a) const {
    u64 value = FIXED_RANDOM;
    for (auto &x : a)
      hash_combine(value, x);
    return value;
  }
};

template <class... T>
struct custom_hash<std::tuple<T...>> {
  u64 operator()(const std::tuple<T...> &a) const {
    u64 value = FIXED_RANDOM;
    std::apply(
        [&value](T const &...args) {
          (hash_combine(value, args), ...);
        },
        a);
    return value;
  }
};

template <class T, class U>
struct custom_hash<std::pair<T, U>> {
  u64 operator()(std::pair<T, U> const &a) const {
    u64 value = FIXED_RANDOM;
    hash_combine(value, a.first);
    hash_combine(value, a.second);
    return value;
  }
};
};  // namespace hashing

#ifdef PB_DS_ASSOC_CNTNR_HPP
template <class Key, class Value = null_type>
using hashtable = gp_hash_table<
    Key, Value, hashing::custom_hash<Key>, std::equal_to<Key>,
    direct_mask_range_hashing<>, linear_probe_fn<>,
    hash_standard_resize_policy<hash_exponential_size_policy<>,
                                hash_load_check_resize_trigger<>, true>>;

#endif
#ifdef PB_DS_TREE_POLICY_HPP
template <typename T>
using multitree = tree<T, null_type, std::less_equal<T>, rb_tree_tag,
                       tree_order_statistics_node_update>;
template <class Key, class Value = null_type>
using rbtree = tree<Key, Value, std::less<Key>, rb_tree_tag,
                    tree_order_statistics_node_update>;
#endif

void solve() {
  int n, q;
  cin >> n >> q;
  hashtable<int, int> id_to_salary;
  rbtree<p<int, int>> tree;

  int salary;
  for (int i = 0; i < n; ++i) {
    cin >> salary;
    id_to_salary[i] = salary;
    tree.insert({salary, i});
  }

  char cmd;
  int l, r, i;
  while (q--) {
    cin >> cmd;
    if (cmd == '?') {
      cin >> l >> r;
      int ans = tree.order_of_key({r + 1, 0}) - tree.order_of_key({l, 0});
      cout << ans << endl;
    } else {
      cin >> i >> salary;
      --i;
      tree.erase({id_to_salary[i], i});
      id_to_salary[i] = salary;
      tree.insert({salary, i});
    }
  }
}

int main() {  // {{{
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit);

  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
// }}}
