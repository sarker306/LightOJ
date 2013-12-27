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

int fCloth[101][101];
int minCost[101][101];
int party[101], N;

int main(){
	int test, ks;
	int i, j, k, len, temp;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &N);
			
			for ( i = 0 ; i < N ; i++ ) scanf("%d", &party[i]);

			for ( i = 0 ; i < N ; i++ ) minCost[i][i] = 1, fCloth[i][i] = party[i];
			for ( len = 2 ; len <= N ; len++ ){
				for ( i = 0 ; i + len - 1 < N ; i++ ){
					j = i + len - 1;
					minCost[i][j] = N<<1;
					for ( k = i ; k < j ; k++ ){
						temp = minCost[i][k] + minCost[k+1][j];
						if ( fCloth[i][k] == fCloth[k+1][j] ) temp--;
						if ( temp < minCost[i][j] ){
							minCost[i][j] = temp;
							fCloth[i][j] = fCloth[k+1][j];
						}
					}
				}
			}
			
			printf("Case %d: %d\n", ks, minCost[0][N-1]);
		}
	}
	
	return 0;
}

