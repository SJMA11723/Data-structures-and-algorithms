#include "template.h"

/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

/**
*   La idea es tener un arreglo no_primo[] en el cual
*       - no_primo[i] = false si i es primo
*       - no_primo[i] = true si i no es primo
*   Al principio, para todo i, no_primo[i] = false.
*   Como ya sabemos que 2 es primo y todo par mayor es compuesto,
*   entonces recorremos todos los impares en [3, sqrt(n)] y para cada
*   numero en ese rango marcamos todos sus multiplos como no primos
*/

/// calcula primos hasta n y guarda los primos en el vector
void sieve(int n, vi &primes){
    primes.clear(); if(n < 2) return;

    vector<bool> nprime(n + 1);
    nprime[0] = nprime[1] = 1;

    for(ll i = 3; i * i <= n; i += 2) if(!nprime[i])
    for(ll j = i * i; j <= n; j += 2 * i) nprime[j] = 1;

    primes.pb(2);
    for(int i = 3; i <= n; i += 2) if(!nprime[i]) primes.pb(i);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vi primos;
    sieve(1, primos);
    for(int it : primos)
        cout << it << ' ';
}
