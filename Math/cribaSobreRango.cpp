/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

/// calcula primos hasta n y guarda los primos en el vector
void criba(int n, vector<int> &primos){
    primos.clear();
    if(n < 2) return;

    bool no_primo[n + 1] = {};
    no_primo[0] = no_primo[1] = true;

    for(long long i = 3; i * i <= n; i += 2){
        if(no_primo[i]) continue;
        for(long long j = i * i; j <= n; j += 2 * i)
            no_primo[j] = true;
    }

    primos.push_back(2);
    for(int i = 3; i <= n; i += 2){
        if(!no_primo[i])
            primos.push_back(i);
    }
}/// Tiempo: O(nloglogn), Memoria: O(n)


/**
    La idea es que para un entero x, si no es primo, entonces
    x es dividido por algún primo menor o igual a sqrt(x). Entonces,
    si calculamos todos los primos hasta sqrt(b), ya tenemos todos los
    primos posibles que pueden dividir a todo entero en el rango [a, b]
*/

void cribaSobreRango(long long a, long long b, vector<long long> &primos){
    a = max(a, 0ll);
    b = max(b, 0ll);

    long long tam = b - a + 1;

    vector<int> primosRaiz;
    criba(sqrt(b) + 1, primosRaiz);


    bool no_primo[tam] = {};
    primos.clear();
    for(long long p : primosRaiz){
        /// va por todos los multiplos m de p tales que a <= m <= b
        long long ini = p * max(p, (a + p - 1) / p);
        for(long long m = ini; m <= b; m += p){
            no_primo[m - a] = true;
        }
    }

    for(long long i = 0; i < tam; ++i){
        if(no_primo[i] || i + a < 2) continue;
        primos.push_back(i + a);
    }
}/// Tiempo: O(sqrt(b)loglogsqrt(b) + (b - a)loglog(b - a)), Memoria: O(b - a)

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<long long> primos;
    cribaSobreRango(-10, -2, primos);
    for(int it : primos)
        cout << it << ' ';
}
