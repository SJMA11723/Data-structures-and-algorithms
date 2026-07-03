/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
* LinkedIn: https://www.linkedin.com/in/jorgetzab/
*/

#include <bits/stdc++.h>

using namespace std;

void check(int arr[], int n){
    /**
        Aqui revisas las condiciones que quieras de la permutacion actual
    */
    for(int i = 0; i < n; ++i)
        cout << arr[i] << ' ';
    cout << '\n';
}

/// permutaciones de m elementos de un conjunto de n elementos
void generaPermutacionesDeM(int arr[], int n, int m, int actual = 0){
    if(n < m) return;

    if(actual == m){
        /// permutacion completa
        check(arr, m);
        return;
    }

    /**
        Genera las permutaciones
    */
    for(int i = actual; i < n; ++i){
        swap(arr[i], arr[actual]);
        generaPermutacionesDeM(arr, n, m, actual + 1);
        swap(arr[i], arr[actual]);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n = 4;
    int arr[n] = {1, 2, 3, 4};
    generaPermutacionesDeM(arr, n, 3);
}
