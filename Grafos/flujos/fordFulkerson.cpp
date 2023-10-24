/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct edge {
    long long c; // capacity
    long long f; // flow
    int to;
};

class ford_fulkerson {
public:
    ford_fulkerson (vector<vector<pair<int, long long>>> &graph) : g(graph){}
    long long getMaxFlow(int s, int t){
        init();
        long long f = 0 ;
        while(findAndUpdate(s, t, f)){}
        return f;
    }
private:
    vector<vector<pair<int, long long>>> g; // graph (to, capacity)
    vector<edge> edges; // List of edges (including the inverse ones)
    vector<vector<int>> eIndexes; // indexes of edges going out from each vertex
    void init(){
        edges.clear();
        eIndexes.clear(); eIndexes.resize(g.size());
        for(int i = 0; i < g.size(); i++){
            for(int j = 0; j < g[i].size(); j++){
                edges.push_back({g[i][j].second, 0, g[i][j].first});
                edges.push_back({0, 0, i});
                eIndexes[i].push_back(edges.size() - 2);
                eIndexes[g[i][j].first].push_back(edges.size() - 1);
            }
        }
}
    bool findAndUpdate(int s, int t, long long &flow){
        // Encontrar camino desat con BFS
        queue<int> pending;
        // Desde donde llego y con que arista
        vector<pair<int, int>> from(g.size(), make_pair(-1, -1));
        pending.push(s);
        from[s] = make_pair(s, -1);
        bool found = false;
        while(pending.size() && (!found)){
            int u = pending.front(); pending.pop();
            for(int i = 0; i < eIndexes[u].size(); i++){
                int eI = eIndexes[u][i];
                if((edges[eI].c > edges[eI].f) && (from[edges[eI].to].first == -1)){
                    from[edges[eI].to] = make_pair(u, eI);
                    pending.push(edges[eI].to);
                    if(edges[eI].to == t) found = true;
                }
            }
        }
        if(!found) return false;
        // Encontrar cap. minima del camino de aumento
        long long uFlow = LLONG_MAX;
        int current = t;
        while(current != s) {
            uFlow = min(uFlow, edges[from[current].second].c - edges[from[current].second].f);
            current = from[current].first;
        }
        current = t;
        // Actualizar flujo
        while(current != s){
            edges[from[current].second].f += uFlow;
            edges[from[current].second^1].f -= uFlow; // Arista inversa
            current = from[current].first;
        }
        flow += uFlow ;
        return true;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

}
