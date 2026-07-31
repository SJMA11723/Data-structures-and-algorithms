#include "template.h"
/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

void sieve(int n, vi &primes);


/**
    La idea es que para un entero x, si no es primo, entonces
    x es dividido por algun primo menor o igual a sqrt(x). Entonces,
    si calculamos todos los primos hasta sqrt(b), ya tenemos todos los
    primos posibles que pueden dividir a todo entero en el rango [a, b]

    Criba Segmentada
*/
void range_sieve(ll a, ll b, vll &primes){
    a = max(a, 0ll);
    b = max(b, 0ll);

    ll len = b - a + 1;

    vi sqrt_primes;
    sieve(sqrt(b) + 1, sqrt_primes);


    vector<char> nprime(len);
    primes.clear();
    for(ll p : sqrt_primes){
        /// va por todos los multiplos 'm' de p tales que a <= m <= b
        ll ini = p * max(p, (a + p - 1) / p);
        for(ll m = ini; m <= b; m += p) nprime[m - a] = 1;
    }

    for(ll i = 0; i < len; ++i)
        if(!(nprime[i] || i + a < 2)) primes.pb(i + a);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
