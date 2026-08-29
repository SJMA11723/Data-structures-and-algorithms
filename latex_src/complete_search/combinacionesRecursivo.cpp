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
void generaCombinacionesEnM(int arr[], bool used[], int n, int m, int actual = 0){
    if(n < m) return;
    if(actual == n || m == 0){
        if(m != 0) return;
        check(arr, used, n);
        return;
    }
    used[actual] = true;
    generaCombinacionesEnM(arr, used, n, m - 1, actual + 1);
    used[actual] = false;
    generaCombinacionesEnM(arr, used, n, m, actual + 1);
}
