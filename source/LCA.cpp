#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MX = 1e5 + 228;
const int LG = 17;

int up[MX][LG], tin[MX], tout[MX], d[MX];
vector<vector<int>> gr;
int timer = 0;

void dfs(int v, int p = 0) {
    tin[v] = timer++;
    up[v][0] = p;
    if (p != v)
        d[v] = d[p] + 1;
    else
        d[v] = 0;
    for (int i = 1; i < LG; i++)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (int u : gr[v])
        if (u != p)
            dfs(u, v);
    tout[v] = timer++;
}

bool ispar(int u, int v) { // u предок v
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (ispar(u, v)) return u;
    if (ispar(v, u)) return v;
    for (int i = LG - 1; i >= 0; i--) {
        if (!ispar(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void solve() {
    int n;
    cin >> n;
    gr.resize(n);
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    int root = 0;
    dfs(root, 0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        int x = lca(u, v);
        cout << d[u] - 2 * d[x] + d[v] << "\n";
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
