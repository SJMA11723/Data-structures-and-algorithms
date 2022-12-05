/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct SegmentTree{
    struct nodo{
        int val, lazy;
        nodo():val(0), lazy(0){}/// inicializa con el neutro y sin lazy pendiente
        nodo(int x):val(x){}
        const nodo operator+(const nodo &b)const{
            return nodo(val + b.val);
        }
    }*nodos;
    int *arr;
    SegmentTree(int n){
        arr = new int[n + 1];
        nodos = new nodo[4 * n + 1];
    }

    void pushLazy(int pos, int left, int right){
        int tam = abs(right - left + 1);
        if(1 < tam){
            nodos[pos * 2].lazy += nodos[pos].lazy;
            nodos[pos * 2 + 1].lazy += nodos[pos].lazy;
        }
        /// IMPORTANTE: ESTE UPDATE ES PARA SUMA/RESTA. CAMBIAR SI ES NECESARIO
        nodos[pos].val += nodos[pos].lazy * tam;
        nodos[pos].lazy = 0;
    }

    void update(int x, int l, int r, int left, int right, int pos = 1){
        pushLazy(pos, left, right);
        if(r < left || right < l) return;
        if(l <= left && right <= r){
            nodos[pos].lazy += x;
            pushLazy(pos, left, right);
            return;
        }

        int mitad = (left + right) / 2;
        update(x, l, r, left, mitad, pos * 2);
        update(x, l, r, mitad + 1, right, pos * 2 + 1);

        nodos[pos] = nodos[pos * 2] + nodos[pos * 2 + 1];
    }

    nodo query(int l, int r, int left, int right, int pos = 1){
        pushLazy(pos, left, right);
        if(r < left || right < l) return 0; /// Devuelve el neutro
        if(l <= left && right <= r) return nodos[pos].val;
        int mitad = (left + right) / 2;
        return query(l, r, left, mitad, pos * 2) + query(l, r, mitad + 1, right, pos * 2 + 1);
    }

    ~SegmentTree(){
        delete[] nodos;
        delete[] arr;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    SegmentTree seg(n);
    for(int i = 1; i <= n; ++i){
        int x; cin >> x;
        seg.update(x, i, i, 1, n);
    }

    while(q--){
        int a, b;
        long long x;
        char c;
        cin >> c >> a >> b;
        if(c == 'u'){
            cin >> x;
            seg.update(x, a, b, 1, n);
        } else cout << seg.query(a, b, 1, n).val << '\n';
    }

}
