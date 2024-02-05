/*
Bits Mask
*/
#include <bits/stdc++.h>
using namespace std;


#define isOn(S, j) (S & (1ll << (j)))
#define setBit(S, j) (S |= (1ll << (j)))
#define clearBit(S, j) (S &= ~(1ll << (j)))
#define toggleBit(S, j) (S ^= (1ll << (j)))

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


int main(void){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	// iterar en orden natural 
	int n = 20;
	for (int i = 0; i < (1<<n); i++){
		// code here
	}


	return 0;
}