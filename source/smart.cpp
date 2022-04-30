#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

//#define int short

const int MX = 3e4 + 228;

int dp[MX][2];

void solve() {
    string s, t;
    cin >> s >> t;
    if (s.size() < t.size()) swap(s, t);
    int ns = s.size(), nt = t.size();
    int ans = 0;
    for (int i = 1; i <= ns; i++) {
        for (int j = 1; j <= nt; j++) {
            dp[j][0] = dp[j][1];
            if (s[i - 1] == t[j - 1]) {
                dp[j][1] = dp[j - 1][0] + 1;
            } else {
                dp[j][1] = max(dp[j][0], dp[j - 1][1]);
            }
        }
    }
    for (int i = 0; i < ns; i++)
        ans = max(ans, dp[i][1]);
    cout << ans << "\n";
}

signed main() {
//#ifdef _DEBUG
//    freopen("in.txt", "r", stdin);
//#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}
