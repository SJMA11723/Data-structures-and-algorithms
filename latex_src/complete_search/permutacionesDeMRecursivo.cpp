#include <bits/stdc++.h>
void check(int arr[], int n){
    for(int i = 0; i < n; ++i)
        cout << arr[i] << ' ';
    cout << '\n';
}
void generaPermutacionesDeM(int arr[], int n, int m, int actual = 0){
    if(n < m) return;
    if(actual == m){
        check(arr, m);
        return;
    }
    for(int i = actual; i < n; ++i){
        swap(arr[i], arr[actual]);
        generaPermutacionesDeM(arr, n, m, actual + 1);
        swap(arr[i], arr[actual]);
    }
}
