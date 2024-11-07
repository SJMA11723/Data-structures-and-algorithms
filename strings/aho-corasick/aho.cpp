/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

struct aho_corasick{
    const static int K = 26;
    const char index = 'a';

    struct vertex{
        int next[K];
        bool terminal = false;
        int p = -1;
        char p_edge;
        int link = -1;
        int terminal_link = -1;
        int go[K];
        vertex(int p = -1, char c = '$') : p(p), p_edge(c){
            fill(next, next + K, -1);
            fill(go, go + K, -1);
        }
    };

    vector<vertex> aho;

    aho_corasick(){
        aho.resize(1);
    }

    void add_string(const string &s){
        int u = 0;
        for(char c : s){
            int e = c - index;
            if(aho[u].next[e] == -1){
                aho[u].next[e] = aho.size();
                aho.emplace_back(u, c);
            }
            u = aho[u].next[e];
        }
        aho[u].terminal = true;
    }

    int get_link(int u){
        if(aho[u].link == -1){
            if(!u || !aho[u].p) aho[u].link = 0;
            else aho[u].link = go(get_link(aho[u].p), aho[u].p_edge);
        }
        return aho[u].link;
    }

    int go(int u, char c){
        int e = c - index;
        if(aho[u].go[e] == -1){
            if(aho[u].next[e] != -1) aho[u].go[e] = aho[u].next[e];
            else aho[u].go[e] = !u ? 0 : go(get_link(u), c);
        }
        return aho[u].go[e];
    }

    int get_terminal_link(int u){
        if(aho[u].terminal_link == -1){
            if(!u || !aho[u].p) aho[u].terminal_link = 0;
            else aho[u].terminal_link = get_terminal_link(get_link(u));
        }
        return aho[u].terminal_link;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

}
