#include <bits/stdc++.h>
#define MAXN 1000001
int dp[MAXN];
int lp[MAXN];
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
int moebius(int n){
    if(n <= 1) return 1;
    if(dp[n] == -7){
        int exp = 0, p = lp[n], n0 = n;
        while(n0 % p == 0){
            exp++;
            n0 /= p;
        }
        dp[n] = (exp > 1 ? 0 : -1 * moebius(n0));
    }
    return dp[n];
}
