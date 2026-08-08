#include "template.h"
void linear_sieve(int n, vi &primes){
    primes.clear();
    if(n < 2) return;
    vi lp(n + 1);
    for(ll i = 2; i <= n; ++i){
        if(!lp[i]) primes.pb(lp[i] = i);
        for(int j = 0; i * primes[j] <= n; ++j){
            lp[i * primes[j]] = primes[j];
            if(primes[j] == lp[i]) break;
        }
    }
}
