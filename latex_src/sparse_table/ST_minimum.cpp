#include <bits/stdc++.h>
#define MAXN 500005
#define LOGN 21
int n, q;
int arr[MAXN];
int STMIN[LOGN][MAXN];
int lg2[MAXN];
void buildST(){
    lg2[1] = 0;
    for(int i = 2; i < MAXN; ++i){
        lg2[i] = lg2[i / 2] + 1;
    }
    for(int i = 0; i < n; ++i){
        STMIN[0][i] = arr[i];
    }
    for(int k = 1; k < LOGN; ++k){
        int fin = (1 << k) - 1;
        for(int i = 0; i + fin < n; ++i){
            STMIN[k][i] = min(STMIN[k - 1][i], STMIN[k - 1][i + (1 << (k - 1))]);
        }
    }
}
int computeMin(int l, int r){
    int lg = lg2[r - l + 1];
    return min(STMIN[lg][l], STMIN[lg][r - (1 << lg) + 1]);
}
