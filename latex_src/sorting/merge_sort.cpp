#include <bits/stdc++.h>
void mergeSort(int arr[], int ini, int fin){
    if(ini == fin) return;
    int mitad = (ini + fin) / 2;
    mergeSort(arr, ini, mitad);
    mergeSort(arr, mitad + 1, fin);
    int tam1 = mitad - ini + 1, tam2 = fin - mitad;
    int mitad1[tam1], mitad2[tam2];
    for(int i = ini, idx = 0; i <= mitad; ++i, idx++)
        mitad1[idx] = arr[i];
    for(int i = mitad + 1, idx = 0; i <= fin; ++i, idx++)
        mitad2[idx] = arr[i];
    for(int i = ini, idx1 = 0, idx2 = 0; i <= fin; ++i){
        if(idx1 < tam1 && idx2 < tam2){
            arr[i] = mitad1[idx1] < mitad2[idx2] ? mitad1[idx1++] : mitad2[idx2++];
        } else {
            arr[i] = idx1 < tam1 ? mitad1[idx1++] : mitad2[idx2++];
        }
    }
}
