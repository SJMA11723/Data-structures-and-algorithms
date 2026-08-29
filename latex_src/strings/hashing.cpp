ll bin_exp( ll a, ll exp, ll mod);
ll inv( ll b , ll mod);
ll div( ll a, ll b, ll mod);
struct mystring{
    const ll A = 911382323;
    const ll B = 972663749;
    string s;
    ll hash_val = -1, len = 0;
    mystring(string &s): s(s){
        len = sz(s);
        hash_precalc();
    }
    mystring(ll hash_val, ll len):hash_val(hash_val), len(len){}
    bool operator==(const mystring &o)const{
        return (hash_val == o.hash_val) && (len == o.len);
    }
    bool operator!=(const mystring &other)const{
        return !(*this == other);
    }
    vi h, powA;
    ll hash_precalc(){
        if(hash_val != -1) return hash_val;
        if(len == 0) return hash_val = 0;
        h.resize(len);
        powA.resize(len + 1);
        h[0] = s[0] % B;
        powA[0] = 1;
        for(int i = 1; i < sz(s); ++i){
            h[i] = (h[i-1] * A + s[i]) % B;
            powA[i] = A * powA[i-1] % B;
        }
        powA[len] = powA[len - 1] * A % B;
        hash_val = h[sz(s) - 1];
        return hash_val;
    }
    mystring hash_substring(ll i, ll j){
        if(hash_val == -1) hash_precalc();
        if(i < 0 || j >= len || i > j) return mystring(0, 0);
        if(i == 0) return mystring(h[j], j + 1);
        ll nhash = (h[j] - h[i-1] * powA[j - i + 1] % B + B)%B;
        return mystring(nhash, j - i + 1);
    }
    mystring operator*(ll p)const{
        if( p <= 0 || len == 0 ) return mystring(0, 0);
        if( p == 1) return mystring(hash_val, len);
        ll mult = bin_exp(A, len,   B);
        ll sum_geo;
        if(mult == 1) sum_geo = p % B;
        else{
            ll num = (bin_exp(mult, p,  B) - 1 + B) % B;
            sum_geo = div(num, (mult - 1 + B) % B, B);
        }
        ll new_hash = hash_val * sum_geo % B;
        ll new_len = len * p;
        return mystring(new_hash, new_len);
    }
    mystring operator+(const mystring &o)const{
        ll pA = bin_exp(A, o.len, B);
        ll new_hash = (hash_val * pA % B + o.hash_val) % B;
        ll new_len = len + o.len;
        return mystring(new_hash, new_len);
    }
};
