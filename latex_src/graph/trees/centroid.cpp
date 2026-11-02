struct CT{
    vvi T;
    vi sub;
    vector<bool> removed;
    CT(vvi &_T) : T(_T){
        sub.resize(sz(T)); removed.resize(sz(T)); build(0);
    }
    int find_sub(int u, int p = -1){
        for(int v : T[u]) if(v != p && !removed[v])
            sub[u] += find_sub(v, u);
        return ++sub[u];
    }
    int find_centroid(int u, int n, int p = -1){
        for(int v:T[u])if(v!=p && sub[v]>n/2 && !removed[v])
            return find_centroid(v, n, u);
        return u;
    }
    void build(int u, int p = -1){
        int n = find_sub(u, p);
        int centroid = find_centroid(u, n, p);
        if(p == -1) p = centroid;
        removed[centroid] = 1;
        vi adj(all(T[centroid]));
        for(int v : adj) if(!removed[v]) build(v, centroid);
    }
};
