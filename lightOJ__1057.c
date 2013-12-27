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

int ks, INF = 20000;
int vis[16][1<<16], dp[16][1<<16];
int pts[17][2], n;
char grid[21][21];

int queenDist(int a, int b){
	int delx = pts[a][0] - pts[b][0], dely = pts[a][1] - pts[b][1];
	if ( delx < 0 ) delx = -delx;
	if ( dely < 0 ) dely = -dely;
	return delx > dely ? delx : dely;
}

int rec(int pos, unsigned mask){
	int res = INF, temp, i;

	if ( vis[pos][mask] == ks ) return dp[pos][mask];
	vis[pos][mask] = ks;

	for ( i = 0 ; i < n ; i++ ){
		if ( mask & (1<<i) ) continue;
		if ( i == pos ) continue;
		temp = rec(i, mask | (1<<i)) + queenDist(pos, i);
		if ( res > temp ) res = temp;
	}

	if ( res == INF && pos == 0 && mask == ~(~0u<<n)) res = 0;
	return dp[pos][mask] = res;
}

int main(){
	int test, res, temp, i, row, col;

	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &row, &col);
			getchar();
			n = 0;
			for ( i = 0 ; i < row ; i++ ){
				gets(grid[i]);
				for ( col = 0 ; grid[i][col] ; col++ ){
					if ( grid[i][col] != '.' ){
						pts[n][0] = i, pts[n][1] = col;
						n++;
					}
				}
			}
			
			printf("Case %d: %d\n", ks, n == 1 ? 0 : rec(0,0));
		}
	}

	return 0;
}

