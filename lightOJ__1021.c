#include <stdio.h>
#include <string.h>

typedef long long ll;
typedef unsigned long long llu;

char vals[128];
int ks, K, B;
char inp[17];
llu dp[20][1<<16];
short vis[20][1<<16];
unsigned final;

llu rec(int mod, unsigned mask){
	llu res = 0;
	unsigned pwr = 1, i;
	
	if ( mask == final ) return ( mod == 0 );
	if ( ks == vis[mod][mask] ) return dp[mod][mask];
	
	vis[mod][mask] = ks;
	for ( i = 0 ; inp[i] ; i++, pwr <<= 1 ){
		if ( mask & pwr ) continue;
		res += rec( (mod * B + vals[inp[i]]) % K, mask | pwr );
	}
	
	return dp[mod][mask] = res;
}

void init(){
	int i;
	for ( i = '0' ; i <= '9' ; i++ ) vals[i] = i - '0';
	for ( i = 'A' ; i <= 'F' ; i++ ) vals[i] = i - 'A' + 10;
}

int main(){
	int test;
	
	init();
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d%s", &B, &K, inp);
			final = ~(~0<<strlen(inp));
			printf("Case %d: %llu\n", ks, rec(0, 0));
		}
	}
	
	return 0;
}

