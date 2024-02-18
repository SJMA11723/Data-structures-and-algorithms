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

void generaCombinacionesEnM(int arr[], bool used[], int n, int m, int actual = 0){
    if(n < m) return;

    if(actual == n || m == 0){
        if(m != 0) return;
        /**
            Aqui revisas lo que quieras de cada combinacion
        */
        check(arr, used, n);
        return;
    }


    used[actual] = true; /// elige el elemento actual
    generaCombinacionesEnM(arr, used, n, m - 1, actual + 1);
    used[actual] = false; /// no elige el elemento actual
    generaCombinacionesEnM(arr, used, n, m, actual + 1);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n = 4;
    int arr[n] = {1, 2, 3, 4};
    bool used[n];

    int m = 2;
    ///combinaciones de n en m (subconjuntos de m elementos)
    generaCombinacionesEnM(arr, used, n, m);
}
