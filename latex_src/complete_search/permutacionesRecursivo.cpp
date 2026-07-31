#include <bits/stdc++.h>
void check(int arr[], int n){
    for(int i = 0; i < n; ++i)
        cout << arr[i] << ' ';
    cout << '\n';
}
void generaPermutaciones(int arr[], int n, int actual = 0){
    if(actual == n){
        check(arr, n);
        return;
    }
    for(int i = actual; i < n; ++i){
        swap(arr[i], arr[actual]);
        generaPermutaciones(arr, n, actual + 1);
        swap(arr[i], arr[actual]);
    }
}
