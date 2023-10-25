/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct min_stack{
    stack<pair<int, int>> st;

    min_stack(){st.push(make_pair(INT_MAX, INT_MAX));}

    void push(int v){st.push(make_pair(v, min(v, st.top().second)));}

    int top(){return st.top().first;}

    void pop(){if(st.size() > 1)st.pop();}

    int minV(){return st.top().second;}

    int size(){return st.size() -1;}

    bool empty(){return size() == 0;}
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
