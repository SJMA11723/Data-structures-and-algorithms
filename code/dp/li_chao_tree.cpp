/*  
    * Contest: Topic List : Li Chao Tree
    * URL: https://youkn0wwho.academy/topic-list/li_chao_tree
    * Problem: Segment Add Get Min
    * Status: Accepted
    * Algorithm:  Li Chao Tree sobre coordenadas comprimidas (solo los p de las consultas de tipo 1),
    *            con inserción de segmentos como Segment Tree descomponiendo [l, r) en O(log M) nodos
    * Complexity: O(Q log^2 M) tiempo para insertar segmentos, O(log M) por consulta, O(M) memoria
    *             (M = numero de valores p distintos, N = segmentos iniciales, Q = consultas)
    * angelmanuelgl
*/
#include<bits/stdc++.h>
using namespace std;

// --- Type Aliases ---
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

// --- Short Macros ---
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()


// --- DEBUGER SETUP ---
#ifdef LOCAL
    bool debug = true;
    #define print(...) logger (#__VA_ARGS__,__VA_ARGS__)
#else
    bool debug = false;
    #define print(...)
#endif

#define DEBUG if(debug)
#define DEBUG1 DEBUG cout <<
#define DEBUG2 DEBUG1 "\n" << 
#define DEBUG3 DEBUG1 "\n";
#define NODEBUG if(!debug)

// Overload for std::pair
template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.fi << ", " << p.se << ')';
}
// Overload for Containers (excluding std::string) via SFINAE
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v) {
    string sep;
    for(const T &x : v) os << sep << x, sep = " ";
    return os;
}
// Logger Func
template<typename ...Args>
void logger(string vars, Args&&... vals){
    if( !debug ) return;
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << vals, d = "] ["));
    cout << "]\n";
}

const int MOD = 1e9 + 7;

struct Func {
	ll m,b;
	ll eval(ll x){
		if( m == LLONG_MAX) return LLONG_MAX;
		return (ll)((__int128_t)m * x + b);
	}
	Func(){ m = LLONG_MAX;}
	Func(ll m_, ll b_): m(m_), b(b_){ }

};
ostream& operator<<(ostream &os, const Func &f){
    return  os << f.m << "x+" << f.b ; 
}
struct LiChaoTree {
	vll vals;
	ll maxV;
	Func *treefunc;
	LiChaoTree(vll &vals_){
		vals = vals_;
		sort(all(vals));
        vals.erase( std::unique( all(vals) ), vals.end() );
		treefunc = new Func[sz(vals) * 4 + 5];
		maxV = sz(vals);
	}
	void addFunction(Func f){ addFunction(f, 1, 0, maxV); }
	void addFunction(Func f, ll v, int l, int r){
		int m = l + (r - l) / 2;
        ll mv = vals[m];
        ll lv = vals[l];
        bool lef = f.eval(lv) < treefunc[v].eval(lv); // min
        bool mid = f.eval(mv) < treefunc[v].eval(mv); // min
        if(mid) swap(treefunc[v], f);
        if(r - l == 1) return;
        else if(lef != mid) addFunction(f, 2 * v, l, m); 
        else addFunction(f, 2 * v + 1, m, r);
	}  
    void addSegFunction( Func fi, int l, int r){//[l,r)->[i,j)
        l = lower_bound(all(vals), (ll)l) - vals.begin();
        r = lower_bound(all(vals), (ll)r) - vals.begin();
        if( l < r ) addSeg(fi,l,r, 1,0,maxV );
    }
    void addSeg(Func fi,int l,int r,int v,int left,int right){
        if( r <= left  || right <= l) return;
        if( l <= left  && right <=  r  ){
            addFunction( fi, v, left, right);
            return; 
        }
        if( left +1 == right)  return;
        int m =  left + (right-left)/2;
        addSeg(fi, l, r, v * 2     , left, m);
        addSeg(fi, l, r, v * 2 + 1 , m, right);
    }
    ll get(ll x){ return get(x, 1, 0, maxV); }
	ll get(ll x, int v, int l, int r){
        ll cur = treefunc[v].eval(x);
        if(r - l == 1) return cur;
        int m = l + (r - l) / 2;
        ll mv = vals[m];
        if(x < mv) return min(cur, get(x, 2 * v, l, m)); //min
        else return min(cur, get(x, 2 * v + 1, m, r)); //min
	}
	~LiChaoTree(){ delete[] treefunc; }
};

// // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // //

struct query{
    int tipo;
    ll l,r,a,b; // agregar f(x) = a x + b en [l,r]
    ll v; // minimo f_i(v)

};

// uso :  g++ -DLOCAL A.cpp
int main(){
    #ifdef LOCAL
        ifstream cin("in.in");
    #else
        ios_base::sync_with_stdio(0); 
        cin.tie(0);
        cout.tie(0);
    #endif

    int n,q; cin >> n >> q;

    // rectas f(x) = ax + b en segmentos [l,r]
    vll l(n),r(n),a(n),b(n);
    for( int i=0; i<n; i++){
        cin >> l[i] >> r[i] >> a[i] >> b[i];
    }

    // queries
    vector<query> queries(q);
    vll vals;
    set<ll> used;
    for( int i=0; i<q; i++){
        cin >> queries[i].tipo;
        // agregar otra recta
        if( queries[i].tipo == 0 ){
            cin >> queries[i].l >> queries[i].r >> queries[i].a >> queries[i].b;
        }
        // cosulta // min_i f_i(v)
        if( queries[i].tipo == 1){
            int v; cin >> v;
            queries[i].v = v;
            if( !used.count(v) ){ 
                vals.pb( queries[i].v);
                used.insert(v);
            }
        }
    }

    sort( all(vals) );
    print(vals);

    LiChaoTree lct(vals); // O( M log M) // M = sz(vals)

    print(vals);

    // agregar funciones // O( N log M ) // N functions
    for( int i=0; i<n; i++){
        DEBUG2 "agregar funcion:\n";
        print( a[i],b[i], l[i], r[i]);
        lct.addSegFunction( {a[i],b[i]}, l[i], r[i] );
    }

     for( int i=0; i<q; i++){
        // agregar otra recta
        if( queries[i].tipo == 0 ){
            DEBUG2 "quiery add:\n";
            print(queries[i].a,queries[i].b, queries[i].l, queries[i].r);
            lct.addSegFunction( {queries[i].a,queries[i].b},queries[i].l,queries[i].r );
        }
        // cosulta // min_i f_i(v)
        if( queries[i].tipo == 1){
            DEBUG2 "queri consulta\n";
            print( queries[i].v  );
            ll ans = lct.get( queries[i].v );
            if( ans != LLONG_MAX ) cout << ans << "\n";
            else cout << "INFINITY\n";
        }
    }



    
}