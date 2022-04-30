#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(a) (a).begin(),(a).end()

template<class U, class V>
ostream& operator<<(ostream& out, const pair<U, V>& a) {
  return out << "(" << a.x << ", " << a.y << ")";
}

template<class U, class V>
istream& operator>>(istream& in, pair<U, V>& a) {
  return in >> a.x >> a.y;
}

template<typename W, typename T = typename enable_if<!is_same<W, string>::value, typename W::value_type>::type>
ostream& operator<<(ostream& out, const W& v) { out << "{ "; for (const auto& x : v) out << x << ", "; return out << '}'; }

template<class T>
void readArr(T from, T to) {
  for (auto i = from; i != to; ++i) cin >> *i;
}

template<class T>
void outArr(T from, T to) {
  for (auto i = from; i != to; ++i) cerr << *i << ' ';
  cerr << endl;
}

struct mergetree {
    vector<vector<int>> f;
    int n;
    mergetree(vector<int>& a) {
        n = a.size();
        f.resize(4 * n);
        build(0, 0, n, a);
    }
    void build(int v, int vl, int vr, vector<int>& a) {
        if (vl == vr - 1) {
            f[v].push_back(a[vl]);
//            cerr << "(" << vl+1 << ", " << vr+1 << "): ";
//            outArr(all(f[v]));
            return;
        }
        int mid = (vl + vr) / 2;
        build(2 * v + 1, vl, mid, a);
        build(2 * v + 2, mid, vr, a);
        int q = 0;
        for (int p = 0; p < (int)f[2 * v + 1].size(); p++) {
            while (q < (int)f[2 * v + 2].size() && f[2 * v + 1][p] > f[2 * v + 2][q]) {
                f[v].push_back(f[2 * v + 2][q]);
                q++;
            }
            f[v].push_back(f[2 * v + 1][p]);
        }
        for (; q < (int)f[2 * v + 2].size(); q++) {
            f[v].push_back(f[2 * v + 2][q]);
        }
//        cerr << "(" << vl+1 << ", " << vr+1 << "): ";
//        outArr(all(f[v]));
    }
    int get(int v, int vl, int vr, int l, int r, int L, int R) {
        if (l >= vr || vl >= r) {
            return 0;
        }
        if (vl >= l && r >= vr) {
            auto itR = upper_bound(f[v].begin(), f[v].end(), R);
            auto itL = lower_bound(f[v].begin(), f[v].end(), L);
            return distance(itL, itR);
        }
        int mid = (vl + vr) / 2;
        int ql = get(2 * v + 1, vl, mid, l, r, L, R);
        int qr = get(2 * v + 2, mid, vr, l, r, L, R);
        return ql + qr;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    mergetree mt(a);
    for (int zz = 0; zz < q; zz++) {
        int l, r, L, R;
        cin >> l >> r >> L >> R;
        cout << mt.get(0, 0, n, l - 1, r, L, R) << "\n";
    }
}

void mergeme(vector<int> a, vector<int> b) {
    int q = 0;
    vector<int> c;
    for (int p = 0; p < (int)a.size(); p++) {
        while (q < (int)b.size() && a[p] > b[q]) {
            c.push_back(b[q]);
            q++;
        }
        c.push_back(a[p]);
    }
    for (; q < (int)b.size(); q++) {
        c.push_back(b[q]);
    }
    outArr(all(c));
}

signed main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);

//    vector<int> a = {1, 2}, b = {3, 4, 5};
//    mergeme(a, b);
//    return 0;

    solve();
}
