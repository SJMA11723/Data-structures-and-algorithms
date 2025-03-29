/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 10001

using namespace std;

struct segment_tree{
    struct node{
        int val, lazy;
        node():val(0), lazy(0){}/// inicializa con el neutro y sin lazy pendiente
        node(int x, int lz = 0):val(x), lazy(lz){}
        const node operator+(const node &b)const{
            return node(val + b.val);
        }
    };
    vector<node> nodes;
    segment_tree(int n, int data[]){
        nodes.resize(4 * n + 1);
        build(1, n, data);
    }

    void build(int left, int right, int data[], int pos = 1){
        if(left == right){
            nodes[pos] = node(data[left]);
            return;
        }
        int mid = (left + right) / 2;
        build(left, mid, data, pos * 2);
        build(mid + 1, right, data, pos * 2 + 1);
        nodes[pos] = nodes[pos * 2] + nodes[pos * 2 + 1];
    }

    void combine_lazy(int lz, int pos){
        nodes[pos].lazy += lz;
    }

    /// IMPORTANTE: ESTE UPDATE ES PARA SUMA/RESTA. CAMBIAR SI ES NECESARIO
    void apply_lazy(int pos, int tam){
        nodes[pos].val += nodes[pos].lazy * tam;
        nodes[pos].lazy = 0;
    }

    void push_lazy(int pos, int left, int right){
        int len = abs(right - left + 1);
        if(1 < len){
            combine_lazy(nodes[pos].lazy, pos * 2);
            combine_lazy(nodes[pos].lazy, pos * 2 + 1);
        }
        apply_lazy(pos, len);
    }

    void update(int x, int l, int r, int left, int right, int pos = 1){
        push_lazy(pos, left, right);
        if(r < left || right < l) return;
        if(l <= left && right <= r){
            combine_lazy(x, pos);
            push_lazy(pos, left, right);
            return;
        }

        int mid = (left + right) / 2;
        update(x, l, r, left, mid, pos * 2);
        update(x, l, r, mid + 1, right, pos * 2 + 1);
        nodes[pos] = nodes[pos * 2] + nodes[pos * 2 + 1];
    }

    node query(int l, int r, int left, int right, int pos = 1){
        push_lazy(pos, left, right);
        if(r < left || right < l) return node(); /// Devuelve el neutro
        if(l <= left && right <= r) return nodes[pos];
        int mid = (left + right) / 2;
        return query(l, r, left, mid, pos * 2) + query(l, r, mid + 1, right, pos * 2 + 1);
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

    segment_tree seg(n, arr);

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
