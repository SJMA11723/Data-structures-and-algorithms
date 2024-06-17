/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

/// calcula primos hasta n
void criba(int n, vector<int> &primos){
    primos.clear();
    if(n < 2) return;

    vector<bool> no_primo(n + 1);
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
    La idea es primero calcular los primos hasta sqrt(n), entonces
    ya tenemos todos los primos que dividen a los no primos en [0, n].
    Luego, vamos haciendo la criba en segmentos de tamaño S. De esta manera
    tenemos una complejidad en memoria de O(sqrt(n) + S). Si S = sqrt(n), entonces
    la complejidad en memoria queda O(sqrt(n))
*/

/// cuenta primos hasta n en O(sqrt(n)) de memoria - Criba segmentada
int cuenta_primos(int n){
    if(n < 2) return 0;

    const int S = sqrt(n);

    vector<int> primosRaiz;
    criba(sqrt(n) + 1, primosRaiz);

    int ans = 0;

    vector<char> no_primo(S + 1);
    for(int ini = 0; ini <= n; ini += S){
        fill(no_primo.begin(), no_primo.end(), false);
        for(int p : primosRaiz){
            int m = p * max(p, (ini + p - 1) / p) - ini;
            for(; m <= S; m += p)
                no_primo[m] = true;
        }

        for(int i = 0; i < S && i + ini <= n; ++i)
            if(!no_primo[i] && 1 < i + ini)
                ans++;
    }

    return ans;
} /// Tiempo: O(nloglogn), Memoria: O(sqrt(n))

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n = 11;
    cout << cuenta_primos(n);
}
