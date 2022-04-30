#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int bad = -1;

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
        if (lazy[v] != -1) {
            f[v] = (vr - vl) * lazy[v];
            if (vl != vr - 1) {
                lazy[2 * v + 1] = lazy[v];
                lazy[2 * v + 2] = lazy[v];
            }
            lazy[v] = -1;
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
            lazy[v] = x;
            push(v, vl, vr);
            return;
        }
        int mid = (vl + vr) / 2;
        change(2 * v + 1, vl, mid, l, r, x);
        change(2 * v + 2, mid, vr, l, r, x);
        f[v] = f[2 * v + 1] + f[2 * v + 2];
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    segtree st(a);
    for (int z = 0; z < q; z++) {
        char t;
        cin >> t;
        if (t == 'Q') {
            int l, r;
            cin >> l >> r;
            cout << st.get((0, 0, n, l - 1, r)) << "\n";
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            st.change(0, 0, n, l - 1, r, x);
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
