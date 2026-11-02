#include "../../template.h"

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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n; cin >> n;
    vvi T(n);
    for(int i = 1; i < n; ++i){
        int a, b; cin >> a >> b;
        a--, b--;
        T[a].pb(b);
        T[b].pb(a);
    }
    CT centree(T);
}