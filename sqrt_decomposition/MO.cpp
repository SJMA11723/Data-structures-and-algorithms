#include <bits/stdc++.h>

using namespace std;

const int block_size = 300;

struct query {
    int l, r;
    int block, i;
    bool operator<(const query &b) const {
        if(block == b.block) return r < b.r;
        return block < b.block;
    }
};

void add(int idx){
    /// TO-DO
}

void remove(int idx){
    /// TO-DO
}

int get_answer(){
    return 0; /// TO-DO
}

vector<int> solve(vector<query> &queries) {
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());

    int cur_l = 0;
    int cur_r = -1;

    for(query q : queries){
        while(cur_l > q.l) add(--cur_l);
        while(cur_r < q.r) add(++cur_r);
        while(cur_l < q.l) remove(cur_l++);
        while(cur_r > q.r) remove(cur_r--);
        answers[q.i] = get_answer();
    }
    return answers;
}

int arr[50000];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q; cin >> n >> q;
    for(int i = 0; i < n; ++i) cin >> arr[i];
    vector<query> queries;
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r;
        queries.push_back(query{l, r, l / block_size, i});
    }

    vector<int> ans = solve(queries);
    for(int x : ans)
        cout << x << '\n';
}
