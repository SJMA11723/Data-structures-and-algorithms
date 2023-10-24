/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 10001

using namespace std;

struct edge{
    int to;
    long long c;
    const bool operator<(const edge &b)const{
        return c > b.c;
    }
};

vector<edge> grafo[MAXN];
long long eCost[MAXN];
bool visitado[MAXN];

long long prim(){
    memset(visitado, 0, sizeof(visitado));
    fill(eCost, eCost + MAXN, LLONG_MAX);

    long long ans = 0;
    priority_queue<edge> q;
    q.push(edge{1, 0});
    while(q.size()){
        int node = q.top().to;
        long long c = q.top().c;
        q.pop();

        if(visitado[node]) continue;
        visitado[node] = true;

        ans += c;

        for(edge it : grafo[node]){
            if(visitado[it.to] || eCost[it.to] <= it.c) continue;
            eCost[it.to] = it.c;
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
    while(m--){
        int i, j, k;
        cin >> i >> j >> k;
        grafo[i].push_back(edge{j, k});
        grafo[j].push_back(edge{i, k});
    }

    cout << prim();
}
