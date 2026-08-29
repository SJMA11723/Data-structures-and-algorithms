void linear_sigma(int n, vi &lp, vll &sigma1){
    vi primes;
    lp.resize(n + 1, 0);
    sigma1.resize(n + 1, 0);
    vll sum_p(n + 1, 0);
    sigma1[1] = 1;
    for(ll i = 2; i <= n; ++i){
        if(lp[i] == 0){
            lp[i] = i;
            primes.pb(i);
            sigma1[i] = i + 1;
            sum_p[i] = i + 1;
        }
        for(int p : primes){
            if(p > lp[i] || i * p > n) break;
            lp[i * p] = p;
            if(lp[i] == p){
                sum_p[i*p] = sum_p[i] * p + 1;
                sigma1[i*p] = sigma1[i] / sum_p[i] * sum_p[i*p];
                break;
            } else {
                sum_p[i * p] = p + 1;
                sigma1[i * p] = sigma1[i] * (p + 1);
            }
        }
    }
}
