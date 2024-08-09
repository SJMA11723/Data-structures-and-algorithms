/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
*/

#include <bits/stdc++.h>

using namespace std;

template<class TPriority, class TKey> class UpdatableHeap{
public:
    UpdatableHeap(){
        TPriority a;
        TKey b;
        nodes.clear();
        nodes.push_back( make_pair(a, b) );
    }
    pair<TPriority, TKey> top() {
        return nodes[1];
    }
    void pop(){
        if(nodes.size() == 1) return;
        TKey k = nodes[1].second;
        swap_nodes(1, nodes.size() - 1);
        nodes.pop_back();
        position.erase(k);
        heapify(1);
    }
    void insert_or_update(const TPriority &p, const TKey &k){
        int pos;
        if(is_inserted(k)){
            pos = position[k];
            nodes[pos].first += p;
        } else {
            position[k] = pos = nodes.size();
            nodes.push_back( make_pair(p, k) );
        }
        heapify(pos);
    }
    bool is_inserted(const TKey &k) {
        return position.count(k);
    }
    int get_size() {
        return (int)nodes.size() - 1;
    }
    void erase(const TKey &k){
        if(!is_inserted(k)) return;
        int pos = position[k];
        swap_nodes(pos, nodes.size() - 1);
        nodes.pop_back();
        position.erase(k);
        heapify(pos);
    }
private:
    vector<pair<TPriority, TKey>> nodes;
    map<TKey, int> position;

    void heapify(int pos){
        if(pos >= nodes.size()) return;
        while(1 < pos && nodes[pos / 2] <= nodes[pos]){
            swap_nodes(pos / 2, pos);
            pos /= 2;
        }
        int l = pos * 2, r = pos * 2 + 1, maxi = pos;
        if(l < nodes.size() && nodes[l] > nodes[maxi]) maxi = l;
        if(r < nodes.size() && nodes[r] > nodes[maxi]) maxi = r;
        if(maxi != pos){
            swap_nodes(pos, maxi);
            heapify(maxi);
        }
    }
    void swap_nodes(int a, int b){
        position[ nodes[a].second ] = b;
        position[ nodes[b].second ] = a;
        swap(nodes[a], nodes[b]);
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

}
