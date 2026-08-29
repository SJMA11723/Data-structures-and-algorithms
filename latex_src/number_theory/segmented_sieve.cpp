int count_primes(int n){
    if(n < 2) return 0;
    const int S = sqrt(n);
    vi sqrt_primes;
    sieve(sqrt(n) + 1, sqrt_primes);
    int ans = 0;
    vector<char> nprime(S + 1);
    for(int ini = 0; ini <= n; ini += S){
        fill(all(nprime), 0);
        for(int p : sqrt_primes){
            ll m = 1ll * p * max(p, (ini + p - 1) / p) - ini;
            for(; m <= S; m += p) nprime[m] = 1;
        }
        for(int i = 0; i < S && i + ini <= n; ++i)
            if(!nprime[i] && 1 < i + ini) ans++;
    } return ans;
}
