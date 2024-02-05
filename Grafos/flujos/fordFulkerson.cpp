/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct edge {
    int64_t c; // capacity
    int64_t f; // flow
    int to;
};

class ford_fulkerson {
public:
    ford_fulkerson (vector<vector<pair<int, int64_t>>> &graph) : graph(graph){}
    int64_t get_max_flow(int s, int t){
        init();
        int64_t f = 0;
        while(find_and_update(s, t, f)){}
        return f;
    }
private:
    vector<vector<pair<int, int64_t>>> graph; // graph (to, capacity)
    vector<edge> edges; // List of edges (including the inverse ones)
    vector<vector<int>> edge_indexes; // indexes of edges going out from each vertex
    void init(){
        edges.clear();
        edge_indexes.clear(); edge_indexes.resize(graph.size());
        for(int i = 0; i < graph.size(); i++){
            for(int j = 0; j < graph[i].size(); j++){
                edges.push_back({graph[i][j].second, 0, graph[i][j].first});
                edges.push_back({0, 0, i});
                edge_indexes[i].push_back(edges.size() - 2);
                edge_indexes[graph[i][j].first].push_back(edges.size() - 1);
            }
        }
}
    bool find_and_update(int s, int t, int64_t &flow){
        // Encontrar camino desat con BFS
        queue<int> q;
        // Desde donde llego y con que arista
        vector<pair<int, int>> from(graph.size(), make_pair(-1, -1));
        q.push(s);
        from[s] = make_pair(s, -1);
        bool found = false;
        while(q.size() && (!found)){
            int u = q.front(); q.pop();
            for(int i = 0; i < edge_indexes[u].size(); i++){
                int eI = edge_indexes[u][i];
                if((edges[eI].c > edges[eI].f) && (from[edges[eI].to].first == -1)){
                    from[edges[eI].to] = make_pair(u, eI);
                    q.push(edges[eI].to);
                    if(edges[eI].to == t) found = true;
                }
            }
        }
        if(!found) return false;
        // Encontrar cap. minima del camino de aumento
        int64_t u_flow = LLONG_MAX;
        int current = t;
        while(current != s) {
            u_flow = min(u_flow, edges[from[current].second].c - edges[from[current].second].f);
            current = from[current].first;
        }
        current = t;
        // Actualizar flujo
        while(current != s){
            edges[from[current].second].f += u_flow;
            edges[from[current].second^1].f -= u_flow; // Arista inversa
            current = from[current].first;
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
