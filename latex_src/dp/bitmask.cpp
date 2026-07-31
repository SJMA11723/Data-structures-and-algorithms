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
void GospersHack(int n, int k) {
    int mask = (1 << k) - 1;
    int limit = (1 << n);
    while(mask < limit){
        int c = mask & - mask;
        int r = mask + c;
        mask = (((r ^ mask) >> 2) / c) | r;
    }
}
void submasks(int mask){
	for( int x = mask; x;){
    	--x &= mask;
	}
}
