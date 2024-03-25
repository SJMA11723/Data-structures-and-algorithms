/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 10001

using namespace std;

struct dsu{
    int RA[MAXN], P[MAXN];

    dsu(int n){
        for(int i = 0; i < n; ++i){
            RA[i] = 1;
            P[i] = i;
        }
    }

    int root(int x){
        if(x == P[x]) return x;
        return P[x] = root(P[x]);
    }

    void join(int x, int y){
        int Px = root(x);
        int Py = root(y);
        if(Px == Py) return;
        if(RA[Px] < RA[Py]){
            RA[Py] += RA[Py];
            P[Px] = Py;
        } else {
            RA[Px] += RA[Py];
            P[Py] = Px;
        }
    }
};

struct edge{
    int from, to;
    int64_t w;
    const bool operator<(const edge &b)const{
        return w < b.w;
    }
};

int64_t kruskal(vector<edge> &edges, int n){
    sort(edges.begin(), edges.end());
    dsu mset(n);
    int64_t res = 0;
    for(edge &e : edges){
        if(mset.root(e.from) == mset.root(e.to)) continue;
        mset.join(e.from, e.to);
        res += e.w;
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
    cout << kruskal(edges, n) << '\n';
}
