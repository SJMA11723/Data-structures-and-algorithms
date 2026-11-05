struct dom_tree{
    int N, T;
    vvi graph, DT, rg, bucket;
    vi sdom, dfspar, idom, dsu, label, P, id, rev;
    dom_tree(int s, vvi &_g) : N(sz(_g)), T(0), graph(_g){
        DT = rg = bucket = vvi(N);
        sdom= dfspar= idom= dsu= label= P= id= rev= vi(N);
        build(s, N);
    }
    int find_(int u, int x = 0){
        if(u == dsu[u]) return x ? -1 : u;
        int v = find_(dsu[u], x+1);
        if(v < 0)return u;
        if(sdom[label[dsu[u]]] < sdom[label[u]])
            label[u] = label[dsu[u]];
        dsu[u] = v;
        return x ? v : label[u];
    }
    void dfs(int u){
        T++; rev[T] = u;
        id[u] = label[T] = sdom[T] = dsu[T] = T;
        for(int w : graph[u]){
            if(!id[w]) dfs(w), dfspar[id[w]] = id[u];
            rg[id[w]].pb(id[u]);
        }
    }
    void build(int r, int n){
        dfs(r); n = T;
        repr(i, 1, n + 1){
            for(int w : rg[i])
                sdom[i] = min(sdom[i], sdom[find_(w)]);
            if(i > 1) bucket[sdom[i]].pb(i);
            for(int w : bucket[i]){
                int v = find_(w);
                if(sdom[v] == sdom[w]) idom[w] = sdom[w];
                else idom[w] = v;
            }
            if(i > 1) dsu[i] = dfspar[i];
        }
        rep(i, 2, n + 1){
            if(idom[i] != sdom[i]) idom[i]=idom[idom[i]];
            DT[rev[i]].pb(rev[idom[i]]);
            DT[rev[idom[i]]].pb(rev[i]);
            P[rev[i]] = rev[idom[i]];
        }
    }
};
