bool find_sol(ll a, ll b, ll c, ll &x, ll &y, ll &g){
    g = ext_gcd(abs(a), abs(b), x, y);
    if(c % g) return false;
    x *= c / g;
    y *= c / g;
    if(a < 0) x = -x;
    if(b < 0) y = -y;
    return true;
}
void change_sol(ll &x, ll &y, ll a, ll b, ll cnt, ll g = 1){
    x += cnt * b / g;
    y -= cnt * a / g;
}
ll cntsol(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy){
    ll x, y, g;
    if(!find_sol(a, b, c, x, y, g)) return 0;
    a /= g; b /= g;
    int sign_a = a > 0 ? +1 : -1; int sign_b = b > 0 ? +1 : -1;
    change_sol(x, y, a, b, (minx - x) / b);
    if(x < minx) change_sol(x, y, a, b, sign_b);
    if(x > maxx) return 0;
    ll lx1 = x;
    change_sol(x, y, a, b, (maxx - x) / b);
    if(x > maxx) change_sol(x, y, a, b, -sign_b);
    ll rx1 = x;
    change_sol(x, y, a, b, -(miny - y) / a);
    if(y < miny) change_sol(x, y, a, b, -sign_a);
    if(y > maxy) return 0;
    ll lx2 = x;
    change_sol(x, y, a, b, -(maxy - y) / a);
    if(y > maxy) change_sol(x, y, a, b, sign_a);
    ll rx2 = x;
    if(lx2 > rx2) swap(lx2, rx2);
    ll lx = max(lx1, lx2); ll rx = min(rx1, rx2);
    if(lx > rx) return 0;
    return (rx - lx) / abs(b) + 1;
}
