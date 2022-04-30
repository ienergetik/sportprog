#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

set<char> ch{'a', 'e', 'i', 'o', 'u', 'y'};

bool f(char c) {
    return ch.count(c);
}

bool g(char c) {
    return !ch.count(c);
}

void solve() {
    string s;
    cin >> s;
    ll res = 1;
    ll a = 6, b = 20;
    int n = s.size();
    for (int i = 0; i < (int)s.size(); i++) {
        if (i != 0 && i != n-1 && ((f(s[i-1]) && f(s[i+1])) || (g(s[i-1]) && g(s[i+1])))) {
            res *= 0;
        }
    }
}

signed main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();
}
