/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>
#define lsb(S) (S & (-S))

using namespace std;

struct fenwick_tree{
    int n;
    vector<int> BIT;

    fenwick_tree(int _n){
        n = _n;
        BIT.resize(n + 1);
    }

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
        }
        return res;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    fenwick_tree BIT(n);

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
