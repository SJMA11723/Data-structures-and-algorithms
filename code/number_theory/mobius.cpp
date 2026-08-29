#include "template.h"

void linear_mobius(int n, vi &primes, vi &mu) {
    vi lp(n + 1);
    mu.assign(n + 1, 0);
    mu[1] = 1;

    for(ll i = 2; i <= n; ++i){
        // si no hay primo que lo divida es primo
        if(!lp[i]){
            primes.pb(lp[i] = i);
            mu[i] = -1;
        }
        
        for(int j = 0; i * primes[j] <= n; ++j){
            lp[i * primes[j]] = primes[j];
            
            // i * p_j tiene un primo repetido 
            // porque el menor primo que divide a i lp[i] es p_j
            if(primes[j] == lp[i]){
                mu[i * primes[j]] = 0;
                break;
            } else mu[i * primes[j]] = -mu[i];
            // primos distitnos : alternar -1 +1 -1 
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
}