/**
 * Author: C0ldSmi1e
 * Created Time: 02/06/2024 08:07:40 AM
**/

// time-limit: 5000
// problem-url: https://codeforces.com/contest/1927/problem/D
#include <bits/stdc++.h>

using namespace std;

#ifdef DANIEL_DEBUG_TEMPLATE
#include "../debug.h"
#else
#define debug(...) 42
#endif

#ifndef lowbit
#define lowbit(x) (x & (-x))
#endif

// usage:
//   auto Fun = [&](int i, int j) { return min(i, j); };
//   Fenwick<int, decltype(Fun)> fenw(a, Fun);
// or:
//   Fenwick<int> fenw(a, [&](int i, int j) { return min(i, j); });
template <typename T, class F = function<T(const T&, const T&)>>
class Fenwick {
 public:
  int n;
  vector<T> val, fenw;
  F Func;
  Fenwick (const vector<T>& a, const F& f) : Func(f) {
    n = static_cast<int>(a.size());
    val.resize(n);
    fenw.resize(n);
    for (int i = 1; i <= n; i++) {
      val[i - 1] = fenw[i - 1] = a[i - 1];
      int len = lowbit(i);
      for (int j = 1; j < len; j <<= 1) {
        fenw[i - 1] = Func(fenw[i - 1], fenw[i - j - 1]);
      }
    }
  }
  // change value at k to v
  // k is [0, n)
  inline void Modify(int k, T v) {
    assert(k >= 0 && k < n);
    val[k] = v;
    for (int i = k + 1; i <= n; i += lowbit(i)) {
      fenw[i - 1] = val[i - 1];
      int len = lowbit(i);
      for (int j = 1; j < len; j <<= 1) {
        fenw[i - 1] = Func(fenw[i - 1], fenw[i - j - 1]);
      }
    }
  }
  // l and r are [0, n)
  // ask for [l, r]
  inline T Query(int l, int r) {
    assert(l >= 0 && l < n);
    assert(r >= 0 && r < n);
    ++l, ++r;
    T res = val[r - 1];
    while (true) {
      res = Func(res, val[r - 1]);
      if (l == r) break;
      for (--r; r - lowbit(r) >= l; r -= lowbit(r)) {
        res = Func(res, fenw[r - 1]);
      }
    }
    return res;
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      mp[a[i]].emplace_back(i);
    }
    Fenwick<int> fenw_mx(a, [&](int i, int j) { return max(i, j); });
    Fenwick<int> fenw_mn(a, [&](int i, int j) { return min(i, j); });
    int q;
    cin >> q;
    while (q--) {
      int L, R;
      cin >> L >> R;
      --L;
      --R;
      int mx = fenw_mx.Query(L, R);
      int mn = fenw_mn.Query(L, R);
      if (mn == mx) {
        cout << "-1 -1\n";
        continue;
      }
      int x = *lower_bound(mp[mn].begin(), mp[mn].end(), L);
      int y = *lower_bound(mp[mx].begin(), mp[mx].end(), L);
      cout << x + 1 << ' ' << y + 1 << '\n';
    }
  }
  return 0;
}
