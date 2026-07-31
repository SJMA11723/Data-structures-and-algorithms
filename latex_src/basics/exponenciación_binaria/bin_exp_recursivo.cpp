#include <bits/stdc++.h>
int bin_exp(int a, int b){
    if(!b) return 1;
    int tmp = bin_exp(a, b / 2);
    if(b % 2) return tmp * tmp * a;
    return tmp * tmp;
}
