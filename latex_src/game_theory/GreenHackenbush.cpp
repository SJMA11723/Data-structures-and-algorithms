struct dsu{ ... }
struct edge{
    int from, to;
};
struct hackenbush_result{
    int cntRepresentantes, root, value;
    vi compactados, paridad, nim;
    vvi tree;
};
hackenbush_result green_hackenbush(int n, vector<edge> edges, const vi &mas_suelo = {}){
    vi norm(n);
    iota(all(norm), 0);
    for(int u : mas_suelo) norm[u] = 0;
    vvi adj(n);
    for(int i = 0; i < sz(edges); i++){
        edge &e = edges[i];
        e.from = norm[e.from], e.to = norm[e.to];
        adj[e.from].pb(i);
        if(e.from != e.to) adj[e.to].pb(i);
    }
    vi pendiente = {0}, depth(n, -1), low(n), parent(n, -1), parent_edge(n, -1), next(n,0);
    dsu unionf(n);
    depth[0] = low[0] = 0;
    while( sz(pendiente) ){
        int u = pendiente.back();
        if(next[u] < sz(adj[u])){
            int id = adj[u][next[u]++];
            if(id == parent_edge[u]) continue;
            const edge &e = edges[id];
            int v = (e.from == u ? e.to : e.from);
            if(v == u) continue;
            if(depth[v] == -1){
                parent[v] = u;
                parent_edge[v] = id;
                depth[v] = low[v] = depth[u] + 1;
                pendiente.pb(v);
            }
            else if(depth[v] < depth[u])
                low[u] = min(low[u], depth[v]);
        }else{
            pendiente.pop_back();
            int p = parent[u];
            if(p == -1) continue;
            low[p] = min(low[p], low[u]);
            if(low[u] <= depth[p]) unionf.join(p, u, false);
        }
    }
    hackenbush_result res;
    vi id(n, -1);
    res.cntRepresentantes = 0;
    for(int u = 0; u < n; u++){
        if(depth[u] == -1) continue;
        int r = unionf.root(u);
        if(id[r] == -1) id[r] = res.cntRepresentantes++;
    }
    res.compactados.assign(n, -1);
    for(int u = 0; u < n; u++){
        int v = norm[u];
        if(depth[v] != -1) res.compactados[u] = id[unionf.root(v)];
    }
    res.root = res.compactados[0];
    res.tree.resize(res.cntRepresentantes);
    res.paridad.assign(res.cntRepresentantes, 0);
    for(const edge &e : edges){
        if(depth[e.from] == -1) continue;
        int a = id[unionf.root(e.from)], b = id[unionf.root(e.to)];
        if(a == b) res.paridad[a] ^= 1;
        else{
            res.tree[a].pb(b);
            res.tree[b].pb(a);
        }
    }
    for(int u = 0; u < res.cntRepresentantes; u++){
        if(!res.paridad[u]) continue;
        int leaf = sz(res.tree);
        res.tree.pb(vi{u});
        res.tree[u].pb(leaf);
    }
    vi order = {res.root}, par(sz(res.tree), -1);
    par[res.root] = res.root;
    for(int i = 0; i < sz(order); i++){
        int u = order[i];
        for(int v : res.tree[u]){ 
            if(v == par[u]) continue;
            par[v] = u;
            order.pb(v);
        }
    }
    res.nim.assign(sz(res.tree), 0);
    for(int i = sz(order) - 1; i > 0; i--){
        int u = order[i];
        res.nim[par[u]] ^= (res.nim[u]+1);
    }
    res.value = res.nim[res.root];
    return res;
}