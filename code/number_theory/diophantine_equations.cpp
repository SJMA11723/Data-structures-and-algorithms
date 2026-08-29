#include "template.h"
/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

ll ext_gcd(ll a, ll b, ll &x, ll &y); // hide

/// Encuentra una solucion para la ecuacion ax + by = c y regresa true. Guarda la solucion en x e y
/// Si la ecuacion no tiene solucion, entonces regresa false
bool find_sol(ll a, ll b, ll c, ll &x, ll &y, ll &g){
    g = ext_gcd(abs(a), abs(b), x, y);
    if(c % g) return false;
    x *= c / g;
    y *= c / g;
    if(a < 0) x = -x;
    if(b < 0) y = -y;
    return true;
}

/// cambia a la siguiente (anterior) solucion abs(cnt) veces. g := gcd(a ,b)
void change_sol(ll &x, ll &y, ll a, ll b, ll cnt, ll g = 1){
    x += cnt * b / g;
    y -= cnt * a / g;
}

/// Cuenta la cantidad de soluciones x, y con x en [minx, maxx] y y en [miny, maxy]
ll cntsol(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy){
    ll x, y, g;
    if(!find_sol(a, b, c, x, y, g)) return 0;

    /// ax + by = c ssi (a/g)x + (b/g)y = c/g
    /// Dividimos entre g para simplificar y no dividir a cada rato
    a /= g; b /= g;

    /// Signos de a, b nos sirven para pasar a la
    /// siguiente (anterior) solucion
    int sign_a = a > 0 ? +1 : -1; int sign_b = b > 0 ? +1 : -1;

    /// pasa a la minima solucion tal que minx <= x
    change_sol(x, y, a, b, (minx - x) / b);
    /// si x < minx, pasa a la siguiente para que minx <= x
    if(x < minx) change_sol(x, y, a, b, sign_b);
    if(x > maxx) return 0; /// si x > maxx, entonces no hay x solucion tal que x in [minx, maxx]
    ll lx1 = x;

    /// pasa a la maxima solucion tal que x <= maxx
    change_sol(x, y, a, b, (maxx - x) / b);
    if(x > maxx) change_sol(x, y, a, b, -sign_b); /// si x > maxx, pasa a la solucion anterior
    ll rx1 = x;

    /// hace todo lo anterior pero con y
    change_sol(x, y, a, b, -(miny - y) / a);
    if(y < miny) change_sol(x, y, a, b, -sign_a);
    if(y > maxy) return 0;
    ll lx2 = x;

    change_sol(x, y, a, b, -(maxy - y) / a);
    if(y > maxy) change_sol(x, y, a, b, sign_a);
    ll rx2 = x;

    /// como al encontrar las x tomando y como criterio no nos asegura
    /// que esten ordenadas, entonces las ordenamos
    if(lx2 > rx2) swap(lx2, rx2);

    /// obtenemos la interseccion de los intervalos
    ll lx = max(lx1, lx2); ll rx = min(rx1, rx2);

    if(lx > rx) return 0; /// no existen soluciones, interseccion vacia

    /// las soluciones (por x) van de b en b (b/g en b/g pero dividimos al principio)
    return (rx - lx) / abs(b) + 1;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll a, b, x, y, c, g;
    cin >> a >> b >> c;
    cout << find_sol(a, b, c, x, y, g) << ' ' << x << ' ' << y;

    /// Cuenta las soluciones con x in [1, 1000] y y in [1, 1000]
    long long x1 = 1, x2 = 1000, y1 = 1, y2 = 1000;
    if(!a && !b){
        if(c) cout << "0\n";
        else cout << (x2 - x1 + 1) * (y2 - y1 + 1) << '\n';
    } else if(!a){
        if(c % b || c/b < y1 || y2 < c/b) cout << "0\n";
        else cout << x2 - x1 + 1 << '\n';
    } else if(!b){
        if(c % a || c/a < x1 || x2 < c/a) cout << "0\n";
        else cout << y2 - y1 + 1 << '\n';
    } else cout << cntsol(a, b, c, x1, x2, y1, y2) << '\n';
}
