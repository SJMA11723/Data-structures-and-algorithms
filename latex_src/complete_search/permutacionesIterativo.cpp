#include <bits/stdc++.h>
void check(int arr[], int n){
    for(int i = 0; i < n; ++i)
        cout << arr[i] << ' ';
    cout << '\n';
}
void generaPermutaciones(int arr[], int n){
    do{
        check(arr, n);
    } while(next_permutation(arr, arr + n));
}
