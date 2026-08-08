#include "template.h"
/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

/// calcula primos hasta n
void sieve(int n, vi &primes);

/*
    La idea es primero calcular los primos hasta sqrt(n), entonces
    ya tenemos todos los primos que dividen a los no primos en [0, n].
    Luego, vamos haciendo la criba en segmentos de tamanio S. De esta manera
    tenemos una complejidad en memoria de O(sqrt(n) + S). Si S = sqrt(n), entonces
    la complejidad en memoria queda O(sqrt(n))
*/
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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n = 11;
    cout << count_primes(n);
}
