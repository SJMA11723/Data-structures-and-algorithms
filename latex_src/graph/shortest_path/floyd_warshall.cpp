vvi floyd_warshall(int n){
    const int INF = INT_MAX;
    vvi d(n, vector<int>(n, INF));
    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(d[i][k] == INF) continue;
                if(d[k][j] == INF) continue;
                if(d[i][j] > d[i][k] + d[k][j]) d[i][j] = d[i][k] + d[k][j];
            }
        }
    }
    return d;
}
