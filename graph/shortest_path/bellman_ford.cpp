/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct edge{
    int from, to;
    int w;
};

vector<int> bellman_ford(int s, int n, vector<edge> &edges, bool cycles = false){
    vector<int> d(n, (cycles ? 0 : INT_MAX));
    d[s] = 0;
    vector<int> P(n, -1); /// Predecesor

    for(int i = 0; i < n - 1; ++i){
        for(edge &e : edges){
            if(d[e.from] == INT_MAX) continue;

            if(d[e.to] > d[e.from] + e.w){
                d[e.to] = d[e.from] + e.w;
                P[e.to] = e.from;
            }
        }
    }

    /// Una iteracion adicional con al menos un relax de arista
    /// encuentra correctamente los caminos minimos de tamanio
    /// a lo mas n, por lo que si mejora algun camino, se trata de
    /// un ciclo negativo.
    int last_relax = -1;
    for(edge &e : edges){
        if(d[e.from] == INT_MAX) continue;

        if(d[e.to] > d[e.from] + e.w){
            d[e.to] = d[e.from] + e.w;
            P[e.to] = e.from;
            last_relax = e.to;
        }
    }

    if(last_relax == -1) return d;
    return {}; /// VACIO
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

}
