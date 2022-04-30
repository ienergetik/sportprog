#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MX = 228;

//int dp[MX][MX];
//pair<int, int> p[MX][MX];
vector<vector<int>> dp;
vector<vector<pair<int, int>>> p;
string s, t;

string ans;

void go(int i, int j) {
    if (i < 0 || j < 0) return;
    if (p[i][j] == make_pair(i - 1, j - 1)) {
        go(i - 1, j - 1);
        ans.push_back(s[i]);
    } else {
        if (p[i][j] == make_pair(i - 1, j)) {
            go(i - 1, j);
        } else {
            go(i, j - 1);
        }
    }
}

void solve() {
    string ss, tt;
    cin >> ss >> tt;
    s.push_back('#'), t.push_back('#'+1);
    s += ss, t += tt;
    s.push_back('#'), t.push_back('#'+1);
    int ns = s.size(), nt = t.size();
    dp.resize(ns, vector<int>(nt));
    p.resize(ns, vector<pair<int, int>>(nt));
    for (int i = 0; i < ns; i++) {
        dp[i][0] = (s[i] == t[0]);
    }
    for (int i = 0; i < nt; i++) {
        dp[0][i] = (t[i] == s[0]);
    }
    int maxlen = 0;
    for (int i = 1; i < ns; i++) {
        for (int j = 1; j < nt; j++) {
            if (s[i] == t[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                p[i][j] = {i - 1, j - 1};
                maxlen = max(maxlen, dp[i][j]);
                continue;
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                    p[i][j] = {i - 1, j};
                } else {
                    dp[i][j] = dp[i][j - 1];
                    p[i][j] = {i, j - 1};
                }
            }
        }
    }
    go(ns - 1, nt - 1);
    cout << ans << endl;
}

int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}
