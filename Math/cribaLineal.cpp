/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

/**
*   La idea es que por cada x en [2, n] guardamos el menor primo que
*   lo divide. Tambien para cada x en [2, n] marcamos para todos los
*   y = p * x tales que p <= (menor primo de x) que el menor primo que
*   divide a y es p
*/

/// hace la criba en O(n) y guarda los primos en el vector
void cribaLineal(int n, vector<int> &primos){
    int lp[n + 1] = {}; /// lp[i] guarda el menor primo que divide a i
    bool no_primo[n + 1] = {};
    no_primo[0] = no_primo[1] = true;

    primos.clear();
    for(long long i = 2; i <= n; ++i){
        if(!lp[i]){ /// si lp[i] = 0, entonces i es primo
            lp[i] = i;
            primos.push_back(i);
        }

        /// para cada numero i * primos[j] tal que primos[j] <= lp[i]
        /// asignamos el menor primo que lo divide como primos[j]
        for(int j = 0; i * (long long)primos[j] <= n; ++j){
            lp[i * primos[j]] = primos[j];
            if(primos[j] == lp[i])
                break;
        }
    }
}/// Tiempo: O(n), Memoria: O(n)

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n = 200;
    vector<int> primos;
    cribaLineal(n, primos);
    for(int it : primos){
        cout << it << ' ';
    }
}
