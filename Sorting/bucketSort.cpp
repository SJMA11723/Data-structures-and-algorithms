#include <bits/stdc++.h>

#define MAXVAL 100

using namespace std;

void bucketSort(int arr[], int n){
    int cub[MAXVAL + 1] = {};

    ///Cuentas la cantidad de elementos de cada valor
    for(int i = 0; i < n; ++i){
        cub[ arr[i] ]++;
    }

    ///reconstruyes el arreglo insertando los elementos de menor a mayor valor
    int idx = 0;
    for(int i = 0; i <= MAXVAL; ++i){
        while( cub[i] ){ ///mientras haya elementos i
            arr[idx] = i; ///agrega el elemeto i a arr
            cub[i]--;
            idx++; ///pasa al siguiente espacio de arr
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int arr[n];

    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    bucketSort(arr, n);

    for(int i = 0; i < n; ++i){
        cout << arr[i] << ' ';
    }
}
