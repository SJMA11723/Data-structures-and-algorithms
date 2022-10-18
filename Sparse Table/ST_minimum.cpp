#include <bits/stdc++.h>
#define MAXN 500005
#define LOGN 21

/**
    Sparse table - minimum/maximum
*/

using namespace std;

int n, q;
int arr[MAXN];
int STMIN[MAXN][LOGN];
int lg2[MAXN];

void buildST(){
    for(int i = 0; i < n; ++i){
        STMIN[i][0] = arr[i];
    }

    ///build min
    for(int k = 1; k < LOGN; ++k){
        int fin = (1 << k) - 1;
        for(int i = 0; i + fin < n; ++i){
            STMIN[i][k] = min(STMIN[i][k - 1], STMIN[i + (1 << (k - 1))][k - 1]);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    /// precompute logarithms
    lg2[1] = 0;
    for(int i = 2; i < MAXN; ++i){
        lg2[i] = lg2[i / 2] + 1;
    }

    cin >> n >> q;

    /// read n elements
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    buildST();

    /// read and answer q minimum queries for [l, r], 0 <= l <= r < n
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r;

        int lg = lg2[r - l + 1];
        cout << min(STMIN[l][lg], STMIN[r - (1 << lg) + 1][lg]) << '\n';
    }
}
