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

void dfs(int node, vector<int> &order){
    if(vis[node]) return;
    vis[node] = true;

    for(int v : graph[node]) dfs(v, order);
    order.push_back(node);
}

void scc(int node, const int id){
    if(vis[node]) return;
    vis[node] = true;
    scc[node] = id;

    for(int v : inv_graph[node]) scc(v, id);
}

int kosajaru(){
    vector<int> order;
    for(int i = 1; i <= n; ++i) dfs(i, order);
    reverse(order.begin(), order.end());
    memset(vis, 0, sizeof(vis));
    int id = 0;
    for(int u : topo_ord) if(!vis[u]) assign_scc(u, id++);
    return id;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        inv_graph[b].push_back(a);
    }

    int cnt_comp = kosajaru();

    for(int i = 1; i <= n;++i) cout << i << ": " << scc[i] << '\n';
}
