/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct nodo{
    int left, right;
    long long val;
};

struct SegmentTree{
    int n;
    const long long NEUTRO = 0;
    long long *arr;
    nodo *nodos, *lazy;

    SegmentTree(int sz){
        n = sz;
        arr = new long long[n + 1];
        nodos = new nodo[4*n + 1];
        lazy = new nodo[4*n + 1];
    }

    void scanValues(){
        for(int i = 1; i <= n; ++i)
            cin >> arr[i];
    }

    /// calcula la operacion deseada en el segment tree
    long long f(const long long &a, const long long &b){
        return a + b;
    }

    void build(int l, int r, int pos = 1){
        lazy[pos].val = 0;

        nodos[pos].left = l;
        nodos[pos].right = r;

        if(nodos[pos].left == nodos[pos].right){
            nodos[pos].val = arr[r];
            return;
        }

        int mitad = (nodos[pos].left + nodos[pos].right) / 2;

        build(l, mitad, pos * 2);
        build(mitad + 1, r, pos * 2 + 1);

        nodos[pos].val = f(nodos[pos * 2].val, nodos[pos * 2 + 1].val);
    }

    void pushLazy(int pos){
        ///izq
        long long left = nodos[pos].left,
            right = nodos[pos].right,
            tam = abs(right - left + 1);

        if(1 < tam){
            lazy[pos * 2].val += lazy[pos].val;
            lazy[pos * 2 + 1].val += lazy[pos].val;
        }
        nodos[pos].val += lazy[pos].val * tam;
        lazy[pos].val = 0;
    }

    void update(long long x, int left, int right, int pos = 1){
        pushLazy(pos);

        if(right < nodos[pos].left || nodos[pos].right < left) return;

        if(left <= nodos[pos].left && nodos[pos].right <= right){
            lazy[pos].val += x;
            pushLazy(pos);
            return;
        }

        update(x, left, right, pos * 2);
        update(x, left, right, pos * 2 + 1);

        nodos[pos].val = f(nodos[pos * 2].val, nodos[pos * 2 + 1].val);
    }

    long long query(int left, int right, int pos = 1){
        pushLazy(pos);

        if(right < nodos[pos].left || nodos[pos].right < left) return NEUTRO;

        if(left <= nodos[pos].left && nodos[pos].right <= right)
            return nodos[pos].val;

        return f(query(left, right, pos * 2), query(left, right, pos * 2 + 1));
    }

    ~SegmentTree(){
        delete[] nodos;
        delete[] lazy;
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

    seg.scanValues();
    seg.build(1, n);

    while(q--){
        int a, b;
        long long x;
        char c;
        cin >> c >> a >> b;
        if(c == 'u'){
            cin >> x;
            seg.update(x, a, b);
        } else cout << seg.query(a, b) << '\n';
    }

}
