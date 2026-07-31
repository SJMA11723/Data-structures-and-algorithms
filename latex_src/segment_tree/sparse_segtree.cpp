#include <bits/stdc++.h>
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
    int64_t query(int64_t l, int64_t r, int64_t L, int64_t R){
        push_lazy(L, R);
        if(r < L || R < l) return 0;
        if(l <= L && R <= r) return sum;
        extend();
        int64_t mid = L + (R - L) / 2;
        return left->query(l, r, L, mid) + right->query(l, r, mid + 1, R);
    }
};
