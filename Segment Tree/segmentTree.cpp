/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct SegmentTree{
    struct nodo{
        int val;
        nodo():val(0){}/// inicializa con el neutro
        nodo(int x):val(x){}
        const nodo operator+(const nodo &b)const{
            return nodo(val + b.val);
        }
    }*nodos;
    int *arr;
    SegmentTree(int n){
        arr = new int[n + 1];
        nodos = new nodo[4*n + 1];
    }

    void update(int x, int idx, int left, int right, int pos = 1){
        if(idx < left || right < idx) return;
        if(left == right){
            arr[idx] += x;
            nodos[pos].val += x;
            return;
        }

        int mitad = (left + right) / 2;
        update(x, idx, left, mitad, pos * 2);
        update(x, idx, mitad + 1, right, pos * 2 + 1);

        nodos[pos] = nodos[pos * 2] + nodos[pos * 2 + 1];
    }

    nodo query(int l, int r, int left, int right, int pos = 1){
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
        seg.update(x, i, 1, n);
    }

    while(q--){
        int a, b;
        char c;
        cin >> c >> a >> b;
        if(c == 'u'){
            seg.update(b, a, 1, n);
        } else cout << seg.query(a, b, 1, n).val << '\n';
    }

}
