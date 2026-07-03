/*
Li Chao Tree
*/

#include "../template.h"

struct Function {
	ll m;
	ll b;
	ll eval(ll x){
		if (m == LLONG_MIN) return LLONG_MIN;
		return m*x+b;
	}
	Function(){ m = LLONG_MIN;}
	Function(ll m_, ll b_): m(m_), b(b_){ }
};

struct LiChaoTree {
	vll values;
	ll maxV;
	Function *functions;
	LiChaoTree(vll &values_){
		values = values_;
		sort(all(values));
		functions = new Function[sz(values) * 4];
		maxV = sz(values);
	}
	//Range from l to r - 1
	ll get(ll x){
		return get(x, 1, 0, maxV);
	}
	ll get(ll x, int v, int l, int r){
		int m = l + (r - l) / 2;
		ll mv = values[m];
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
		int m = l + (r - l) / 2;
		ll mv = values[m];
		ll lv = values[l];
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
}
