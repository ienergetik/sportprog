#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

//#define int long long

//const int INF = 1e18 + 228;
const int INF = 1e9 + 228; // поменять, если слишком большие числа

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i], a[i] *= -1;
    vector<int> d(n), pos(n), prev(n);
    int len = 0;
    pos[0] = -1;
    d[0] = -INF;
    for (int i = 1; i < n; i++)
        d[i] = INF;
    for (int i = 0; i < n; i++) {
        int j = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[j - 1] < a[i] && a[i] < d[j]) {
            d[j] = a[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            len = max(len, j);
        }
    }
    vector<int> ans;
    int p = pos[len];
    while (p != -1) {
        ans.push_back(p + 1);
        p = prev[p];
    }
    reverse(ans.begin(), ans.end());
    cout << len << "\n";
    for (int e : ans) cout << e << ' ';
}

signed main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}