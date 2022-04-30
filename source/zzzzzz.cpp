#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 1) написать хэши для поиска пероида
// 2) написать сравнение свертки +
// 3) merge? +

string BAD;


struct num {
	static const int MA = 1e9 + 7, MB = 1e9 + 9;
	int a, b;
	num() {}
	num(int x) : a(x), b(x) {}
	num(int a, int b) : a(a), b(b) {}
	num operator + (const num& x) { return num((a + x.a) % MA, (b + x.b) % MB); }
	num operator + (int x) { return num((a + x) % MA, (b + x) % MB); }
	num operator - (const num& x) { return num((a - x.a + MA) % MA, (b - x.b + MB) % MB); }
	num operator * ( int x ) { return num(((int64_t)a * x) % MA, ((int64_t)b * x) % MB); }
	num operator * ( const num& x ) { return num(((int64_t)a * x.a) % MA, ((int64_t)b * x.b) % MB); }
	bool operator == (const num& x) { return (x.a == a && x.b == b); }
	bool operator < (const num& x) { return (a < x.a) || (a == x.a && b < x.b); }
};

const num P(43, 53);

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()

struct Hesh {
	vector<num> h, deg;
	string s;
	int n;
	Hesh(const string& ss) {
		s = ss;
		n = sz(s);
		h.resize(n + 1), deg.resize(n + 1);
		h[0] = 0, deg[0] = 1;
		forn(i, n) {
			h[i + 1] = h[i] * P + s[i];
			deg[i + 1] = deg[i] * P;
		}
	}
	num getHesh(int l, int r) {
		return h[r + 1] - h[l] * deg[r - l + 1];
	}
	num substr(int i, int len) {
		return h[i + len] - h[i] * deg[len];
	}
	bool isEq(int i, int j, int len) {
		auto a = getHesh(i, i + len - 1), b = getHesh(j, j + len - 1);
		return a == b;
	}
	int lcp(int i, int j) {
		int l = 0, r = n - max(i, j);
		while (l < r) {
			int mid = (l + r + 1) / 2;
			if (substr(i, mid) == substr(j, mid))
				l = mid;
			else
				r = mid - 1;
		}
		return l;
	}
	bool cmp(int i, int j) {
		int LCP = lcp(i, j);
		return s[i + LCP] < s[j + LCP];
	}
};

struct box {
    int x;
    string s;
    box() {}
    box(int _x, string _s) {
        x = _x;
        s = _s;
    }
};

struct V {
    vector<box> a;
    int n;
    V() {}
    void add(box b) {
        a.push_back(b);
    }
};

int f(int x) {
    if (x >= 10) return 2;
    return 1;
}

void out(V v) {
    for (int i = 0; i < (int)v.a.size(); i++) {
        cerr << v.a[i].x << "(" << v.a[i].s << ")";
    }
    cerr << endl;
}

string getString(V v) {
    string res;
    for (int i = 0; i < (int)v.a.size(); i++) {
        for (int j = 0; j < v.a[i].x; j++) {
            res += v.a[i].s;
        }
    }
    return res;
}

int sizeOf(V v) {
    int res = 0;
    for (int i = 0; i < (int)v.a.size(); i++) {
        res += f(v.a[i].x) + v.a[i].s.size() + 2;
    }
    return res;
}

V merge(V u, V v) {
    V res = u;
    if (u.a.back().s == v.a[0].s) {
        u.a.back().x += v.a[0].x;
        for (int i = 1; i < (int)v.a.size(); i++) {
            u.add(v.a[i]);
        }
    } else {
        for (int i = 0; i < (int)v.a.size(); i++) {
            u.add(v.a[i]);
        }
    }
    return res;
}

void relax(V& me, V other) {
//    V x1 = make(getString(merge(me, other));
//    V x2 = merge(me, other);
//    if (sizeOf(x1) < sizeOf(y1)) me = x1; else me = x2;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<V>> dp(n, vector<V>(n));
    for (int i = 0; i < n; i++) {
//        dp[i][i] = V(s[i], 1);
    }
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l < n; l++) {
            int r = l + len - 1;
            if (r >= n) break;
//            dp[l][r] = BAD;
            for (int i = l; i < r; i++) {
                // try optimize
//                relax(dp[l][r], merge(dp[l][i], dp[i + 1][r]));
//                relax = if sizeOf(a) < sizeOf(b) ? a : b
            }
        }
    }
}

int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 200; i++) {
        BAD.push_back('1');
    }

    solve();
}
