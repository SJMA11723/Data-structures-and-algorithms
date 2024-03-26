/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 10001

using namespace std;

struct dsu{
    int RA[MAXN], P[MAXN];

    dsu(int n){
        for(int i = 0; i < n; ++i){
            RA[i] = 1;
            P[i] = i;
        }
    }

    int root(int x){
        if(x == P[x]) return x;
        return P[x] = root(P[x]);
    }

    void join(int x, int y){
        x = root(x);
        y = root(y);
        if(x == y) return;
        if(RA[x] >= RA[y]) swap(x, y);
        RA[y] += RA[x];
        P[x] = y;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
