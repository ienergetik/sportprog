#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int bad = 0;

struct segtree {
    vector<ll> f;
    vector<int> lazy;
    int n;
    segtree(vector<int>& a) {
        n = a.size();
        f.resize(4 * n);
        lazy.resize(4 * n, bad);
        build(0, 0, n, a);
    }
    segtree(int n_) {
        n = n_;
        f.resize(4 * n);
        lazy.resize(4 * n, bad);
    }
    void build(int v, int vl, int vr, vector<int>& a) {
        if (vl == vr - 1) {
            f[v] = a[vl];
            return;
        }
        int mid = (vl + vr) / 2;
        build(2 * v + 1, vl, mid, a);
        build(2 * v + 2, mid, vr, a);
        f[v] = f[2 * v + 1] + f[2 * v + 2];
    }
    void push(int v, int vl, int vr) {
        if (lazy[v] != 0) {
            f[v] += (vr - vl) * 1LL * lazy[v];
            if (vl != vr - 1) {
                lazy[2 * v + 1] += lazy[v];
                lazy[2 * v + 2] += lazy[v];
            }
            lazy[v] = 0;
        }
    }
    ll get(int v, int vl, int vr, int l, int r) {
        push(v, vl, vr);
        if (l >= vr || vl >= r) {
            return 0;
        }
        if (vl >= l && r >= vr) {
            return f[v];
        }
        int mid = (vl + vr) / 2;
        return get(2 * v + 1, vl, mid, l, r) + get(2 * v + 2, mid, vr, l, r);
    }
    void change(int v, int vl, int vr, int l, int r, int x) {
        push(v, vl, vr);
        if (l >= vr || vl >= r) {
            return;
        }
        if (vl >= l && r >= vr) {
            lazy[v] += x;
            push(v, vl, vr);
            return;
        }
        int mid = (vl + vr) / 2;
        change(2 * v + 1, vl, mid, l, r, x);
        change(2 * v + 2, mid, vr, l, r, x);
        f[v] = f[2 * v + 1] + f[2 * v + 2];
    }
    ll get(int l, int r) {
        return get(0, 0, n, l, r);
    }
    void change(int l, int r, int x) {
        change(0, 0, n, l, r, x);
    }
    void print() {
        for (int i = 0; i < n; i++) {
            cerr << get(i, i+1) << ' ';
        }
        cerr << endl;
    }
};

int n = 4, m = 5;

vector<pair<int, int>> get_sg() {
    vector<pair<int, int>> res;
    for (int i = 0; i < n; i++) {
        res.push_back({rand() % 5, rand() % 10});
        if (res[i].first > res[i].second) swap(res[i].first, res[i].second);
    }
    return res;
}

vector<int> get_pt() {
    vector<int> res;
    for (int i = 0; i < m; i++) {
        res.push_back(rand() % 10);
    }
    return res;
}

vector<pair<int, int>> sg;
vector<int> pt;

vector<int> solve() {
    vector<int> all;
    for (int i = 0; i < n; i++) {
        all.push_back(sg[i].first), all.push_back(sg[i].second);
    }
    for (int i = 0; i < m; i++) {
        all.push_back(pt[i]);
    }
    sort(all.begin(), all.end());
    int now = -1, prev = -(1e9 + 228);
    map<int, int> mapa;
    for (int i = 0; i < (int)all.size(); i++) {
        if (all[i] > prev) {
            mapa[all[i]] = ++now;
        }
        prev = all[i];
    }
    segtree st(now);
    for (int i = 0; i < n; i++) {
        sg[i] = {mapa[sg[i].first], mapa[sg[i].second]};
//        cerr << sg[i].first << ' ' << sg[i].second << "\n";
        st.change(sg[i].first, sg[i].second + 1, 1);
    }
    vector<int> res;
    for (int i = 0; i < m; i++) {
        pt[i] = mapa[pt[i]];
//        cerr << pt[i] << "\n";
        res.push_back(st.get(pt[i], pt[i] + 1));
    }
    return res;
}

void make() {
    sg = get_sg();
    pt = get_pt();
}

vector<int> slow() {
    vector<int> xx(100);
    for (pair<int, int> p : sg) {
        for (int i = p.first; i <= p.second; i++) {
            xx[i]++;
        }
    }
    vector<int> res;
    for (int x : pt) {
        res.push_back(xx[x]);
    }
    return res;
}

#ifdef _DEBUG
#include "debug.h"
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

signed main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int tt = 0; tt < 1010; tt++) {
        make();
        auto a = solve();
        auto b = slow();
        if (a != b) {
            cerr << "FOUND : ";
            cerr << n << ' ' << m << endl;
            for (pair<int, int> p : sg) {
                cerr << p.first << ' ' << p.second << endl;
            }
            for (int e : pt) {
                cerr << e << ' ';
            }
            cerr << "---------" << endl;
        }
    }
}