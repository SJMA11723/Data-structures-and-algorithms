/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
* LinkedIn: https://www.linkedin.com/in/jorgetzab/
*/

#include <bits/stdc++.h>

using namespace std;

void check(int arr[], int n, int bitmask){
    cout << "{ ";
    for(int i = 0; i < n; ++i){
        if(bitmask & (1 << i)){
            cout << arr[i] << " ";
        }
    }
    cout << "}\n";
}

void generaSubconjuntos(int arr[], int n){
    int lim = 1 << n;
    for(int i = 0; i < lim; ++i){
        /// aqui revisas lo que quieras de cada subconjunto
        check(arr, n, i);
    }
}

void generaCombinacionesEnM(int arr[], int n, int m){
    if(n < m) return;

    int lim = 1 << n;
    for(int i = 0; i < lim; ++i){
        if(__builtin_popcount(i) == m){
            /// aqui revisas lo que quieras de cada combinacion
            check(arr, n, i);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int  n = 4;
    int arr[n] = {1, 2, 3, 4};
    generaSubconjuntos(arr, n);
    cout << '\n';
    int m = 2;
    generaCombinacionesEnM(arr, n, m);
}
