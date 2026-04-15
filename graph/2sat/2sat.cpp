#include "../../template.h"

struct two_sat{
    int n;
    vvi graph, inv_graph;
    vi scc, ans;
    vector<bool> vis;

    two_sat(){}

    two_sat(int _n){
        n = _n;
        graph.resize(2 * n);
        inv_graph.resize(2 * n);
        scc.resize(2 * n);
        vis.resize(2 * n);
        ans.resize(n);
    }

    void add_edge(int u, int v){
        graph[u].pb(v);
        inv_graph[v].pb(u);
    }

    /// al menos una es verdadera
    void add_or(int p, bool val_p, int q, bool val_q){
        add_edge(p + (val_p ? n : 0), q + (val_q ? 0 : n));
        add_edge(q + (val_q ? n : 0), p + (val_p ? 0 : n));
    }

    /// exactamente una es verdadera
    void add_xor(int p, bool val_p, int q, bool val_q){
        add_or(p, val_p, q, val_q);
        add_or(p, !val_p, q, !val_q);
    }

    /// p y q tienen el mismo valor
    void add_and(int p, bool val_p, int q, bool val_q){
        add_xor(p, !val_p, q, val_q);
    }

    /// Kosajaru
    void dfs(int u, vi &topo_ord){
        if(vis[u]) return;
        vis[u] = true;

        for(int v : graph[u]) dfs(v, topo_ord);
        topo_ord.pb(u);
    }

    void assign_scc(int u, const int id){
        if(vis[u]) return;
        vis[u] = true;
        scc[u] = id;

        for(int v : inv_graph[u]) assign_scc(v, id);
    }

    /// construye respuesta
    bool build_ans(){
        fill(all(vis), false);
        vi topo_ord;

        for(int i = 0; i < 2 * n; ++i) dfs(i, topo_ord);
        fill(all(vis), false);
        reverse(all(topo_ord));

        int id = 0;
        for(int u : topo_ord) if(!vis[u]) assign_scc(u, id++);

        for(int i = 0; i < n; ++i){
            if(scc[i] == scc[i + n]) return false;
            ans[i] = (scc[i] < scc[i + n] ? 0 : 1);
        }
        return true;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

}
