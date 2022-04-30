#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define int short

const int MX = 3e4 + 228;

//int dp[MX][MX];
string s, t;

void solve() {
    string ss, tt;
    cin >> ss >> tt;
    s.push_back('#'), t.push_back('#'+1);
    s += ss, t += tt;
    s.push_back('#'), t.push_back('#'+1);
    int ns = s.size(), nt = t.size();
    vector<vector<short>> dp(ns, vector<short>(nt));
    for (int i = 0; i < ns; i++) {
        dp[i][0] = (s[i] == t[0]);
    }
    for (int i = 0; i < nt; i++) {
        dp[0][i] = (t[i] == s[0]);
    }
    short maxlen = 0;
    for (short i = 1; i < ns; i++) {
        for (short j = 1; j < nt; j++) {
            if (s[i] == t[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                maxlen = max(maxlen, dp[i][j]);
                continue;
            }
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    cout << maxlen << "\n";
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}
