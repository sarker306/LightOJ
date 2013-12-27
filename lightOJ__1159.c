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

char one[51], two[51], three[51];
int len[51][51][51], vis[51][51][51], ks;

int maxi(int a, int b, int c){
	int res = a;
	if ( res < b ) res = b;
	if ( res < c ) res = c;
	return res;
}

int rec(int x, int y, int z){
	int res;
	
	if ( one[x] == 0 || two[y] == 0 || three[z] == 0 ) return 0;
	if ( vis[x][y][z] == ks ) return len[x][y][z];
	vis[x][y][z] = ks;
	
	if ( one[x] == two[y] && two[y] == three[z] ) res = 1 + rec(x + 1, y + 1, z + 1);
	else res = maxi(rec(x, y, z+1), rec(x, y+1, z), rec(x+1, y, z));
	return len[x][y][z] = res;
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%s%s%s", one, two, three);
			printf("Case %d: %d\n", ks, rec(0, 0, 0));
		}
	}
	
	return 0;
}

