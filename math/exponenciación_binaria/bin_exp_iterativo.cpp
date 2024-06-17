/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

int binExp(int a, int b){
    int ans = 1;
    while(b){
        if(b % 2) ans *= a;
        a *= a;
        b /= 2;
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int a, b;
    cin >> a >> b;
    cout << binExp(a, b);
}
