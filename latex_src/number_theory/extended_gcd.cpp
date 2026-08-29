ll ext_gcd(ll a, ll b, ll &x, ll &y){
    if(!b) return x = 1, y = 0, a;
    ll g = ext_gcd(b, a % b, y, x);
    return y -= a / b * x, g;
}
