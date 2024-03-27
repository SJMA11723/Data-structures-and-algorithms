/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define LOGN 21

using namespace std;

struct sparse_table{
    int n, NEUTRO;
    vector<vector<int>> ST;
    vector<int> lg2;

    /// Funcion/operacion que se aplicara (suma, min, max, gcd, etc)
    int f(int a, int b){
        return a + b;
    }

    /// Recibe la cantidad de elementos, los elementos, la funcion/operacion y el neutro de la funcion
    sparse_table(int _n, int data[]){
        n = _n;
        NEUTRO = 0;

        /// Precalcula logaritmos
        lg2.resize(n + 1);
        lg2[1] = 0;
        for(int i = 2; i <= n; ++i)
            lg2[i] = lg2[i / 2] + 1;

        /// Construye la sparse table
        ST.resize(lg2[n] + 1, vector<int>(n + 1, NEUTRO));
        for(int i = 0; i < n; ++i) ST[0][i] = data[i];
        for(int k = 1; k <= lg2[n]; ++k){
            int fin = (1 << k) - 1;
            for(int i = 0; i + fin < n; ++i)
                ST[k][i] = f(ST[k - 1][i], ST[k - 1][i + (1 << (k - 1))]);
        }
    }

    int query(int l, int r){
        if(l > r) return NEUTRO;
        int ans = NEUTRO;
        for(int k = lg2[n]; 0 <= k; --k){
            if( r - l + 1 < (1 << k) ) continue;
            ans = f(ans, ST[k][l]);
            l += 1 << k;
        }
        return ans;
    }

    int queryIdem(int l, int r){
        /**
            Para funciones/operaciones idempotentes podemos responder en O(1)
            Ejemplo: la funcion min es idempotente
        */
        if(l > r) return NEUTRO;
        int lg = lg2[r - l + 1];
        return f(ST[lg][l], ST[lg][r - (1 << lg) + 1]);
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;

    cin >> n >> q;

    int arr[n];

    /// read n elements
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    sparse_table st(n, arr);

    /// read and answer q sum queries for [l, r], 0 <= l <= r < n
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r; r--; l--;
        cout << "Suma: " << st.query(l, r) << '\n';
    }
}
