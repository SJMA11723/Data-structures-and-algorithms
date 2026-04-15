#include "../../template.h"

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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
