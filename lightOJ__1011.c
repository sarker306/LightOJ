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

int priority[16][16], n;
int ks, vis[16][1<<16], dp[16][1<<16];

int rec(int pos, unsigned mask){
	int res = INT_MIN, temp, i;
	
	if ( pos == n ) return 0;
	if ( vis[pos][mask] == ks ) return dp[pos][mask];
	vis[pos][mask] = ks;
	
	for ( i = 0 ; i < n ; i++ ){
		if ( mask & ( 1 << i ) ) continue;
		temp = rec(pos + 1, mask | (1<<i)) + priority[pos][i];
		if ( res < temp ) res = temp;
	}
	
	return dp[pos][mask] = res;
}

int main(){
	int test, i, j;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			for ( i = 0 ; i < n ; i++ )
				for ( j = 0 ; j < n ; j++ )
					scanf("%d", &priority[i][j]);

			printf("Case %d: %d\n", ks, rec(0, 0));
		}
	}
	
	return 0;
}

