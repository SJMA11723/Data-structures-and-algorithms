/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

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
void criba(int n, vector<int> &primos){
    bool no_primo[n + 1] = {};
    no_primo[0] = no_primo[1] = true;

    primos.clear();
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
} /// Tiempo: O(nloglogn), Memoria: O(n)

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> primos;
    criba(200, primos);
    for(int it : primos)
        cout << it << ' ';
}
