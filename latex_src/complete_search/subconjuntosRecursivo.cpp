#include <bits/stdc++.h>
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
        check(arr, used, n);
        return;
    }
    used[actual] = true; /// elige el elemento actual
    generaSubconjuntos(arr, used, n, actual + 1);
    used[actual] = false; /// no elige el elemento actual
    generaSubconjuntos(arr, used, n, actual + 1);
}
