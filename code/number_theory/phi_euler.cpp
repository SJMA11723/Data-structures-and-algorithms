#include "template.h"

/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

vi calc_phi(int n){
    vi phi(n + 1);
    for(int i = 0; i <= n; ++i) phi[i] = i & 1 ? i : i / 2;
    for(int i = 3; i <= n; i += 2) if(phi[i] == i)
    for(int j = i; j <= n; j += i) phi[j] -= phi[j] / i;
    return phi;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vi phi = calc_phi(1e6);
}
