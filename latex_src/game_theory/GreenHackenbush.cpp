struct dsu{ ... } struct edge{ int from, to; };
struct ghb_r{
    int cntRepre, root, value;
    vi compactados, paridad, nim; vvi tree;
};
ghb_r ghb(int n, vector<edge> edges, const vi &suelo={} ){
    vi norm(n); vvi adj(n); iota( all(norm), 0 );
    for( int  u : suelo) norm[u] = 0;
    for( int  i = 0; i < sz(edges); i++ ){
        edge &e = edges[i];
        e.from = norm[e.from], e.to = norm[e.to];
        adj[e.from].pb(i);
        if(e.from != e.to) adj[e.to].pb(i);
    }
    vi pen,dep(n,-1),low(n),par(n, -1),paredg(n, -1),nex(n,0);
    dsu uf(n); pen.pb(0); dep[0] = low[0] = 0;
    while( sz(pen)  ){
        int u = pen.back();
        if( nex[u] < sz(adj[u])  ){
            int id = adj[u][nex[u]++];
            if(id == paredg[u]) continue;
            const edge &e = edges[id];
            int v = (e.from == u ? e.to : e.from);
            if( v == u ) continue;
            if( dep[v] == -1  ){
                par[v] = u, paredg[v] = id;
                dep[v] = low[v] = dep[u] + 1; pen.pb(v);
            }
            else if(dep[v] < dep[u])
                low[u] = min(low[u], dep[v]);
        }else{
            pen.pop_back();
            int p = par[u];
            if(p == -1) continue;
            low[p] = min(low[p], low[u]);
            if(low[u] <= dep[p]) uf.join(p, u, false);
        }
    }
    ghb_r r; vi id(n, -1); r.cntRepre = 0;
    for( int  u = 0; u < n; u++ ){
        if(dep[u] == -1) continue;
        int ro = uf.root(u);
        if(id[ro] == -1) id[ro] = r.cntRepre++;
    }
    r.compactados.assign(n, -1);
    for( int  u = 0; u < n; u++ ){
        int v = norm[u];
        if(dep[v] != -1) r.compactados[u] = id[uf.root(v)];
    }
    r.root = r.compactados[0];
    r.tree.resize(r.cntRepre);r.paridad.assign(r.cntRepre,0);
    for(const edge &e : edges ){
        if(dep[e.from] == -1) continue;
        int a = id[uf.root(e.from)], b = id[uf.root(e.to)];
        if(a == b) r.paridad[a] ^= 1;
        else{ r.tree[a].pb(b); r.tree[b].pb(a); }
    }
    for( int  u = 0; u < r.cntRepre; u++ ){
        if(!r.paridad[u]) continue;
        int leaf = sz(r.tree);
        r.tree.pb(vi{u});
        r.tree[u].pb(leaf);
    }
    vi order={r.root},npar(sz(r.tree),-1);npar[r.root]=r.root;
    for( int  i = 0; i < sz(order); i++ ){ int u = order[i];
        for( int  v : r.tree[u] ){ 
            if(v == npar[u]) continue;
            npar[v] = u; order.pb(v);
        }
    }
    r.nim.assign(sz(r.tree), 0);
    for( int  i = sz(order) - 1; i > 0; i-- ){
        int u = order[i]; r.nim[npar[u]] ^= (r.nim[u]+1);
    }
    r.value = r.nim[r.root]; return r;
}