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
	int a, b, test, ks, grey, res;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			res = 0;
			scanf("%d", &grey);
			while ( grey-- ){
				scanf("%d%d", &a, &b);
				res ^= (b-a-1);
			}
			
			printf("Case %d: %s\n", ks, res ? "Alice" : "Bob");
		}
	}
	
	return 0;
}

