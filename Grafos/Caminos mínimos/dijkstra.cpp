/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

struct edge{
    int to;
    long long c;
};

struct pos{
    int from;
    long long c;
    const bool operator<(const pos &b)const{
        return c > b.c;
    }
};

vector<edge> grafo[MAXN];
long long dist[MAXN];
bool visitado[MAXN];

int dijkstra(int a, int b){
    fill(dist, dist + MAXN, LLONG_MAX);
    memset(visitado, 0, sizeof(visitado));

    priority_queue<pos> q;
    q.push(pos{a, 0});
    dist[a] = 0;

    while(!q.empty()){
        pos act = q.top();
        q.pop();

        if(visitado[act.from]) continue;
        visitado[act.from] = true;

        for(edge &e : grafo[act.from]){
            if(dist[e.to] < dist[act.from] + e.c) continue;

            dist[e.to] = dist[act.from] + e.c;
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
