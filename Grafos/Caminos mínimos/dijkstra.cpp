/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

vector<pair<int, int>> grafo[MAXN];
int dist[MAXN];
bool visitado[MAXN];

void dijkstra(int a, int b){
    memset(dist, 255, sizeof(dist));
    memset(visitado, 0, sizeof(visitado));

    priority_queue<pair<int, int>> q;
    q.push({0, a});
    dist[a] = 0;
    visitado[a] = true;

    while(!q.empty()){
        int c, nodo;
        tie(c, nodo) = q.top();
        q.pop();

        if(visitado[nodo]) continue;
        visitado[nodo] = true;

        for(pair<int, int> it : grafo[nodo]){
            int to, c; tie(to, c) = it;
            if(dist[to] < dist[nodo] + c) continue;

            dist[to] = dist[nodo] + c;
            q.push({-dist[to], to});
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
