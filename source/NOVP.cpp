#define _USE_MATH_DEFINES

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <list>
#include <iomanip>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>

#define all(a) a.begin(),a.end()
#define pb push_back
#define mp make_pair
#define forn(i,n) for(int i = 0; i < int(n); ++i)
#define sz(a) int(a.size())

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    vector<int> dp(m, 0);
    vector<int> res;
    for (int i = 0; i < n; i++) {
        int k = 0;
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j] && k + 1 > dp[j]) {
                dp[j] = k+1;
            }
            if (b[j] < a[i] && k < dp[j]) {
                k = dp[j];
            }
        }
    }
    for (int e : dp) cerr << e << " ";
    cerr << endl;
    cout << *max_element(dp.begin(), dp.end()) << "\n";
}

int main() {
#ifdef _DEBUG
//    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}
