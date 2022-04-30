#include <bits/stdc++.h>
using namespace std;

string s;
vector<vector<int>> dp;
vector<vector<int>> ep;

void rec(int l, int r) {
	if (dp[l][r] == r - l + 1)
		return;
	if (dp[l][r] == 0) {
		cout << s.substr(l, r - l + 1);
		return;
	}
	if (ep[l][r] == -1) {
		cout << s[l];
		rec(l + 1, r - 1);
		cout << s[r];
		return;
	}
	rec(l, ep[l][r]);
	rec(ep[l][r] + 1, r);
}

int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> s;
	int n = s.size();
	dp.resize(n);
	ep.resize(n);
	for (int i = 0; i < n; i++) {
		dp[i].resize(n);
		ep[i].resize(n);
	}
    for (int r = 0; r < n; ++r) {
		for (int l = r; l >= 0; --l) {
            if (l == r) {
                dp[l][r] = 1;
                continue;
            }
            int best = 1e9 + 228;
            int mk = -1;
            if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']') || (s[l] == '{' && s[r] == '}')) {
                best = dp[l + 1][r - 1];
            }
            for (int k = l; k < r; ++k) {
                if (dp[l][k] + dp[k + 1][r] < best) {
                    best = dp[l][k] + dp[k + 1][r];
                    mk = k;
                }
            }
            dp[l][r] = best;
            ep[l][r] = mk;
        }
	}
	rec(0, n - 1);
	return 0;
}