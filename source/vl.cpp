#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

struct Edge {
    int to;
    bool flag;
    Edge(int to_) {
        to = to_;
        flag = 0;
    }
};

vector<vector<Edge>> oldgr;
vector<vector<int>> gr;
set<pii> br;
vector<int> clr;
vector<bool> used;
vector<int> dd, h;
int n, m, f, cur = 0;
int timer = 0;

void dfs1(int v, int p) { // ищет мосты в oldgr
    used[v] = 1;
    h[v] = dd[v] = timer++;
    for (Edge e : oldgr[v]) {
        int u = e.to;
        if (u == p) continue;
        if (used[u])
            dd[v] = min(dd[v], h[u]);
        else {
            dfs1(u, v);
            dd[v] = min(dd[v], dd[u]);
            if (dd[u] > h[v]) {
                e.flag = 1;
                br.insert({v, u});
            }
        }
    }
}

void dfs2(int v) { // нахожу компоненты
    clr[v] = cur;
    for (Edge e : oldgr[v]) {
        int u = e.to;
        if (clr[u] == 0 && !br.count({v, u}) && !br.count({u, v}))
            dfs2(u);
    }
}

const int N = 100228, LOG = 21;
int up[N][LOG], d[N], tin[N], tout[N];

void dfs3(int v, int p) {
    tin[v] = timer++;
    if (v == p)
        d[v] = 0;
    else
        d[v] = d[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < LOG; i++)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (int u : gr[v]) {
        if (u != p)
            dfs3(u, v);
    }
    tout[v] = timer++;
}

bool ispar(int u, int v) { // u предок v
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (ispar(u, v)) return u;
    if (ispar(v, u)) return v;
    for (int i = LOG - 1; i >= 0; i--) {
        if (!ispar(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

int main() {
#ifdef home
    freopen("in.txt", "r", stdin);
#else
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
#endif
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> n >> m >> f;
    --f;
    oldgr.resize(n);
    clr.resize(n);
    used.resize(n);
    dd.resize(n);
    h.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        oldgr[x].push_back(Edge(y));
        oldgr[y].push_back(Edge(x));
    }
    int root = f;
    dfs1(root, root);
    cur = 0;
    for (int v = 0; v < n; v++) { // ищу компоненты реб.двусвязанности
        if (clr[v] == 0) {
            cur++;
            dfs2(v);
        }
    }
    int ncomp = cur + 1;
    for (int i = 0; i < ncomp; i++) {
        clr[i]--;
    }
    gr.resize(ncomp);
    for (pii e : br) {
        int u = e.first, v = e.second;
        gr[clr[u]].push_back(clr[v]);
        gr[clr[v]].push_back(clr[u]);
//        cerr << clr[v] << ' ' << clr[u] << endl;
    }
    root = clr[f];
    timer = 0;
    dfs3(root, root);
    int k;
    cin >> k;
    for (int z = 0; z < k; z++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        u = clr[u], v = clr[v];
        int l = lca(u, v);
        cout << d[l] << endl;
    }
}
/*
 * 1) ищу мосты и помечаю их
 * 2) во втором дфсе чекаю что текущее ребро не мост,
 *    иначе добавляю в дерево ребро из текущей компоненты и следующей
 * 3) на получившемся дереве ищем лца
 */

