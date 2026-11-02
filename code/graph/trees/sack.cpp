#include "../../../template.h"

vvi T; // hide
vi sub, depth; // hide
vector<bool> big; // hide

int precalc(int u, int p = 0){
    depth[u] = depth[p] + 1;
    for(int v : T[u]) if(v != p) sub[u] += precalc(v, u);
    return ++sub[u];
}

/// sack
void add(int u, int x, int p = 0){
    /// add node here

    /// add subtree
    for(int v: T[u]) if(v != p && !big[v]) add(v, x, u);
}

void dfs(int u, bool keep, int p = 0){
    int maxi = -1, big_child = -1;
    /// Search for big_child
    for(int v : T[u]) if(v != p && sub[v] > maxi)
        maxi = sub[v], big_child = v;

    for(int v : T[u]) if(v!=p && v!=big_child) dfs(v, 0, u);  /// run a dfs on small childs and clear them
    if(big_child!=-1) dfs(big_child,1,u), big[big_child] = 1;  /// big_child marked as big and not cleared

    add(u, 1, p);
    /// answer queries here

    if(big_child != -1) big[big_child] = 0;
    if(!keep) add(u, -1, p);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

}
