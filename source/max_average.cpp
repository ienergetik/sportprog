#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

inline int nxt() {
    int x;
    scanf("%d", &x);
    return x;
}

const double EPS = 1e-7;

double Max(double a, double b) {
    return a - b < EPS ? b : a;
}

const int MX = 228;
double dp[MX][MX];

void solve() {
    int n = nxt();
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = nxt();
    for (int i = 0; i < n; i++) dp[i][i] = a[i];
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l < n; l++) {
            int r = l + len - 1;
            if (r >= n) break;
            if (l == r - 1) {
                dp[l][r] = (a[l] + a[r]) * 0.5;
                continue;
            }
            for (int i = l; i < r; i++) {
                dp[l][r] = Max(dp[l][r], (dp[l][i] + dp[i + 1][r]) * 0.5);
            }
        }
    }
    printf("%.6lf\n", dp[0][n-1]);
}

int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif

    solve();
}
