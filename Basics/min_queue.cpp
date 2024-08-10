/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct min_stack{
    stack<pair<T, T>> st;

    min_stack(){}

    min_stack(const T &MAXVAL){init(MAXVAL);}

    void init(const T &MAXVAL){st.push(make_pair(MAXVAL, MAXVAL));}

    void push(const T &v){st.push(make_pair(v, min(v, st.top().second)));}

    T top(){return st.top().first;}

    void pop(){if(st.size() > 1)st.pop();}

    T minV(){return st.top().second;}

    int size(){return st.size() - 1;}

    bool empty(){return size() == 0;}
};

template<typename T>
struct min_queue{
    min_queue(const T &MAXVAL){
        p_in.init(MAXVAL);
        p_out.init(MAXVAL);
    }

    void push(const T &v){p_in.push(v);}

    T front(){transfer(); return p_out.top();}

    void pop(){transfer(); p_out.pop();}

    int size(){return p_in.size() + p_out.size();}

    T minV() {return min(p_in.minV(), p_out.minV());}

    bool empty(){ return size() == 0;}
    void transfer(){
        if(p_out.size()) return;

        while(p_in.size()){
            p_out.push(p_in.top());
            p_in.pop();
        }
    }
    min_stack<T> p_in, p_out;
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
