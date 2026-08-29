void dfs(int u, vi graph[], bool vis[], vi &topo_ord){
    if(vis[u]) return;
    vis[u] = true;
    for(int v : graph[u]) dfs(v, graph, vis, topo_ord);
    topo_ord.pb(u);
}
void assign_scc(int u, vi inv_graph[], bool vis[], vi &scc, const int id){
    if(vis[u]) return;
    vis[u] = true;
    scc[u] = id;
    for(int v : inv_graph[u]) assign_scc(v, inv_graph, vis, scc, id);
}
pair<int, vi> kosajaru(int n, vi graph[], vi inv_graph[]){
    bool vis[n] = {};
    vi topo_ord;
    for(int i = 0; i < n; ++i) dfs(i, graph, vis, topo_ord);
    reverse(all(topo_ord));
    memset(vis, 0, sizeof(vis));
    vi scc(n);
    int id = 0;
    for(int u : topo_ord) if(!vis[u]) assign_scc(u, inv_graph, vis, scc, id++);
    return {id, scc};
}
pair<vvi, vvi> build_scc_graph(int n, vi graph[], int max_scc, const vi &scc){
    vvi scc_graph(max_scc), inv_scc_graph(max_scc);
    for(int u = 0; u < n; ++u)
        for(int v : graph[u])
            if(scc[u] != scc[v])
                scc_graph[scc[u]].pb(scc[v]);
    for(int u = 0; u < max_scc; ++u){
        sort(all(scc_graph[u]));
        auto it = unique(all(scc_graph[u]));
        scc_graph[u].resize(it - scc_graph[u].begin());
        for(int v : scc_graph[u])
            inv_scc_graph[v].pb(u);
    }
    return {scc_graph, inv_scc_graph};
}
