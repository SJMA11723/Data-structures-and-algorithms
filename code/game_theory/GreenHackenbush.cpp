#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distr(1, LLONG_MAX);
const int MOD = 1e9 + 7;
// --- DEBUGER SETUP ---
#ifdef LOCAL
    bool debug = true;
#else
    bool debug = false;
#endif

#define DEBUG if(debug)
#define NODEBUG if(!debug)
//
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p){return os << '(' << p.fi << ", " << p.se << ')';}
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v){string sep; for(const T &x : v) os << sep << x, sep = " "; return os;}
#define print(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values){
    if( !debug ) return;
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << values, d = "] ["));
    cout << "]\n";
}


struct dsu{
    struct action{
        int x_p, y_p;
        int rank_y;
    };
    vi RA, P;
    vector<action> actions;
    dsu(int n){
        RA.resize(n, 1);
        P.resize(n);
        iota(all(P), 0);
    }
    int root(int x){
        return x == P[x] ? x : P[x] = root(P[x]);
    }
    void join(int x, int y, bool recording){
        x = root(x);
        y = root(y);
        if(x == y) return;
        if(RA[x] >= RA[y]) swap(x, y);
        if(recording) actions.pb({x, y, RA[y]});
        RA[y] += RA[x];
        P[x] = y;
    }
    void rollback(int cnt){
        while(cnt-- > 0 && sz(actions)){
            action act = actions.back();
            actions.pop_back();
            RA[act.y_p] = act.rank_y;
            P[act.x_p] = act.x_p;
        }
    }
};

struct edge{
    int from, to;
};


struct hackenbush_result{
    // transformar el original al arbol compacto
    int cntRepresentantes; // cantidades de nuevos nodos 
    vi compactados;  // dado el vertice original nos el nodo compacto que le corresponde //  -1 si no llega al suelo.

    // el arbol compacto es de tam cntRepresentantes (antes de nuevas hojas)
    int root;      // el indice del piso en el arbol 
    vvi tree;      // arbol equivalente

    vi paridad;     // paridad de lazos en el arbol compactados 
    vi nim;        // valor de cada subarbol, sin su arista hacia el padre 

    // respuesta
    int value; // pierdes si value = 0
};

// notas:
// n incluye al nodo 0
// vertices [0,n)
// cada arista aparece UNA vez (son no dirigidas)
// asi que peudes poner dobles aristas {1,2} {1,2} a edges
// por si acaso: mas_suelo contiene puntos adicionales del suelo
// 0 siempre pertenece al suelo).

/// T:  O( (n+m)*alpha(n) )
/// M:  memoria O(n+m)
hackenbush_result green_hackenbush(int n, vector<edge> edges, const vi &mas_suelo = {}){
    // --- --- SUELO --- ---
    // identificar contactos con 0 ANTES del DFS.
    // una arista real entre dos contactos se vuelve lazo y NO se elimina
    // en normalizado esta el nuevo grafo
    vi normalizado(n);
    iota(all(normalizado), 0); // normalizado[i] = i
    for(int u : mas_suelo){
        normalizado[u] = 0;
    }
    // la lista de adyacencia para guardar aristas
    // esta sobre el grafo normalizado
    vvi adj(n); 
    // sobreescribimos los edges para que tomen en cuenta estos nodos
    for(int i = 0; i < sz(edges); i++){
        edge &e = edges[i];
        e.from = normalizado[e.from];
        e.to = normalizado[e.to];
        // en la lista de adyacencia guardamos el indice de la arista
        adj[e.from].pb(i);
        if(e.from != e.to) adj[e.to].pb(i);
    }
    // esto solo es necesario en caso de que existan nodos suelo dados por el porblema 

    // --- --- DFS TREE INTENTO INTERATIVO --- ---
    // lo hacemos sobre el normalizado ya que la lista de adyacencia esta hecha sobre el

    /// La pila contiene el camino activo del DFS
    // para conservar la propiedad ancestro/back-edge
    vi pendiente = {0};
    dsu unidos_para_compactar(n);
    /// usados para el postorden e ir uniendo
    vi depth(n, -1); // profundidad (de arriba a bajo)
    vi low(n); // nos dice la back-edge mas alta
    depth[0] = low[0] = 0; 
    /// representacion del dfs tree
    vi parent(n, -1), parent_edge(n, -1); 
    /// utilidades para hacerlo recursivo
    vi next(n,0);  // guarda el siguiente vecino por explorar de este nodo
    

    while( sz(pendiente) ){
        // el nodo a procesar
        int u = pendiente.back();

        // si aun tenemos por explorar
        if(next[u] < sz(adj[u])){
            // tomamos el next[u]-esimo vecino de la lista de adyacencia de u
            // notar que en la lista de adyacencia tenemos edges
            // para la sigueinte queremos ver el next[u]+1
            int id = adj[u][next[u]++];

            // omitir padre solo si es de esta arista
            // no es lo mismo que si vecino == padre 
            // por el caso a -> b -> c con a == b
            if(id == parent_edge[u]) continue;
            
            // cuidado con las aristas, son no dirigidas
            // vamos de u -> v
            const edge &e = edges[id];
            int v = (e.from == u ? e.to : e.from);
            if(v == u) continue; // si es lazo

            // los lazos los vamos a contar despues 

            // si no hemos pasado por esto 
            if(depth[v] == -1){
                parent[v] = u;
                parent_edge[v] = id;
                depth[v] = low[v] = depth[u] + 1;

                // entramos 'recursivamente' a sus hijo
                pendiente.pb(v);
            }
            // back endge
            // u -> v 
            // u debeira estar arriba (menor profunidad) que v (mayor profundiad)
            else if(depth[v] < depth[u]){
                low[u] = min(low[u], depth[v]);
            }
        }
        

        // ESTAMOS EN POSTORDEN
        // low[u] ya deberia tener valor correcto porque ya temrinaron sus hijos
        // 
        else{
            // EJEMPLO: u esta en ciclo
            // ... -> x -> y -> ... -> p -> u -> ... -> w
            //       \_______<_______<_______<________/    // back edge
            // low[w] = low[u] = ... = low[p] = ... = low[y] = low[x] = depth[x]
            // depth[ z ] <= depth[p] = low[u]
            
            // EJEMPLO: u NO esta en ciclo 
            //        /---<------<----\
            // ... -> x -> ... -> w -> y -> ... -> p -> u -> ... -> z -> ...  -> w
            //                                                      \___________/    // back edge
            // low[w] = low[u] = ... = low[p] =  depth[z]
            // low[y] = low[w] = ... = low[x] =  depth[x]
            // depth[ z ] > depth[p] = low[u]

            // mas ejemplos en papel

            // la idea es que vamos fucionado con el padre si la arista (p,u) es un ciclo
            // tambien podriamos fucionar el nodo que le corresponde low[u] = depth[x]


            // la edge (p,u) es parte de un ciclo si sii low[u] > depth[p]
            
            // y fusionamos todo el camino de regreso
            // en particular  u y su padre
            pendiente.pop_back();
            int p = parent[u];
            if(p != -1){
                low[p] = min(low[p], low[u]);
                if(low[u] <= depth[p]) unidos_para_compactar.join(p, u, false);
            }
        }
    }

    // --- --- COMPACTACION --- --- 
    // construimos el arbol usanod lo obtenido en dsu
    // el representante puede ser cualquiera

    hackenbush_result res;

    // PARA CADA NODO ALCANZADO LO "PONEMOS" EN EL NODO COMPACTADO // normalizado -> compactado
    
    
    // basicamente >> reindexamos los representantes <<
    // vamos guardando a que 'nodo compacto' pertenece cada represenante
    // {valores cualesquiera entre de [0,n) }.  ->  [0, cntRepresentantes]
    // -1 si no podias llegar a piso
    vi id(n, -1);
    // el siguiente id sera este contador
    res.cntRepresentantes = 0;
    for(int u = 0; u < n; u++){
        // si es alcanzable desde el suelo
        if(depth[u] != -1){
            // tomar su representante
            int r = unidos_para_compactar.root(u);
            // si todavia no tiene id le ponemos uno
            if(id[r] == -1) id[r] = res.cntRepresentantes++;
        }
    }
    // >> a cada nodo le asignamos su compactado <<
    // compactados[u] = a que nodo compacto pertenece el nodo original u
    res.compactados.assign(n, -1);
    for(int u = 0; u < n; u++){
        int v = normalizado[u];
        if(depth[v] != -1) res.compactados[u] = id[unidos_para_compactar.root(v)];
    }
    res.root = res.compactados[0];

    // ya estamos trabajando con el arbol compactado
    // reservamos par
    res.tree.resize(res.cntRepresentantes);
    res.paridad.assign(res.cntRepresentantes, 0);

    // --- --- PARIDAD LAZOS --- ---
    // RECORDAR QUE: despues de todas las uniones cada arista interna se convierte en un lazo
    
    // contamos cuantos lazos tiene cada nodo
    for(const edge &e : edges){
        if(depth[e.from] == -1) continue;
        int a = id[unidos_para_compactar.root(e.from)];
        int b = id[unidos_para_compactar.root(e.to)];
        if(a == b){
            res.paridad[a] ^= 1;
        } else {
            res.tree[a].pb(b);
            res.tree[b].pb(a);
        }
    }

    // Cada lazo equivale a una hoja
    // 1 XOR 1 = 0
    // Materializamos exactamente una hoja si la paridad es impar
    // si es par se eliminan toods los lazos
    for(int u = 0; u < res.cntRepresentantes; u++){
        if(res.paridad[u]){
            // un nuevo nodo
            int leaf = sz(res.tree);
            // lo agregamos a este porque tiene lazo paridad 1
            res.tree.pb(vi{u});
            res.tree[u].pb(leaf);
        }
    }
    // --- --- NIM --- ---
    // obtener un orden padre-antes-que-hijo y procesarlo al reves.
    // g(u) = XOR sobre hijos v de (g(v)+1). El +1 es suma ORDINARIA,
    // mientras que la combinacion de ramas es XOR. Como las hojas de lazos
    // ya existen, NO volver a incluir paridad[u] en esta recurrencia.
    // La raiz no tiene arista de soporte: NO sumar 1 al resultado global.
    
    
    // hacemos una dfs // guardando el padre antes que el hijo
    vi order = {res.root}; // el orden // como la pila anterior pero sin pop
    vi par(sz(res.tree), -1); // padre del nodo compacto u
    // raiz su propio padre
    par[res.root] = res.root;
    // DFS iterativa guardando primero padre
    for(int i = 0; i < sz(order); i++){
        // el nodo sigueinte en la DFS
        int u = order[i];
        // para los hijos del nodo actual
        for(int v : res.tree[u]){
            if(v == par[u]) continue;
            // actualizamos su padre y agregamos
            par[v] = u;
            order.pb(v);
        }
    }
    // guardamos el valor de la pila de nim equivalente desde el nodo actual 
    // sin contar la arista hacia su padre
    res.nim.assign(sz(res.tree), 0);
    for(int i = sz(order) - 1; i > 0; i--){
        int u = order[i];
        // actualizamos el valor del padre
        int padre = par[u];
        int valorSubarbol = res.nim[u];
        int valorRama = valorSubarbol + 1;

        res.nim[padre] ^= valorRama;
    }
    res.value = res.nim[res.root];
    return res;
}


int main(){
    ios_base::sync_with_stdio(0); 
    cout.tie(0);
    cin.tie(0);

    // suelo - 1 - 2 - 3 - 4 
    // ganar
    vector<edge> edges1 = {{0,1}, {1,2}, {2,3}, {3,4}};
    auto result1 = green_hackenbush(4+1, edges1);
    cout << result1.value << '\n';

    // suelo - 1  -  2
    //          \  /
    //           3
    // ganar
    vector<edge> edges2 = {{0,1}, {1,2}, {2,3}, {3,1}};
    auto result2 = green_hackenbush(3+1, edges2);
    cout << result2.value << '\n';

    // suelo - 1  
    // suelo - 2  
    // perder       
    vector<edge> edges3 = {{0,1}, {0,2}};
    auto result3 = green_hackenbush(2+1, edges3);
    cout << result3.value << '\n';

    // suelo = 1  
    // suelo - 2         
    // suelo - 3 
    // suelo - 4 
    // ganar
    vector<edge> edges4 = {{0,1}, {0,1}, {0,2}, {0,3}, {0,4}};
    auto result4 = green_hackenbush(4+1, edges4);
    cout << result4.value << '\n';

    // suelo - 1  
    // suelo - 2         
    // suelo - 3 
    // suelo - 4 
    // perder
    vector<edge> edges5 = {{0,1}, {0,2}, {0,3}, {0,4}};
    auto result5 = green_hackenbush(4+1, edges5);
    cout << result5.value << '\n';

    // suelo - 1
    // suelo - 2
    // suelo - 3
    // ganar
    vector<edge> edges7 = { {0,1},{0,2},{0,3}};
    auto result7 = green_hackenbush(3+1, edges7);
    cout << result7.value << '\n';

    // suelo - 1
    // suelo - 2 - 3
    // gana: 1 XOR 2 = 3.
    vector<edge> edges8 = { {0,1}, {0,2}, {2,3}};
    auto result8 = green_hackenbush(3+1, edges8);
    cout << result8.value << '\n';

    // suelo - 1 - 2
    // suelo - 3 - 4
    // pierde: 2 XOR 2 = 0
    vector<edge> edges9 = { {0,1}, {1,2},   {0,3}, {3,4}};
    auto result9 = green_hackenbush(4+1, edges9);
    cout << result9.value << '\n';

    // suelo - 1
    // suelo - 2 - 3
    // suelo - 4 - 5 - 6
    // pierde:  1 XOR 2 XOR 3 = 0.
    vector<edge> edges10 = {
        {0,1},
        {0,2}, {2,3},
        {0,4}, {4,5}, {5,6}
    };
    auto result10 = green_hackenbush(6+1, edges10);
    cout << result10.value << '\n';

    // suelo - 1 - 2 - 3 - 4
    // suelo - 5
    // suelo - 6 - 7 - 8 - 9 - 10
    // pierde: 4 xor 1 xor 5
    vector<edge> edges11 = {
        {0,1}, {1,2}, {2,3}, {3,4},
        {0,5},
        {0,6}, {6,7}, {7,8}, {8,9}, {9,10}
    };
    auto result11 = green_hackenbush(10+1, edges11);
    cout << result11.value << '\n';

    // 0 -(*3)- 1
    // gana: tres cortes aristas impar
    vector<edge> edges16 = { {0,1}, {0,1}, {0,1} };
    auto result16 = green_hackenbush(1+1, edges16);
    cout << result16.value << '\n';

    //          2 ----- 3
    //          |       |
    // suelo -- 1 ----- 4
    // gana: corta el puente 0-1 y todo desconectado
    vector<edge> edges15 = { {0,1},{1,2}, {2,3}, {3,4}, {4,1}};
    auto result15 = green_hackenbush(4+1, edges15);
    cout << result15.value << '\n';

    //           2                 5
    //          / \               / \
    // suelo - 1---3     suelo - 4---6
    // pierde: son dos compactadoss iguales, el segundo copia
    vector<edge> edges17 = {
        {0,1}, {1,2}, {2,3}, {3,1},
        {0,4}, {4,5}, {5,6}, {6,4}
    };
    auto result17 = green_hackenbush(6+1, edges17);
    cout << result17.value << '\n';

    //          2---3                  6---7  11
    //          |   |                  |   | / 
    // suelo -- 1---4 -- 9    suelo -- 5---8 -- 10
    //                                      \
    //                                      12
    // pierde: son compactados equivalentes porque arboles en 4 y 8 equivalentes
    vector<edge> edges18 = {
        {0,1}, {1,2}, {2,3}, {3,4}, {4,1}, {4,9},
        {0,5}, {5,6}, {6,7}, {7,8}, {8,5}, {8,10}, {8,11}, {8,12}
    };
    auto result18 = green_hackenbush(12+1, edges18);
    cout << result18.value << "<-\n";

    //           2     11          5                 8
    //          / \    |          / \               / \
    // suelo - 1---3 --10     suelo - 4---6     suelo - 7---9
    // gana: si eliminas la primer compactados lo dejas en posicion perdedora
    vector<edge> edges19 = {
        {0,1}, {1,2}, {2,3}, {3,1}, {3,10}, {3,11},
        {0,4}, {4,5}, {5,6}, {6,4},
        {0,7}, {7,8}, {8,9}, {9,7}
    };
    auto result19 = green_hackenbush(11+1, edges19);
    cout << result19.value << '\n';


    //          2---3                  6---7  11
    //          |   |                  |   | / 
    // suelo -- 1---4 -- 9    suelo -- 5---8 -- 10    suelo(13) --- 14
    //                                      \
    //                                      12
    // gana: elimina suelo --14 y deja en poscion perdedora
    vector<edge> edges20 = {
        {0,1}, {1,2}, {2,3}, {3,4}, {4,1}, {4,9},
        {0,5}, {5,6}, {6,7}, {7,8}, {8,5}, {8,10}, {8,11}, {8,12},
        {13,14}
    };
    vi mas_suelo = {13};
    auto result20 = green_hackenbush(14+1, edges20, mas_suelo);
    cout << result20.value << "<-\n";

}