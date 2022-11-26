/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

int gcdExtendido(int a, int b, int &x, int &y){
    if(!b){
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = gcdExtendido(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

/// Encuentra una solucion para la ecuacion ax + by = c y regresa true. Guarda la solucion en x e y
/// Si la ecuacion no tiene solucion, entonces regresa false
bool encuentra_solucion(int a, int b, int c, int &x, int &y){
    int g = gcdExtendido(abs(a), abs(b), x, y);
    if(c % g) return false;
    x *= c / g;
    y *= c / g;
    if(a < 0) x = -x;
    if(b < 0) y = -y;
    return true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int a, b, x, y, c;
    cin >> a >> b >> c;
    cout << encuentra_solucion(a, b, c, x, y) << ' ' << x << ' ' << y;
}
