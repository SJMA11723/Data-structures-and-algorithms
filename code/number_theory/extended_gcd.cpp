#include "template.h"
/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

/// Resuelve la ecuacion ax + bx = gcd(a, b) y guarda la solucion en x e y
ll ext_gcd(ll a, ll b, ll &x, ll &y){
    if(!b) return x = 1, y = 0, a;
    ll g = ext_gcd(b, a % b, y, x);
    return y -= a / b * x, g;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll a, b, x, y;
    cin >> a >> b;
    cout << ext_gcd(a, b, x, y) << ' ' << x << ' ' << y;
}
