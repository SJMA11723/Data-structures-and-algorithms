#include "template.h"
/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

/**
*   La idea es que por cada x en [2, n] guardamos el menor primo que
*   lo divide. Tambien para cada x en [2, n] marcamos para todos los
*   y = p * x tales que p <= (menor primo de x) que el menor primo que
*   divide a y es p
*/

/// hace la criba en O(n) y guarda los primos en el vector
void linear_sieve(int n, vi &primes){
    primes.clear();
    if(n < 2) return;

    vi lp(n + 1);

    for(ll i = 2; i <= n; ++i){
        /// si lp[i] = 0, entonces i es primo
        if(!lp[i]) primes.pb(lp[i] = i);

        /// para cada numero i * primes[j] tal que primes[j] <= lp[i]
        /// asignamos el menor primo que lo divide como primes[j]
        for(int j = 0; i * primes[j] <= n; ++j){
            lp[i * primes[j]] = primes[j];
            if(primes[j] == lp[i]) break;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n = 200;
    vector<int> primes;
    linear_sieve(n, primes);
    for(int it : primes){
        cout << it << ' ';
    }
}
