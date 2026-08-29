#include <bits/stdc++.h>
#define MAXVAL 100
void bucketSort(int arr[], int n){
    int cub[MAXVAL + 1] = {};
    for(int i = 0; i < n; ++i){
        cub[ arr[i] ]++;
    }
    int idx = 0;
    for(int i = 0; i <= MAXVAL; ++i){
        while( cub[i] ){
            arr[idx] = i;
            cub[i]--;
            idx++;
        }
    }
}
