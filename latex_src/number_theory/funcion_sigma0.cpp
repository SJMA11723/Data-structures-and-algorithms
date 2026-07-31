#include <bits/stdc++.h>
#define MAXN 500001
long long dp[MAXN];
long long lp[MAXN];
void criba(int n){
    vector<int> primos;
    primos.reserve(sqrt(n));
    for(long long i = 2; i <= n; ++i){
        if(!lp[i]){
            lp[i] = i;
            primos.push_back(i);
        }
        for(int j = 0; i * (long long)primos[j] <= n; ++j){
            lp[i * primos[j]] = primos[j];
            if(primos[j] == lp[i]) break;
        }
    }
}
long long sigma0(int n){
    if(n <= 1) return 1;
    if(!dp[n]){
        long long exp = 0, p = lp[n], n0 = n;
        while(n0 % p == 0){
            exp++;
            n0 /= p;
        }
        dp[n] = (exp + 1) * sigma0(n0);
    }
    return dp[n];
}
