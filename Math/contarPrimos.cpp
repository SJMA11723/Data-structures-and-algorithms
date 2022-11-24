/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

/// calcula primos hasta n
void criba(int n, vector<int> &primos){
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

/// cuenta primos hasta n en O(sqrt(n)) de memoria
int cuentaPrimos(int n){
    const int S = sqrt(n);

    vector<int> primosRaiz;
    criba(S, primosRaiz);

    int ans = 0;

    bool no_primo[S];
    for(int ini = 0; ini <= n; ini += S){
        memset(no_primo, 0, S);
        for(int p : primosRaiz){
            int m = p * max(p, (ini + p - 1) / p) - ini;
            for(; m <= S; m += p)
                no_primo[m] = true;
        }

        if(ini == 0) no_primo[0] = no_primo[1] = true;
        for(int i = 0; i < S && i + ini <= n; ++i)
            if(!no_primo[i])
                ans++;
    }

    return ans;
} /// Tiempo: O(nloglogn), Memoria: O(sqrt(n))

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n = 2e8;
    cout << cuentaPrimos(n);
}
