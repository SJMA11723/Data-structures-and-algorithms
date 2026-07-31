#include <bits/stdc++.h>
void criba_lineal(int n, vector<int> &primos){
    primos.clear();
    if(n < 2) return;
    vector<int> lp(n + 1); /// lp[i] guarda el menor primo que divide a i
    for(long long i = 2; i <= n; ++i){
        if(!lp[i]){ /// si lp[i] = 0, entonces i es primo
            lp[i] = i;
            primos.push_back(i);
        }
        for(int j = 0; i * (long long)primos[j] <= n; ++j){
            lp[i * primos[j]] = primos[j];
            if(primos[j] == lp[i])
                break;
        }
    }
}/// Tiempo: O(n), Memoria: O(n)
