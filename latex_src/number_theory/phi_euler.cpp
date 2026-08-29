vi calc_phi(int n){
    vi phi(n + 1);
    for(int i = 0; i <= n; ++i) phi[i] = i & 1 ? i : i / 2;
    for(int i = 3; i <= n; i += 2) if(phi[i] == i)
    for(int j = i; j <= n; j += i) phi[j] -= phi[j] / i;
    return phi;
}
