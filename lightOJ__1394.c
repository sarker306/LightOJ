#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef unsigned long long llu;
typedef long long ll;

long maxOne, K;
llu dp[2][3][7][32][32][32], dpNum[2][3][7][32][32][32];
short vis[2][3][7][32][32][32], visNum[2][3][7][32][32][32], turn;
char ideal[32], limit[32];

void toBinary(char *arr, long num){
	int i, j;
	long pwr = 1<<30;
	
	for ( i = 30, j = 0 ; i >= 0 ; i--, j++, pwr >>= 1 ) arr[j] = (num & pwr) ? '1' : '0';
	arr[j] = 0;
}

long recNum(int less, int mod3, int mod7, int pos, int idealDiff, int ones){
	long res = 0;
	int nless, i, nDiff, nOnes;

	if ( pos == 31 ){
		if ( ones <= maxOne && idealDiff <= K && mod3 == 0 && mod7 ) return 1;
		return 0;
	}
	/*if ( ones > maxOne || idealDiff > K ) return 0;*/
	if ( visNum[less][mod3][mod7][pos][idealDiff][ones] == turn )
		return dpNum[less][mod3][mod7][pos][idealDiff][ones];

	visNum[less][mod3][mod7][pos][idealDiff][ones] = turn;

	for ( i = 0 ; i < 2 ; i++ ){
		nless = less;
		if ( less == 0 && (i + '0') > limit[pos] ) continue;
		if ( less == 0 && (i + '0') < limit[pos] ) nless = 1;

		nDiff = idealDiff;
		if ( (i + '0') != ideal[pos] ) nDiff++;
		if ( nDiff > K ) continue;

		nOnes = ones;
		if ( i == 1 ) nOnes++;
		if ( nOnes > maxOne ) continue;

		res += recNum(nless, ((mod3<<1) + i)%3, ((mod7<<1) + i)%7, pos + 1, nDiff, nOnes);
	}

	return dpNum[less][mod3][mod7][pos][idealDiff][ones] = res;
}

llu rec(int less, int mod3, int mod7, int pos, int idealDiff, int ones){
	llu res = 0;
	int nless, i, nDiff, nOnes;
	
	if ( pos == 31 ) return 0;
	
	if ( vis[less][mod3][mod7][pos][idealDiff][ones] == turn )
		return dp[less][mod3][mod7][pos][idealDiff][ones];

	vis[less][mod3][mod7][pos][idealDiff][ones] = turn;
	
	for ( i = 0 ; i < 2 ; i++ ){
		nless = less;
		if ( less == 0 && (i + '0') > limit[pos] ) continue;
		if ( less == 0 && (i + '0') < limit[pos] ) nless = 1;
		
		nDiff = idealDiff;
		if ( (i + '0') != ideal[pos] ) nDiff++;
		if ( nDiff > K ) continue;
		
		nOnes = ones;
		if ( i == 1 ) nOnes++;
		if ( nOnes > maxOne ) continue;
		
		if ( i ) res += (1LLU<<(30-pos)) * recNum(nless, ((mod3<<1) + i)%3, ((mod7<<1) + i)%7, pos + 1, nDiff, nOnes);
		res += rec(nless, ((mod3<<1) + i)%3, ((mod7<<1) + i)%7, pos + 1, nDiff, nOnes);
	}
	
	return dp[less][mod3][mod7][pos][idealDiff][ones] = res;
}

llu rawCheck(long start, long end, int maxOne, int K){
	long i;
	int j, cntDiff, cntOne;
	llu sum = 0;
	char tmp[32];
	
	for ( i = start ; i <= end ; i++ ){
		if ( i % 3 ) continue;
		if ( i % 7 == 0 ) continue;
		toBinary(tmp, i);
		cntDiff = cntOne = 0;
		for ( j = 0 ; tmp[j] ; j++ ){
			if ( tmp[j] == '1' ) cntOne++;
			if ( tmp[j] != ideal[j] ) cntDiff++;
			if ( cntOne > maxOne ) break;
			if ( cntDiff > K ) break;
		}
		
		if ( tmp[j] == 0 ) sum += i;
	}
	
	return sum;
}

int main(){
	int test, ks;
	long start, end, idln;
	llu res = 0;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%ld%ld%ld%ld%ld", &start, &end, &maxOne, &idln, &K);
			
			turn++;
			toBinary(limit, end);
			toBinary(ideal, idln);
			res = rec(0, 0, 0, 0, 0, 0);
			
			turn++;
			if ( start ){
				toBinary(limit, start-1);
				res -= rec(0, 0, 0, 0, 0, 0);
			}
			
			printf("Case %d: %llu\n", ks, res);
			#ifndef ONLINE_JUDGE
			printf("%llu\n", rawCheck(start, end, maxOne, K));
			#endif
		}
	}
			
	return 0;
}

