/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct nodo{
    int left, right;
    int val;
};

struct SegmentTree{
    int n, NEUTRO;
    int *arr;
    nodo *nodos;
    int (*f)(const int &a, const int &b);

    SegmentTree(int n_size, int nums[], int (*func)(const int &a, const int &b), int neutro){
        n = n_size;
        arr = new int[n + 1];
        memcpy(arr, nums, sizeof(int) * (n + 1));
        nodos = new nodo[4*n + 1];
        f = func;
        NEUTRO = neutro;
        build(1, n);
    }

    void build(int l, int r, int pos = 1){
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

    void update(int x, int idx, int pos = 1){
        if(idx < nodos[pos].left || nodos[pos].right < idx) return;

        if(nodos[pos].left == nodos[pos].right){
            arr[idx] += x;
            nodos[pos].val += x;
            return;
        }

        update(x, idx, pos * 2);
        update(x, idx, pos * 2 + 1);

        nodos[pos].val = f(nodos[pos * 2].val, nodos[pos * 2 + 1].val);
    }

    int query(int left, int right, int pos = 1){
        if(right < nodos[pos].left || nodos[pos].right < left) return NEUTRO;

        if(left <= nodos[pos].left && nodos[pos].right <= right)
            return nodos[pos].val;

        return f(query(left, right, pos * 2), query(left, right, pos * 2 + 1));
    }

    ~SegmentTree(){
        delete[] nodos;
        delete[] arr;
    }
};

int suma(const int &a, const int &b){return a + b;}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    int arr[n + 1];
    for(int i = 1; i <= n; ++i) cin >> arr[i];

    SegmentTree seg(n, arr, suma, 0);

    while(q--){
        int a, b;
        char c;
        cin >> c >> a >> b;
        if(c == 'u'){
            seg.update(b, a);
        } else cout << seg.query(a, b) << '\n';
    }

}
