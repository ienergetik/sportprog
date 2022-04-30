#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int cost[26];
vector<string> p;
vector<int> plen;
set<string> all;
int n, np;

int count(string s) {
    int res = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        res += cost[s[i] - 'a'];
    }
    return res;
}

int f(string s) {
    int res = 1e9 + 228;
    bool found = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        for (int j = 0; j < np; j++) {
            if (all.count(s.substr(i, plen[j]))) {
                string new_s;
                for (int k = 0; k < (int)s.size(); k++) {
                    if (i <= k && k <= i + plen[j] - 1) {
                    } else {
                        new_s.push_back(s[k]);
                    }
                }
                if (new_s.size()) found = 1;
                res = min(res, f(new_s));
            }
        }
    }
    if (!found) {
//        cerr << s << " - " << count(s) << endl;
        res = count(s);
    }
    cerr << s << " - " << res << endl;
    return res;
}

void solve() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        char c;
        int x;
        cin >> c >> x;
        cost[c-'a'] = x;
    }
    string s;
    cin >> s, n = s.size();
    cin >> np;
    p.resize(np);
    plen.resize(np);
    for (int i = 0; i < np; i++) cin >> p[i], plen[i] = p[i].size(), all.insert(p[i]);
    int ans = f(s);
    cout << count(s) - ans << "\n";
}

int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}
