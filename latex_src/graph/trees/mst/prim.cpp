#include <bits/stdc++.h>
#define MAXN 10001
struct edge{
    int from, to;
    int64_t w;
    const bool operator<(const edge &b)const{
        return w > b.w;
    }
};
int64_t prim(vector<edge> graph[]){
    int64_t e_cost[MAXN];
    bool vis[MAXN] = {};
    fill(e_cost, e_cost + MAXN, LLONG_MAX);
    int64_t ans = 0;
    priority_queue<edge> q;
    q.push(edge{1, 1, 0});
    while(q.size()){
        int node = q.top().to;
        int64_t w = q.top().w;
        q.pop();
        if(vis[node]) continue;
        vis[node] = true;
        ans += w;
        for(edge &e : graph[node]){
            if(vis[e.to] || e_cost[e.to] <= e.w) continue;
            e_cost[e.to] = e.w;
            q.push(e);
        }
    }
    return ans;
}
