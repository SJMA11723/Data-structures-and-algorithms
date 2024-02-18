#include <bits/stdc++.h>

using namespace std;

void mergeSort(int arr[], int ini, int fin){
    if(ini == fin) return;

    int mitad = (ini + fin) / 2;

    ///ordenar mitades
    mergeSort(arr, ini, mitad);
    mergeSort(arr, mitad + 1, fin);

    ///unir los subarreglos
    int tam1 = mitad - ini + 1, tam2 = fin - mitad;
    int mitad1[tam1], mitad2[tam2];

    ///guardo las mitades
    for(int i = ini, idx = 0; i <= mitad; ++i, idx++)
        mitad1[idx] = arr[i];

    for(int i = mitad + 1, idx = 0; i <= fin; ++i, idx++)
        mitad2[idx] = arr[i];


    for(int i = ini, idx1 = 0, idx2 = 0; i <= fin; ++i){
        if(idx1 < tam1 && idx2 < tam2){ /// si quedan elementos en ambas mitades
            arr[i] = mitad1[idx1] < mitad2[idx2] ? mitad1[idx1++] : mitad2[idx2++];
        } else {
            arr[i] = idx1 < tam1 ? mitad1[idx1++] : mitad2[idx2++];
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
    for(int i = 0; i < n; ++i) cin >> arr[i];

    mergeSort(arr, 0, n - 1);

    for(int i = 0; i < n; ++i){
        cout << arr[i] << ' ';
    }
}
