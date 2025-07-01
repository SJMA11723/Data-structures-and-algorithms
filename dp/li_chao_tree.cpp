/*
Li Chao Tree
*/

/*				Librerias y Macros			*/
#include <bits/stdc++.h>
using namespace std;

/*				Declaraciones				*/

struct Function {
	long long m;
	long long b;
	long long eval(long long x){
		if (m == LLONG_MIN) return LLONG_MIN;
		return m*x+b;
	}
	Function(){ m = LLONG_MIN;}
	Function(long long m_, long long b_): m(m_), b(b_){ }
};

struct LiChaoTree {
	vector<long long> values;
	long long maxV;
	Function *functions;
	LiChaoTree(vector<long long> &values_){
		values = values_;
		sort(values.begin(), values.end());
		functions = new Function[values.size() * 4];
		maxV = values.size();
	}
	//Range from l to r - 1
	long long get(long long x){
		return get(x, 1, 0, maxV);
	}
	long long get(long long x, int v, int l, int r){
		int m = (l + r) / 2;
		long long mv = values[m];
		if (r - l == 1){
			return functions[v].eval(x);
		} else if (x < mv){
			return max(functions[v].eval(x), get(x, 2 * v, l, m));
		} else {
			return max(functions[v].eval(x), get(x, 2 * v + 1, m, r));
		}
	}

	void addFunction(Function f){
		addFunction(f, 1, 0, maxV);
	}

	void addFunction(Function f, int v, int l, int r){
		int m = (l + r) / 2;
		long long mv = values[m];
		long long lv = values[l];
		bool lef = f.eval(lv) > functions[v].eval(lv);
		bool mid = f.eval(mv) > functions[v].eval(mv);
		if (mid){//Si el actual pierde en el medio
			swap(functions[v], f);
		}
		if (r - l == 1){
			return;
		} else if (lef != mid){//El cruce esta en el lado izq.
			addFunction(f, 2 * v, l, m);
		} else {
			addFunction(f, 2 * v + 1, m, r);
		}
	}
	~LiChaoTree(){ delete[] functions; }
};

/*				Funcion main				*/
int main(void){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);




	return 0;
}
