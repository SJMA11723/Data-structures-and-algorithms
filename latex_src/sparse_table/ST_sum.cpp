#include <bits/stdc++.h>
#define MAXN 500005
#define LOGN 21
int n, q;
long long arr[MAXN];
long long STSUM[LOGN][MAXN];
int lg2[MAXN];
void buildST(){
    lg2[1] = 0;
    for(int i = 2; i < MAXN; ++i){
        lg2[i] = lg2[i / 2] + 1;
    }
    for(int i = 0; i < n; ++i){
        STSUM[0][i] = arr[i];
    }
    for(int k = 1; k < LOGN; ++k){
        int fin = (1 << k) - 1;
        for(int i = 0; i + fin < n; ++i){
            STSUM[k][i] = STSUM[k - 1][i] + STSUM[k - 1][i + (1 << (k - 1))];
        }
    }
}
long long computeSum(int l, int r){
    long long sum = 0;
    for(int k = LOGN; 0 <= k; --k){
        if( r - l + 1 < (1 << k) ) continue;
        sum += STSUM[k][l];
        l += 1 << k;
    }
    return sum;
}
