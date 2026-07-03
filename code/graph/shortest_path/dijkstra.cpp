#include "../../template.h"

#define MAXN 100000

struct edge{
    int to;
    ll w;
};

struct pos{
    int from;
    ll c;
    const bool operator<(const pos &b)const{
        return c > b.c;
    }
};

ll dijkstra(int a, int b, vector<edge> graph[]){
    ll dist[MAXN];
    bool vis[MAXN] = {};
    fill(dist, dist + MAXN, LLONG_MAX);

    priority_queue<pos> q;
    q.push(pos{a, 0});
    dist[a] = 0;

    while(sz(q)){
        pos cur = q.top();
        q.pop();

        if(vis[cur.from]) continue;
        vis[cur.from] = true;

        for(edge &e : graph[cur.from]){
            if(dist[e.to] <= dist[cur.from] + e.w) continue;

            dist[e.to] = dist[cur.from] + e.w;
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
