struct _node{
    ll x, p;
    int freq, cnt, rev;
    _node *l, *r;
    _node() : l(nullptr), r(nullptr){}
    _node(ll _x): x(_x), p(seed()), freq(1), cnt(1), rev(0),
        l(nullptr), r(nullptr){}
    void recalc(){
        cnt = freq;
        cnt += ((l) ? l->cnt : 0) + ((r) ? r->cnt : 0);
    }
};
using node = _node*;
_node pool[MAXN + 2];
int nxt_node = 1;
node alloc(ll _x){
    pool[nxt_node] = _node(_x);
    return &pool[nxt_node++];
}
struct treap{
    node root;
    treap(): root(nullptr){}
    node merge(node l, node r){
        if(!l || !r) return l ? l : r;
        if(l->p < r->p){
            r->l = merge(l, r->l);
            r->recalc();
            return r;
        } else {
            l->r = merge(l->r, r);
            l->recalc();
            return l;
        }
    }
    pair<node, node> split_v(node u, ll d){
        if(!u) return {u, u};
        if(u->x < d){
            auto p = split_v(u->r, d);
            u->r = p.fi;
            u->recalc();
            return {u, p.se};
        } else {
            auto p = split_v(u->l, d);
            u->l = p.se;
            u->recalc();
            return {p.fi, u};
        }
    }
    void insert_v(ll x){
        node l, m, r;
        tie(l, r) = split_v(root, x);
        tie(m, r) = split_v(r, x + 1);
        if(m){
            m->freq++;
            m->cnt++;
        } else m = alloc(x);
        root = merge(merge(l, m), r);
    }
    void erase_v(ll x){
        node l, m, r;
        tie(l, r) = split_v(root, x);
        tie(m, r) = split_v(r, x + 1);
        if(!m || m->freq == 1) m = nullptr;
        else {
            m->freq--;
            m->cnt--;
        }
        root = merge(merge(l, m), r);
    }
};
struct implicit_treap{
    node root;
    implicit_treap(): root(nullptr){}
    void apply_lz(node u){ u->rev = 0; swap(u->l, u->r); }
    void push(node u){
        if(u && u->rev){
            apply_lz(u);
            if(u->l) u->l->rev ^= 1;
            if(u->r) u->r->rev ^= 1;
        }
    }
    node merge(node l, node r){
        push(l);
        push(r);
        if(!l || !r) return l ? l : r;
        if(l->p < r->p){
            r->l = merge(l, r->l);
            r->recalc();
            return r;
        } else {
            l->r = merge(l->r, r);
            l->recalc();
            return l;
        }
    }
    pair<node, node> split_p(node u, int pos){
        if(!u) return {u, u};
        push(u);
        int cur_pos = (u->l) ? (u->l->cnt) : 0;
        if(cur_pos < pos){
            auto p = split_p(u->r, pos - cur_pos - 1);
            u->r = p.fi;
            u->recalc();
            return {u, p.se};
        } else {
            auto p = split_p(u->l, pos);
            u->l = p.se;
            u->recalc();
            return {p.fi, u};
        }
    }
    void insert_p(int pos, ll x){
        node l, r;
        tie(l, r) = split_p(root, pos);
        root = merge(merge(l, alloc(x)), r);
    }
    void erase_p(int pos){
        node l, m, r;
        tie(l, r) = split_p(root, pos);
        tie(m, r) = split_p(r, 1);
        m = nullptr;
        root = merge(l, r);
    }
    void reverse(int l, int r){
        node prv, inter, nxt;
        tie(prv, inter) = split_p(root, l);
        tie(inter, nxt) = split_p(inter, r - l + 1);
        inter->rev ^= 1;
        root = merge(merge(prv, inter), nxt);
    }
    void _print(node u){
        if(!u) return;
        push(u);
        _print(u->l);
        cout << u->x << ' ';
        _print(u->r);
    }
    void print(){ _print(root); }
};
