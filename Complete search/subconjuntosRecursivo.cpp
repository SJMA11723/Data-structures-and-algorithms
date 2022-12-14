/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
* LinkedIn: https://www.linkedin.com/in/jorgetzab/
*/

#include <bits/stdc++.h>

using namespace std;

void check(int arr[], bool used[], int n){
    cout << "{ ";
    for(int i = 0; i < n; ++i){
        if(used[i]){
            cout << arr[i] << " ";
        }
    }
    cout << "}\n";
}

void generaSubconjuntos(int arr[], bool used[], int n, int actual = 0){
    if(actual == n){
        /**
            Aqui revisas lo que quieras de cada subconjunto
        */
        check(arr, used, n);
        return;
    }

    used[actual] = true; /// elige el elemento actual
    generaSubconjuntos(arr, used, n, actual + 1);
    used[actual] = false; /// no elige el elemento actual
    generaSubconjuntos(arr, used, n, actual + 1);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n = 4;
    int arr[n] = {1, 2, 3, 4};
    bool used[n];

    /// todos los subconjuntos de n elementos
    generaSubconjuntos(arr, used, n);
}
