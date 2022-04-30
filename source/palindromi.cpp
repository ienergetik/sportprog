#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MX = 2e3 + 228;
const int MD = 1e9;

inline void add(int& a, int x) {
    a += x;
    if (a >= MD) a -= MD;
}

inline void sub(int& a, int x) {
    a -= x;
    if (a < 0) a += MD;
}

inline int mult(int a, int b) {
    ll res = a * 1LL * b;
    if (res >= MD) {
        res %= MD;
    }
    return res;
}

int dp[MX][MX];

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l <= n - len; l++) {
            int r = l + len - 1;
            if (r >= n) break;
            if (l + 1 < n) {
//                dp[l][r] += dp[l + 1][r];
                add(dp[l][r], dp[l + 1][r]);
            }
            if (r - 1 >= 0) {
//                dp[l][r] += dp[l][r - 1];
                add(dp[l][r], dp[l][r - 1]);
            }
            int x = 0;
            if (l + 1 < n && r - 1 >= 0) {
//                dp[l][r] -= dp[l + 1][r - 1];
                sub(dp[l][r], dp[l + 1][r - 1]);
                x = dp[l + 1][r - 1];
            }
            add(dp[l][r], mult((a[l] == a[r]), (1 + x)));
//            dp[l][r] += (a[l] == a[r]) * (1 + x);
        }
    }
    cout << dp[0][n - 1] << "\n";
}

int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}
