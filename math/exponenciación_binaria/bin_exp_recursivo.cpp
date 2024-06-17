/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

int binExp(int a, int b){
    if(!b) return 1;
    int tmp = binExp(a, b / 2);
    if(b % 2) return tmp * tmp * a;
    return tmp * tmp;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int a, b;
    cin >> a >> b;
    cout << binExp(a, b);
}
