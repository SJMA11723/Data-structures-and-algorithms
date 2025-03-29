/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct node{
    int64_t lazy, maxi, sum;
    node *left = nullptr, *right = nullptr;
    node(): lazy(0), maxi(0), sum(0){}

    void extend(){
        if(left) return;
        left = new node;
        right = new node;
    }

    void combine_lazy(int64_t lz){
        lazy += lz;
    }

    void apply_lazy(int64_t len){
        sum += len * lazy;
        lazy = 0;
    }

    void push_lazy(int64_t L, int64_t R){
        int len = R - L + 1;
        int64_t mid = L + (R - L) / 2;
        if(len){
            extend();
            left->combine_lazy(lazy);
            right->combine_lazy(lazy);
        }
        apply_lazy(len);
    }

    void update(int64_t x, int64_t l, int64_t r, int64_t L, int64_t R){
        push_lazy(L, R);
        if(r < L || R < l) return;
        if(l <= L && R <= r){
            combine_lazy(x);
            push_lazy(L, R);
            return;
        }

        int64_t mid = L + (R - L) / 2;

        extend();
        left->update(x, l, r, L, mid);
        right->update(x, l, r, mid + 1, R);
        sum = left->sum + right->sum;
    }

    /// max
    int64_t query(int64_t l, int64_t r, int64_t L, int64_t R){
        push_lazy(L, R);
        if(r < L || R < l) return 0;
        if(l <= L && R <= r) return sum;

        extend();
        int64_t mid = L + (R - L) / 2;
        return left->query(l, r, L, mid) + right->query(l, r, mid + 1, R);
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    node *root = new node;
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; ++i){
        int x; cin >> x;
        root->update(x, i, i, 0, n - 1);
    }

    while(q--){
        int c; cin >> c;
        if(c){
            int l, r; cin >> l >> r; r--;
            cout << root->query(l, r, 0, n - 1) << '\n';
        } else {
            int p, x; cin >> p >> x;
            root->update(x, p, p, 0, n - 1);
        }
    }
}
