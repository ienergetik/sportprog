#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int NET = -(1e9 + 228);

struct segtree {
    vector<int> lazy;
    vector<int> f;
    int n;
    segtree(vector<int>& a) {
        n = a.size();
        f.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(0, 0, n, a);
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
        if (vl != vr - 1) {
            lazy[2 * v + 1] += lazy[v];
            lazy[2 * v + 2] += lazy[v];
        }
        f[v] += lazy[v];
        lazy[v] = 0;
    }
    int get(int v, int vl, int vr, int l, int r) {
        push(v, vl, vr);
        if (l >= vr || vl >= r) {
            return NET;
        }
        if (vl >= l && vr <= r) {
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
        if (vl >= l && vr <= r) {
            lazy[v] += x;
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    segtree st(a);
    int q;
    cin >> q;
    for (int z = 0; z < q; z++) {
        char t;
        cin >> t;
        if (t == 'm') {
            int l, r;
            cin >> l >> r;
            cout << st.get(l - 1, r) << "\n";
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            st.change(l - 1, r, x);
        }
    }
}

signed main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}
