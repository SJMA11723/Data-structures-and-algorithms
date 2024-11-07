/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

struct edge{
    int to;
    int64_t w;
};

struct pos{
    int from;
    int64_t c;
    const bool operator<(const pos &b)const{
        return c > b.c;
    }
};

int64_t dijkstra(int a, int b, vector<edge> graph[]){
    int64_t dist[MAXN];
    bool vis[MAXN] = {};
    fill(dist, dist + MAXN, LLONG_MAX);

    priority_queue<pos> q;
    q.push(pos{a, 0});
    dist[a] = 0;

    while(!q.empty()){
        pos act = q.top();
        q.pop();

        if(vis[act.from]) continue;
        vis[act.from] = true;

        for(edge &e : graph[act.from]){
            if(dist[e.to] <= dist[act.from] + e.w) continue;

            dist[e.to] = dist[act.from] + e.w;
            q.push(pos{e.to, dist[e.to]});
        }
    }
    return dist[b];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
