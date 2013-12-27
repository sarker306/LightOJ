#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)
#define SZ 5000001
typedef unsigned long long llu;
typedef long long ll;

char isNotPrime[SZ];
llu phi[SZ];

void init(){
	ll i, j;
	
	for ( i = 1 ; i < SZ ; i++ ) phi[i] = i;
	for ( i = 4 ; i < SZ ; i += 2 ) isNotPrime[i] = 1;
	
	for ( i = 3 ; i * i < SZ ; i += 2 )
		if ( isNotPrime[i] == 0 ){
			for ( j = i * i ; j < SZ ; j += i ) isNotPrime[j] = 1;
		}

	for ( i = 2 ; i < SZ ; i++ ){
		if ( isNotPrime[i] == 0 ){
			for ( j = i ; j < SZ ; j += i ) phi[j] -= phi[j]/i;
		}
	}
	
	for ( i = 1 ; i < SZ ; i++ ) phi[i] = phi[i-1] + phi[i] * phi[i];
}

int main(){
	int test, a, b, ks;
	
	init();
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &a, &b);
			printf("Case %d: %llu\n", ks, phi[b] - phi[a-1]);
		}
	}
	
	return 0;
}

