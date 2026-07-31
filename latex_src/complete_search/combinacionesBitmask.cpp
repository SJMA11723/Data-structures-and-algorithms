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
void generaCombinacionesEnM(int arr[], int n, int m){
    if(n < m) return;
    int lim = 1 << n;
    for(int i = 0; i < lim; ++i){
        if(__builtin_popcount(i) == m){
            check(arr, n, i);
        }
    }
}
