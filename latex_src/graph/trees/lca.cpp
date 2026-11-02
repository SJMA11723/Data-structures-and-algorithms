void precalc(int u, int p = 0){
    depth[u] = depth[p] + 1; P[0][u] = p;
    rep(k, 1, LOGN + 1) P[k][u] = P[k - 1][P[k - 1][u]];
    for(int v : T[u]) if(v != p) precalc(v, u);
}
int LCA(int a, int b){
    if(depth[b] < depth[a]) swap(a, b);
    int diff = depth[b] - depth[a];
    repr(k, 0, LOGN + 1) if(is_on(diff, k)) b = P[k][b];
    if(a == b) return a;
    repr(k, 0, LOGN + 1) if(P[k][a] != P[k][b]){
        a = P[k][a];
        b = P[k][b];
    } return P[0][a];
}
int nth_ancestor(int u, int n){
    repr(k, 0, LOGN + 1) if(is_on(n, k)) u = P[k][u];
    return u;
}
