/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

int depth[MAXN];
int P[LOGN + 1][MAXN];
vector<int> tree[MAXN];

void precalc(int node, int parent, int d = 1){
    depth[node] = d;
    P[0][node] = parent;
    for(int k = 1; k <= LOGN; ++k)
        P[k][node] = P[k - 1][P[k - 1][node]];

    for(int child : tree[node])
        if(parent != child) precalc(child, node, d + 1);
}

int LCA(int a, int b){
    if(depth[b] < depth[a]) swap(a, b);
    int dif = depth[b] - depth[a];
    for(int k = LOGN; 0 <= k; --k)
        if(isOn(dif, k)) b = P[k][b];

    if(a == b) return a;

    for(int k = LOGN; 0 <= k; --k){
        if(P[k][a] != P[k][b]){
            a = P[k][a];
            b = P[k][b];
        }
    }
    return P[0][a];
}

int nth_ancestor(int u, int n){
    for(int k = LOGN; 0 <= k; --k)
        if(isOn(n, k)) u = P[k][u];
    return u;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

}
