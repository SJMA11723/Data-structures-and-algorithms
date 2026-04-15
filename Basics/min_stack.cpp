#include "../template.h"

template<typename T>
struct min_stack{
    stack<pair<T, T>> st;

    min_stack(){}

    min_stack(const T &MAXVAL){init(MAXVAL);}

    void init(const T &MAXVAL){st.push(make_pair(MAXVAL, MAXVAL));}

    void push(const T &v){st.push(make_pair(v, min(v, st.top().se)));}

    T top(){return st.top().first;}

    void pop(){if(sz(st) > 1)st.pop();}

    T minV(){return st.top().se;}

    int size(){return sz(st) - 1;}

    bool empty(){return size() == 0;}
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    min_stack<int> st(INT_MAX);
}
