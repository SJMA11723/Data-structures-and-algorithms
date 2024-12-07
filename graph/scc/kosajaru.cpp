/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 100001

using namespace std;

vector<int> graph[MAXN], inv_graph[MAXN];
int scc[MAXN];
bool vis[MAXN];

void dfs(int node, vector<int> &topo_ord){
    if(vis[node]) return;
    vis[node] = true;

    for(int v : graph[node]) dfs(v, topo_ord);
    topo_ord.push_back(node);
}

void assign_scc(int node, const int id){
    if(vis[node]) return;
    vis[node] = true;
    scc[node] = id;

    for(int v : inv_graph[node]) assign_scc(v, id);
}

int kosajaru(int n){
    memset(vis, 0, sizeof(vis));
    vector<int> topo_ord;
    for(int i = 0; i < n; ++i) dfs(i, topo_ord);
    reverse(topo_ord.begin(), topo_ord.end());
    memset(vis, 0, sizeof(vis));
    int id = 0;
    for(int u : topo_ord) if(!vis[u]) assign_scc(u, id++);
    return id;
}

vector<int> scc_graph[MAXN], inv_scc_graph[MAXN];

void build_scc_graph(int n, int n_scc){
    for(int u = 0; u < n; ++u)
        for(int v : graph[u])
            if(scc[u] != scc[v])
                scc_graph[scc[u]].push_back(scc[v]);

    for(int u = 0; u < n_scc; ++u){
        sort(scc_graph[u].begin(), scc_graph[u].end());
        auto it = unique(scc_graph[u].begin(), scc_graph[u].end());
        scc_graph[u].resize(it - scc_graph[u].begin());

        for(int v : scc_graph[u])
            inv_scc_graph[v].push_back(u);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        inv_graph[b].push_back(a);
    }

    int cnt_comp = kosajaru(n);

    for(int i = 1; i <= n;++i) cout << i << ": " << scc[i] << '\n';
}
