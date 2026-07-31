#include <bits/stdc++.h>
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
        check(arr, n, i);
    }
}
