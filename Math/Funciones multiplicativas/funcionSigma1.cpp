/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 500001

using namespace std;

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

long long sigma1(int n){
    if(n <= 1) return 1;
    if(!dp[n]){
        long long pot = 1, p = lp[n], n0 = n;
        while(n0 % p == 0){
            pot *= p;
            n0 /= p;
        }
        pot *= p;
        dp[n] = (pot - 1) / (p - 1) * sigma1(n0);
    }
    return dp[n];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    criba(MAXN - 1);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        cout << sigma1(n) << '\n';
    }
}
