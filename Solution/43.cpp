#include <bits/stdc++.h>

using namespace std;
#define all(v)(v).begin(), (v).end()
#define debug(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef pair < int, int > pii;
typedef pair < ll, ll > pll;
inline ll Mod(ll x, ll mod) {
  return x % mod >= 0 ? x % mod : x % mod + mod;
}

ll sum[10] = {
  0
};
int nums[] = {
  2,
  3,
  5,
  7,
  11,
  13,
  17
};

bool is_strange(string s) {
  int y = s.length();
  for (int i = 1; i <= y - 3; i++) {
    int p = (s[i] - '0') * 100 + (s[i + 1] - '0') * 10 + (s[i + 2] - '0');
    if (p % nums[i - 1] != 0)
      return 0;
  }
  return 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string ss[] = {
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9"
  };
  string s = "012";
  for (int i = 3; i <= 9; i++) {
    s += ss[i];
    if (is_strange(s)) {
      string p = s;
      if (s[0] == '0') {
        int y = s.length();
        p = s.substr(1, y - 1);
      }
      sum[i] += (stoll(p));
    }

    while (next_permutation(all(s))) {
      if (is_strange(s)) {
        string p = s;
        if (s[0] == '0') {
          int y = s.length();
          p = s.substr(1, y - 1);
        }
        sum[i] += (stoll(p));
        //cout << p << " " << flush ;
      }
    }
  }
  int n;
  cin >> n;
  cout << sum[n];
}