#include "template.h"
void sieve(int n, vi &primes);
void range_sieve(ll a, ll b, vll &primes){
    a = max(a, 0ll);
    b = max(b, 0ll);
    ll len = b - a + 1;
    vi sqrt_primes;
    sieve(sqrt(b) + 1, sqrt_primes);
    vector<char> nprime(len);
    primes.clear();
    for(ll p : sqrt_primes){
        ll ini = p * max(p, (a + p - 1) / p);
        for(ll m = ini; m <= b; m += p) nprime[m - a] = 1;
    }
    for(ll i = 0; i < len; ++i)
        if(!(nprime[i] || i + a < 2)) primes.pb(i + a);
}
