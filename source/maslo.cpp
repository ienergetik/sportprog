#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, p;

struct cord {
    int x, l, r;
    bool fl;
};

struct node {
    bool upd = 0;
    int mx = -(1e9+228);
    int add = 0;
};

vector<node> t;

void push(int v) {
    if (!t[v].upd) return;
    if (2 * v + 1 < n+p-1) {
        if (t[2 * v + 1].upd)
            t[2 * v + 1].add += t[v].add;
        else {
            t[2 * v + 1].upd = 1;
            t[2 * v + 1].add = t[v].add;
        }
    }
    if (2 * v + 2 < n+p-1) {
        if (t[2 * v + 2].upd)
            t[2 * v + 2].add += t[v].add;
        else {
            t[2 * v + 2].upd = 1;
            t[2 * v + 2].add = t[v].add;
        }
    }
    t[v].upd = 0;
    t[v].mx += t[v].add;
}

void build(int v, int vl, int vr) {
    if (vl == vr) {
        if (v - p + 1 < n) {
            t[v].mx = 0;
            return;
        }
    }
    int mid = (vl + vr) / 2;
    build(2 * v + 1, vl, mid);
    build(2 * v + 2, mid, vr);
    t[v].mx = max(t[2 * v + 1].mx, t[2 * v + 2].mx);
}

int getY() {
    int mx = t[0].mx, v = 0;
    while (2 * v + 1 < n + p - 1) {
        push(v);
        int lf = -1;
        if (t[2 * v + 1].upd)
            lf = t[2 * v + 1].mx + t[2 * v + 1].add;
        else
            lf = t[2 * v + 1].mx;
        if (lf == mx) v *= 2, ++v;
        else v *= 2, v += 2;
    }
    return v;
}

void add(int v, int vl, int vr, int l, int r, int x) {
    if (l > vr || r < vl)
        return;
    if (vl >= l && r >= vr) {
        push(v);
        if (t[v].upd)
            t[v].add += x;
        else {
            t[v].upd = 1;
            t[v].add = x;
        }
        push(v);
        int tm = (vl + vr) / 2;
        add(v * 2 + 1, l, r, vl, tm, x);
        add(v * 2 + 2, l, r, tm + 1, vr, x);
        int left, right;
        if (t[v * 2 + 1].upd) left = t[v * 2 + 1].mx + t[v * 2 + 1].add;
        else left = t[v * 2 + 1].mx;
        if (t[v * 2 + 2].upd) right = t[v * 2 + 2].mx + t[v * 2 + 2].add;
        else right = t[v * 2 + 2].mx;
        t[v].mx = max(left, right);
    }
}

void solve() {
    int N;
    cin >> N;
    p = 1;
    vector<cord> x(2 * N);
    cin >> x[0].x >> x[0].l >> x[1].x >> x[0].r;
    x[0].fl = 1, x[1].fl = 0;
    x[1].l = x[0].l, x[1].r = x[0].r;
    int mny = x[0].l, mxy = x[0].r;
    for (int i = 2; i < 2 * N; i += 2) {
        cin >> x[i].x >> x[i].l >> x[i+1].x >> x[i].r;
        x[i].fl = 1;
        x[i + 1].fl = 0;
        x[i + 1].l = x[i].l;
        x[i + 1].r = x[i].r;
        mny = min(mny, x[i].l);
        mxy = max(mxy, x[i].r);
    }
    sort(x.begin(), x.end(), [&](cord a, cord b) {
        return (a.x < b.x) || (a.x == b.x && (a.fl || !b.fl));
    });
    n = mxy+1-mny;
    while (n > p) {
        p = p << 1;
    }
    int sz = 2*p-1;
    t.resize(sz);
    build(0, 0, p-1);
    int cx=x[0].x, cy=x[0].l;
    int m = -mny;
    int Add = -1;
    if (x[0].fl) Add = 1;
    add(0, x[0].l + m, x[0].r + m, 0, p - 1, Add);
    int best = t[0].mx;
    for (int i = 1; i < (int)x.size(); i++) {
        Add = -1;
        if (x[i].fl)
            Add = 1;
        add(0, x[i].l + m, x[i].r + m, 0, p - 1, Add);
        if (best < t[0].mx) {
            best = t[0].mx;
            cx = x[i].x;
            cy = getY() - m - p + 1;
        }
    }
    cout << best << "\n" << cx << ' ' << cy << "\n";
}

signed main() {
#ifdef _DEBUG
//    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}