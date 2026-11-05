#include "../../template.h"

#define LOGN 18 // hide
struct virtual_tree{
    vvi T, VT, P;
    vi in, out;
    int timer;
    virtual_tree(vvi &_T, int r = 1) : T(_T){
        in.resize(sz(T)); out.resize(sz(T)); VT.resize(sz(T));
        P.resize(LOGN, vi(sz(T))); timer = 0; precalc(r);
    }

    void precalc(int u, int p = 0);
    int LCA(int a, int b);
    bool is_ancestor(int u, int v){
        return in[u] <= in[v] && out[v] <= out[u];
    }

    // given specific nodes, construct a compressed directed tree with these vertices(if needed some other nodes included)
    // returns the nodes of the tree
    // nodes.front() is the root
    // VT[] is the specific tree
    vi build_tree(vi S){
        // sort by entry time
        sort(all(S),[&](int x, int y){ return in[x]<in[y]; });
        // finding all the ancestors, there are few of them
        int s = sz(S);
        rep(i, 0, s - 1) S.pb(LCA(S[i], S[i + 1]));
        // removing duplicated nodes
        sort(all(S)); S.erase(unique(all(S)), S.end());
        // again sort by entry time
        sort(all(S),[&](int x, int y){ return in[x]<in[y]; });

        for(int u : S) VT[u].clear();
        stack<int> st; st.push(S[0]);
        rep(i, 1, sz(S)){
            while(!is_ancestor(st.top(), S[i])) st.pop();
            VT[st.top()].pb(S[i]); st.push(S[i]);
        } return S;
    }
};