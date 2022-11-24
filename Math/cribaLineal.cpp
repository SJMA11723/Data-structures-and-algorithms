/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

void cribaLineal(int n, vector<int> &primos){
    int lp[n + 1] = {};
    bool no_primo[n + 1] = {};
    no_primo[0] = no_primo[1] = true;

    primos.clear();
    for(long long i = 2; i <= n; ++i){
        if(!lp[i]){
            lp[i] = i;
            primos.push_back(i);
        }

        for(int j = 0; i * (long long)primos[j] <= n; ++j){
            lp[i * primos[j]] = primos[j];
            if(primos[j] == lp[i])
                break;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n = 200;
    vector<int> primos;
    cribaLineal(n, primos);
    for(int it : primos){
        cout << it << ' ';
    }
}
