#include <bits/stdc++.h>
void criba(int n, vector<int> &primos){
    primos.clear();
    if(n < 2) return;
    vector<bool> no_primo(n + 1);
    no_primo[0] = no_primo[1] = true;
    for(long long i = 3; i * i <= n; i += 2){
        if(no_primo[i]) continue;
        for(long long j = i * i; j <= n; j += 2 * i)
            no_primo[j] = true;
    }
    primos.push_back(2);
    for(int i = 3; i <= n; i += 2){
        if(!no_primo[i])
            primos.push_back(i);
    }
}/// Tiempo: O(nloglogn), Memoria: O(n)
void criba_sobre_rango(long long a, long long b, vector<long long> &primos){
    a = max(a, 0ll);
    b = max(b, 0ll);
    long long tam = b - a + 1;
    vector<int> primos_raiz;
    criba(sqrt(b) + 1, primos_raiz);
    vector<char> no_primo(tam);
    primos.clear();
    for(long long p : primos_raiz){
        long long ini = p * max(p, (a + p - 1) / p);
        for(long long m = ini; m <= b; m += p){
            no_primo[m - a] = true;
        }
    }
    for(long long i = 0; i < tam; ++i){
        if(no_primo[i] || i + a < 2) continue;
        primos.push_back(i + a);
    }
}/// Tiempo: O(sqrt(b)loglogsqrt(b) + (b - a)loglog(b - a)), Memoria: O(b - a)
