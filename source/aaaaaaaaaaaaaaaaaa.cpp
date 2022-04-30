#include <bits/stdc++.h>
#ifdef _DEBUG
#include "debug.h"
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
using namespace std;

typedef long long ll;

const int INF = 1e9 + 228;

struct box {
    int l, r, x;
    box() {}
    box(int l_, int r_, int x_) {
        l = l_;
        r = r_;
        x = x_;
    }
};

struct segtree {
    vector<int> f;
    vector<int> lazy;
    int n;
    segtree(int n_) {
        n = n_;
        f.resize(4 * n);
        lazy.resize(4 * n, INF);
    }
    void build(int v, int vl, int vr, vector<int>& a) {
        if (vl == vr - 1) {
            f[v] = a[vl];
            return;
        }
        int mid = (vl + vr) / 2;
        build(2 * v + 1, vl, mid, a);
        build(2 * v + 2, mid, vr, a);
        f[v] = max(f[2 * v + 1], f[2 * v + 2]);
    }
    void push(int v, int vl, int vr) {
        if (lazy[v] != INF) {
            f[v] = lazy[v];
            if (vl != vr - 1) {
                lazy[2 * v + 1] = lazy[v];
                lazy[2 * v + 2] = lazy[v];
            }
            lazy[v] = INF;
        }
    }
    int get(int v, int vl, int vr, int l, int r) {
        push(v, vl, vr);
        if (l >= vr || vl >= r) {
            return -INF;
        }
        if (vl >= l && r >= vr) {
            return f[v];
        }
        int mid = (vl + vr) / 2;
        int ql = get(2 * v + 1, vl, mid, l, r);
        int qr = get(2 * v + 2, mid, vr, l, r);
        return max(ql, qr);
    }
    void change(int v, int vl, int vr, int l, int r, int x) {
        push(v, vl, vr);
        if (l >= vr || vl >= r) {
            return;
        }
        if (vl >= l && r >= vr) {
            lazy[v] = x;
            push(v, vl, vr);
            return;
        }
        int mid = (vl + vr) / 2;
        change(2 * v + 1, vl, mid, l, r, x);
        change(2 * v + 2, mid, vr, l, r, x);
        f[v] = max(f[2 * v + 1], f[2 * v + 2]);
    }
    int get(int l, int r) {
        return get(0, 0, n, l, r);
    }
    void change(int l, int r, int x) {
        change(0, 0, n, l, r, x);
    }
};

int n, k, m;
vector<box> in;

void make() {
    n = 5, k = 3, m = 4;
    in.resize(m);
    for (int i = 0; i < m; i++) {
        in[i].x = rand() % k + 1;
        in[i].l = rand() % n + 1;
        in[i].r = rand() % n + 1;
        if (in[i].l > in[i].r) swap(in[i].l, in[i].r);
    }
}

vector<int> slow() {
    vector<int> c(n);
    for (int i = 0; i < m; i++) {
        for (int ii = in[i].l-1; ii < in[i].r; ii++) {
            c[ii] = in[i].x;
        }
    }
    vector<int> cnt(k);
    for (int i = 0; i < n; i++) {
        if (c[i] != 0) cnt[c[i]-1]++;
    }
    return cnt;
}

vector<int> solve() {
    vector<int> all;
    vector<box> sg;
    for (int i = 0; i < m; i++) {
        int x = in[i].x, l = in[i].l, r = in[i].r;
        sg.push_back({l, r, x});
        all.push_back(l), all.push_back(r);
    }
    map<int, int> mapa;
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    int now = 0, prev = -1;
    for (int e : all) {
        if (e > prev) {
            mapa[e] = now++;
        }
        prev = e;
    }
    segtree st(now);
    for (int i = 0; i < m; i++)
        st.change(mapa[sg[i].l], mapa[sg[i].r] + 1, sg[i].x);
    vector<int> c(now);
    for (int i = 0; i < now; i++) {
        c[i] = st.get(i, i+1);
    }
    debug(c);
    int last = 0;
    vector<box> s;
    for (int i = 1; i < now; i++) {
        if (c[i] != c[i-1]) {
            s.push_back({all[last], all[i], c[i-1]});
            last = i;
        }
    }
    s.push_back({all[last], all[now-1]+1, c[now-1]});
    vector<int> cnt(k);
    for (int i = 0; i < (int)s.size(); i++) {
        cnt[s[i].x - 1] += s[i].r-s[i].l;
//        cerr << s[i].l << ' ' << s[i].r << ' ' << s[i].x << endl;
    }
    return cnt;
}

signed main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
//    freopen("hacks.txt", "w", stderr);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    int count = 0;
    for (int tt = 0; tt < 1010; tt++) {
        make();
        auto a = solve();
        auto b = slow();
//        debug("slow is working");
        if (a != b) {
            cerr << "FOUND: " << endl;
            cerr << n << ' ' << k << ' ' << m << endl;
            for (int i = 0; i < m; i++) {
                cerr << in[i].x << ' ' << in[i].l << ' ' << in[i].r << endl;
            }
            debug("should be:", slow());
            debug("it is:", solve());
            count++;
            assert(count < 5);
        }
    }
}
