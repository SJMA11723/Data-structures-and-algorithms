/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct SegmentTree{
    struct node{
        int val, lazy;
        node():val(0), lazy(0){}/// inicializa con el neutro y sin lazy pendiente
        node(int x, int lz = 0):val(x), lazy(lz){}
        const node operator+(const node &b)const{
            return node(val + b.val);
        }
    }*nodes;
    SegmentTree(int n, int data[]){
        nodes = new node[4*n + 1];
        build(1, n, data);
    }

    void build(int left, int right, int data[], int pos = 1){
        if(left == right){
            nodes[pos].val = data[left];
            return;
        }
        int mid = (left + right) / 2;
        build(left, mid, data, pos * 2);
        build(mid + 1, right, data, pos * 2 + 1);
        nodes[pos] = nodes[pos * 2] + nodes[pos * 2 + 1];
    }

    void combineLazy(int lz, int pos){
        nodes[pos].lazy += lz;
    }

    /// IMPORTANTE: ESTE UPDATE ES PARA SUMA/RESTA. CAMBIAR SI ES NECESARIO
    void applyLazy(int pos, int tam){
        nodes[pos].val += nodes[pos].lazy * tam;
        nodes[pos].lazy = 0;
    }

    void pushLazy(int pos, int left, int right){
        int tam = abs(right - left + 1);
        if(1 < tam){
            combineLazy(nodes[pos].lazy, pos * 2);
            combineLazy(nodes[pos].lazy, pos * 2 + 1);
        }
        applyLazy(pos, tam);
    }

    void update(int x, int l, int r, int left, int right, int pos = 1){
        pushLazy(pos, left, right);
        if(r < left || right < l) return;
        if(l <= left && right <= r){
            combineLazy(x, pos);
            pushLazy(pos, left, right);
            return;
        }

        int mid = (left + right) / 2;
        update(x, l, r, left, mid, pos * 2);
        update(x, l, r, mid + 1, right, pos * 2 + 1);
        nodes[pos] = nodes[pos * 2] + nodes[pos * 2 + 1];
    }

    node query(int l, int r, int left, int right, int pos = 1){
        pushLazy(pos, left, right);
        if(r < left || right < l) return node(0); /// Devuelve el neutro
        if(l <= left && right <= r) return nodes[pos];
        int mid = (left + right) / 2;
        return query(l, r, left, mid, pos * 2) + query(l, r, mid + 1, right, pos * 2 + 1);
    }

    ~SegmentTree(){
        delete[] nodes;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    int arr[n + 1];
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    SegmentTree seg(n, arr);

    while(q--){
        int a, b;
        long long x;
        char c;
        cin >> c >> a >> b;
        if(c == 'u'){
            cin >> x;
            seg.update(x, a, b, 1, n);
        } else if(c == 'q') cout << seg.query(a, b, 1, n).val << '\n';
    }

}
