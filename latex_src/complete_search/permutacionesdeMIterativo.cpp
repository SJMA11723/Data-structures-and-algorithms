#include <bits/stdc++.h>
void check(int arr[], int n){
    for(int i = 0; i < n; ++i)
        cout << arr[i] << ' ';
    cout << '\n';
}
void generaPermutacionesDeM(int arr[], int n, int m){
    if(n < m) return;
    do{
        check(arr, m);
    } while(next_permutation(arr, arr + n));
}
