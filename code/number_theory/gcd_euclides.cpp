#include "../template.h"

int gcd(int a, int b){
    return !b ? a : gcd(b, a % b);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b);
}
