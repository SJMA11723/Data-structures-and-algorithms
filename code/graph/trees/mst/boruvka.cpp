/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 10'001

using namespace std;

struct dsu{
    int RA[MAXN], P[MAXN];
    int cnt_comp;

    dsu(int n){
        for(int i = 0; i < n; ++i){
            RA[i] = 1;
            P[i] = i;
        }
        cnt_comp = n;
    }

    int root(int x){
        if(x == P[x]) return x;
        return P[x] = root(P[x]);
    }

    bool join(int x, int y){
        int Px = root(x);
        int Py = root(y);
        if(Px == Py) return false;
        if(RA[Px] < RA[Py]){
            RA[Py] += RA[Py];
            P[Px] = Py;
        } else {
            RA[Px] += RA[Py];
            P[Py] = Px;
        }
        cnt_comp--;
        return true;
    }
};

struct edge{
    int from, to;
    int64_t w;
};

int64_t boruvka(vector<edge> &edges, int n){
    dsu mset(n);
    int min_edge[n];

    int64_t res = 0;
    while(mset.cnt_comp > 1){
        fill(min_edge, min_edge + n, -1);

        for(int i = 0; i < edges.size(); ++i){
            int u = mset.root(edges[i].from);
            int v = mset.root(edges[i].to);
            if(u == v) continue;
            if(min_edge[u] == -1 || edges[i].w < edges[min_edge[u]].w)
                min_edge[u] = i;

            if(min_edge[v] == -1 || edges[i].w < edges[min_edge[v]].w)
                min_edge[v] = i;
        }

        for(int i = 0; i < n; ++i){
            int idx_e = min_edge[i];
            if(idx_e == -1) continue;
            res += mset.join(edges[idx_e].from, edges[idx_e].to) * edges[idx_e].w;
        }
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m; cin >> n >> m;
    vector<edge> edges;
    for(int i = 0; i < m; ++i){
        int a, b, w; cin >> a >> b >> w;
        a--, b--;
        edges.push_back({a, b, w});
    }
    cout << boruvka(edges, n) << '\n';
}
