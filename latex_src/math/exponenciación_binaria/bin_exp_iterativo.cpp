#include <bits/stdc++.h>
int bin_exp(int a, int b){
    int ans = 1;
    while(b){
        if(b % 2) ans *= a;
        a *= a;
        b /= 2;
    }
    return ans;
}
