/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 10001

using namespace std;

struct edge{
    int from, to;
    int64_t w;
    const bool operator<(const edge &b)const{
        return w > b.w;
    }
};

int64_t prim(vector<edge> grafo[]){
    int64_t eCost[MAXN];
    bool vis[MAXN];
    memset(vis, 0, sizeof(vis));
    fill(eCost, eCost + MAXN, LLONG_MAX);

    int64_t ans = 0;
    priority_queue<edge> q;
    q.push(edge{1, 1, 0});
    while(q.size()){
        int node = q.top().to;
        int64_t w = q.top().w;
        q.pop();

        if(vis[node]) continue;
        visitado[node] = true;

        ans += w;

        for(edge &it : grafo[node]){
            if(visitado[it.to] || eCost[it.to] <= it.w) continue;
            eCost[it.to] = it.w;
            q.push(it);
        }
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<edge> grafo[n + 1];
    while(m--){
        int i, j, k;
        cin >> i >> j >> k;
        grafo[i].push_back(edge{i, j, k});
        grafo[j].push_back(edge{j, i, k});
    }

    cout << prim();
}
