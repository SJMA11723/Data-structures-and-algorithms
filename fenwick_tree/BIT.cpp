/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define MAXN 1000

using namespace std;

struct FenwickTree{
    int n, BIT[MAXN];

    FenwickTree(int n_size){
        n = n_size;
        memset(BIT, 0, sizeof(BIT));
    }

    void add(int pos, int x){
        while(pos <= n){
            BIT[pos] += x;
            pos += pos & -pos;
        }
    }

    int sum(int pos){
        int ret = 0;
        while(pos){
            ret += BIT[pos];
            pos -= pos & -pos;
        }
        return ret;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    FenwickTree BIT(n);

    for(int i = 1; i <= n; ++i){
        int x;
        cin >> x;
        BIT.add(i, x);
    }
    int k;
    cin >> k;
    while(k--){
        int a, b;
        char c;
        cin >> c >> a >> b;
        a++; b++;
        if(c == 'C') BIT.add(a, b - (BIT.sum(a) - BIT.sum(a - 1)) - 1);
        else cout << BIT.sum(b - 1) - BIT.sum(a - 1) << '\n';
    }
}
