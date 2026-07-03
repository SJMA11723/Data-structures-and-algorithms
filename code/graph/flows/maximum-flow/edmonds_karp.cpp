#include "../../../template.h"

struct edge {
    int from, to;
    ll w; /// weight
    ll c; /// capacity
    ll f; /// flow
};

class ford_fulkerson {
public:
    ford_fulkerson (vector<vector<edge>> &graph) : graph(graph){}
    ll get_max_flow(int s, int t){
        init();
        ll f = 0;
        while(find_and_update(s, t, f)){}
        return f;
    }

    vi get_st_cut(const int &s){
        bool vis[sz(graph)] = {};
        vi S;
        queue<int> q;
        q.push(s);
        S.pb(s);
        vis[s] = true;

        while(sz(q)){
            int u = q.front(); q.pop();

            for(int eI : edge_indexes[u]){
                if(edges[eI].c > edges[eI].f && !vis[edges[eI].to]){
                    q.push(edges[eI].to);
                    vis[edges[eI].to] = true;
                    S.pb(edges[eI].to);
                }
            }
        }
        return S;
    }
private:
    vector<vector<edge>> graph; /// graph (to, capacity)
    vector<edge> edges; /// List of edges (including the inverse ones)
    vvi edge_indexes; /// indexes of edges going out from each vertex

    void init(){
        edges.clear();
        edge_indexes.clear(); edge_indexes.resize(sz(graph));
        for(int u = 0; u < sz(graph); u++){
            for(edge &e : graph[u]){
                edges.pb({u, e.to, e.w, e.c, 0});
                edges.pb({e.to, u, -e.w, 0, 0});
                edge_indexes[u].pb(sz(edges) - 2);
                edge_indexes[e.to].pb(sz(edges) - 1);
            }
        }
    }
    bool find_and_update(int s, int t, ll &flow){
        // Encontrar camino desat con BFS
        queue<int> q;
        // Desde donde llego y con que arista
        vpii from(sz(graph), make_pair(-1, -1));
        q.push(s);
        from[s] = make_pair(s, -1);
        while(sz(q)){
            int u = q.front(); q.pop();
            for(int eI : edge_indexes[u]){
                edge &e = edges[eI];
                if(e.c > e.f && from[e.to].fi == -1){
                    from[e.to] = make_pair(u, eI);
                    q.push(e.to);
                    if(e.to == t) break;
                }
            }
        }
        if(from[t].fi == -1) return false;
        // Encontrar cap. minima del camino de aumento
        ll u_flow = LLONG_MAX;
        int current = t;
        while(current != s) {
            u_flow = min(u_flow, edges[from[current].se].c - edges[from[current].se].f);
            current = from[current].fi;
        }
        current = t;
        // Actualizar flujo
        while(current != s){
            edges[from[current].se].f += u_flow;
            edges[from[current].se^1].f -= u_flow; // Arista inversa
            current = from[current].fi;
        }
        flow += u_flow ;
        return true;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
