#include <bits/stdc++.h>
#define MAXN 500005
#define LOGN 21

/**
    Sparse table - range sum
*/

using namespace std;

int n, q;
long long arr[MAXN];
long long STSUM[LOGN][MAXN];
int lg2[MAXN];

void buildST(){
    /// precompute logarithms
    lg2[1] = 0;
    for(int i = 2; i < MAXN; ++i){
        lg2[i] = lg2[i / 2] + 1;
    }

    for(int i = 0; i < n; ++i){
        STSUM[0][i] = arr[i];
    }

    ///build sum
    for(int k = 1; k < LOGN; ++k){
        int fin = (1 << k) - 1;
        for(int i = 0; i + fin < n; ++i){
            STSUM[k][i] = STSUM[k - 1][i] + STSUM[k - 1][i + (1 << (k - 1))];
        }
    }
}

long long computeSum(int l, int r){
    long long sum = 0;
    /// acumula las sumas de los rangos potencias de 2 que conforman al rango [l, r]
    for(int k = LOGN; 0 <= k; --k){
        if( r - l + 1 < (1 << k) ) continue;

        sum += STSUM[k][l];
        l += 1 << k;
    }

    return sum;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;

    /// read n elements
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    buildST();

    /// read and answer q sum queries for [l, r], 0 <= l <= r < n
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r;
        cout << computeSum(l, r) << '\n';
    }
}
