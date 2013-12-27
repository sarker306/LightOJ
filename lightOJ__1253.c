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

int arr[101];

int main(){
	int test, ks, k, i, res;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks =1 ; ks <= test ; ks++ ){
			scanf("%d", &k);
			res = 0;
			for ( i = 0 ; i < k ; i++ ){
				scanf("%d", &arr[i]);
				res ^= arr[i];
			}
			
			for ( i = 0 ; i < k ; i++ ){
				if ( arr[i] != 1 ) break;
			}
			
			if ( i == k ) res = !(k % 2);

			printf("Case %d: %s\n", ks, res ? "Alice" : "Bob");
		}
	}
			
	return 0;
}

