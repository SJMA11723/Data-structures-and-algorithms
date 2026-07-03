/**
* Author: Jorge Raul Tzab Lopez
* Github: https://github.com/SJMA11723
* LinkedIn: https://www.linkedin.com/in/jorgetzab/
*/

#include <bits/stdc++.h>

using namespace std;

void check(int arr[], int n){
    /**
        Aqui revisas las condiciones que quieras de la permutacion actual
    */
    for(int i = 0; i < n; ++i)
        cout << arr[i] << ' ';
    cout << '\n';
}

void generaPermutacionesDeM(int arr[], int n, int m){
    if(n < m) return;

    do{
        check(arr, m);
    } while(next_permutation(arr, arr + n));
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n = 4;
    int arr[n] = {1, 2, 3, 4};
    generaPermutacionesDeM(arr, n, 3);
}
