#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool isInt(char c) {
    return '0' <= c && c <= '9';
}

bool isInt(string s) {
    if (s.size() > 1) return 0;
    char c = s[0];
    return '0' <= c && c <= '9';
}

bool isDot(char c) {
    return c == '.';
}

string to_string(char c) {
    return string(1, c);
}

void solve() {
    string s;
    getline(cin, s);
    vector<string> res;
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        cerr << c << endl;
//        if (i != 0 && res[i - 1] == ",") {
//            res.push_back(to_string(c));
//            continue;
//        }
        if (c == ' ' && !((i != 0 && s[i-1] == ' ') || (i != (int)s.size() && s[i+1] == ' '))) {
            continue;
        }
        if (c == ',') {
            res.push_back(to_string(c));
            continue;
        }
        if (isInt(c)) {
            if (res.size() && (res.back() == "." || isInt(res.back()))) {
                res.back().push_back(c);
                continue;
            } else
                res.push_back(to_string(c));
        }
        if (c == '.') {
            if (res.size() && res.back() != ".") {
                res.back().push_back(c);
                continue;
            }
            int N = res.size();
            if (res.size() >= 3 && res.back()[N-1] == res.back()[N-2] &&
                res.back()[N-3] == res.back()[N-2] && res.back()[N-1] == '.') {
                res.back().push_back(c);
            }
        }
    }
    for (string e : res) {
        for (char cc : e) {
            cout << cc;
            if (cc == ',') cout << " ";
        }
    }
    cout << "\n";
}

signed main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}