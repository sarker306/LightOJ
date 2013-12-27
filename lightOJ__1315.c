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

int grundy[1000][1000];
char xdir[] = {+1,-1,-1,-2,-3,-2};
char ydir[] = {-2,-3,-2,-1,-1,+1};
int row = 1000;

int findGrundy(int x, int y){
	int avl[8], i, u, v;
	
	if ( grundy[x][y] != -1 ) return grundy[x][y];
	for ( i = 0 ; i < 8 ; i++ ) avl[i] = 0;
	for ( i = 0 ; i < 6 ; i++ ){
		u = x + xdir[i], v = y + ydir[i];
		if ( u >= 0 && u < row && v >= 0 && v < row ) avl[findGrundy(u, v)] = 1;
	}
	
	for ( i = 0 ; i < 8 ; i++ ) if ( avl[i] == 0 ) break;
	return grundy[x][y] = i;
}

int main(){
	int test, ks, n, res, x, y;
	
	memset(grundy, -1, sizeof(grundy));
	/*for ( x = 0 ; x < 100 ; x++ ){
		for ( y = 0 ; y < 100 ; y++ ) printf("%d ", findGrundy(x, y));
		puts("");
	}*/
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			res = 0;
			while ( n-- ){
				scanf("%d%d", &x, &y);
				res ^= findGrundy(x, y);
			}
			
			printf("Case %d: %s\n", ks, res ? "Alice" : "Bob");
		}
		
		break;
	}
	
	return 0;
}

