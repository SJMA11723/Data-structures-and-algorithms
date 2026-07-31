#include "template.h"
void sieve(int n, vi &primes){
    primes.clear(); if(n < 2) return;
    vector<bool> nprime(n + 1);
    nprime[0] = nprime[1] = 1;
    for(ll i = 3; i * i <= n; i += 2) if(!nprime[i])
    for(ll j = i * i; j <= n; j += 2 * i) nprime[j] = 1;
    primes.pb(2);
    for(int i = 3; i <= n; i += 2) if(!nprime[i]) primes.pb(i);
}
