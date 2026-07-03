/*
Bits Mask
*/
#include "../template.h"

#define is_on(S, j) (S & (1ll << (j)))
#define set_bit(S, j) (S |= (1ll << (j)))
#define clear_bit(S, j) (S &= ˜(1ll << (j)))
#define toggle_bit(S, j) (S ˆ= (1ll << (j)))
#define lsb(S) ((S) & -(S))
#define clear_lsb(S) (S &= (S - 1))
#define set_all(S, n) (S = (1ll << (n)) - 1ll)
#define clear_trailing_ones(S) (S &= (S + 1))
#define set_last_bit_off(S) (S |= (S + 1))
#define is_power_of_two(S) (!((S) & ((S) - 1)))
#define nearest_power_of_two(S) ((int)pow(2, (int)((log((double)(S)) / log(2)) + 0.5)) )
#define is_divisible_by_power_of_two(n, k) !((n) & ((1ll << (k)) - 1))
#define modulo(S, N) ((S) & ((N) - 1)) // S % N, N potencia de 2

/* one plus the index of the least significant 1-bit of x, or if x is zero, returns zero. */
//int __builtin_ffs (int x)

/* number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined */
//int __builtin_clz (unsigned int x)

/* number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined */
//int __builtin_ctz (unsigned int x)

/* number of 1-bits in x */
//int __builtin_popcount (unsigned int x)

/* the parity of x, i.e. the number of 1-bits in x modulo 2 */
//int __builtin_parity (unsigned int x)

/* hay versiones que acaban con "ll" que operan con long long */
//int __builtin_ffsll (long long)

/* Gospers’ Hack
	Sirve para generar todos las máscaras de n bits, 
	que tengan exactamente k bits a 1 (y que sean menores o iguales que $2^n$)
*/
void GospersHack(int n, int k) {
    int mask = (1 << k) - 1;
    int limit = (1 << n);
    while(mask < limit){
		// Calcula la siguiente mask mayor con la misma cantidad de bits
        int c = mask & - mask;
        int r = mask + c;
        mask = (((r ^ mask) >> 2) / c) | r;
    }
}

// Dada una mascara m, iterar sobre todos sus subconjuntos 
void submasks(int mask){
	for( int x = mask; x;){
    	--x &= mask;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	int n = 20;
	int k=10;
	GospersHack(n, k);
	return 0;
}