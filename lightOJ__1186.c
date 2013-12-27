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

int main(){
	int test, ks, n, arr[305], x, res, i;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			res = 0;
			for ( i = 0 ; i < n ; i++ ) scanf("%d", &arr[i]);
			for ( i = 0 ; i < n ; i++ ){
				scanf("%d", &x);
				res ^= x - arr[i] - 1;
			}
			
			printf("Case %d: %s wins\n", ks, res ? "white" : "black");
		}
	}
	
	return 0;
}

