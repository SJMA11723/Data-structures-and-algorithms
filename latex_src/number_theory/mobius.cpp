void linear_mobius(int n, vi &primes, vi &mu) {
    vi lp(n + 1);
    mu.assign(n + 1, 0);
    mu[1] = 1;
    for(ll i = 2; i <= n; ++i){
        if(!lp[i]){
            primes.pb(lp[i] = i);
            mu[i] = -1;
        }
        for(int j = 0; i * primes[j] <= n; ++j){
            lp[i * primes[j]] = primes[j];
            if(primes[j] == lp[i]){
                mu[i * primes[j]] = 0;
                break;
            } else mu[i * primes[j]] = -mu[i];
        }
    }
}
