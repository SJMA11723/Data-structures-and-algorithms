/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
/**
    Sparse table
*/

using namespace std;

struct SparseTable{
    int n;
    int NEUTRO;
    int **ST;
    int *lg2;

    /// Funcion/operacion que se aplicara (suma, min, max, gcd, etc)
    int (*f)(int a, int b);

    /// Recibe la cantidad de elementos, los elementos, la funcion/operacion y el neutro de la funcion
    SparseTable(int n_size, int nums[], int (*func)(int a, int b), int neutro){
        n = n_size;
        lg2 = new int[n + 1];
        f = func;
        NEUTRO = neutro;

        /// Precalcula logaritmos
        lg2[1] = 0;
        for(int i = 2; i <= n; ++i)
            lg2[i] = lg2[i / 2] + 1;

        /// Inicializa la sparse table con el neutro
        ST = new int*[n];
        for(int i = 0; i < n; ++i){
            ST[i] = new int[lg2[n] + 1];
            fill(ST[i], ST[i] + lg2[n] + 1, NEUTRO);
        }

        /// Construye la sparse table
        for(int i = 0; i < n; ++i)
            ST[i][0] = nums[i];
        for(int k = 1; k <= lg2[n]; ++k){
            int fin = (1 << k) - 1;
            for(int i = 0; i + fin < n; ++i){
                ST[i][k] = f(ST[i][k - 1], ST[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    int query(int l, int r){
        int ans = NEUTRO;
        for(int k = lg2[n]; 0 <= k; --k){
            if( r - l + 1 < (1 << k) ) continue;
            ans = f(ans, ST[l][k]);
            l += 1 << k;
        }
        return ans;
    }

    int queryIdem(int l, int r){
        /**
            Para funciones/operaciones idempotentes podemos responder en O(1)
            Ejemplo: la funcion min es idempotente
        */
        int lg = lg2[r - l + 1];
        return f(ST[l][lg], ST[r - (1 << lg) + 1][lg]);
    }

    ~SparseTable(){
        for(int i = 0; i < n; ++i) delete[] ST[i];
        delete[] ST;
        delete[] lg2;
    }
};

int suma(int a, int b){return a + b;}
int mini(int a, int b){return a < b ? a : b;}

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

    SparseTable st_sum = SparseTable(n, arr, suma, 0);
    SparseTable st_min = SparseTable(n, arr, mini, INT_MAX);

    /// read and answer q sum queries for [l, r], 0 <= l <= r < n
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r; r--; l--;
        cout << "Suma: " << st_sum.query(l, r) << '\n';
        cout << "Minimo: " << st_min.queryIdem(l, r) << '\n';
    }
}
