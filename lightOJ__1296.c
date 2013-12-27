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

typedef unsigned long long llu;
typedef long long ll;

int pwr[33];

int findCleverGrundy(int x){
	int i;

	for ( i = 1 ; i < 33 ; i++ ){
		if ( ( x & pwr[i] ) == pwr[i-1] ) return x>>i;
	}
}

int main(){
	int test, ks, n, i, x, res;

	pwr[0] = 0, pwr[1] = 1;
	for ( i = 2 ; i < 33 ; i++ ) pwr[i] = 1 + (pwr[i-1]<<1);

	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			res = 0;
			for ( i = 0 ; i < n ; i++ ){
				scanf("%d", &x);
				res ^= findCleverGrundy(x);
			}
			
			printf("Case %d: %s\n", ks, res ? "Alice" : "Bob");
		}
	}
	
	return 0;
}

