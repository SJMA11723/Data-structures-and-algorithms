#include "../template.h"
#define lsb(S) ((S) & (-S))
struct fenwick_tree{
    int n;
    vi BIT;
    fenwick_tree(int _n): n(_n){BIT.resize(n + 1);}
    void add(int pos, int x){
        while(pos <= n){
            BIT[pos] += x;
            pos += lsb(pos);
        }
    }
    int sum(int pos){
        int res = 0;
        while(pos){
            res += BIT[pos];
            pos -= lsb(pos);
        } return res;
    }
};
