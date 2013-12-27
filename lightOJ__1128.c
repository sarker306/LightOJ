#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

#define SIZE 100002

typedef unsigned long long llu;
typedef long long ll;

long parent[SIZE], val[SIZE], n, ver, ind;
long P[SIZE][22];

void preprocess(){
	long i;
	short j;
	
	memset(P, -1, sizeof(P));
              
	for ( i = 0 ; i < n ; i++ ) P[i][0] = parent[i];
	
	for ( j = 1 ; ( 1 << j ) < n ; j++ )
		for ( i = 0 ; i < n ; i++ ){
			if ( P[i][j-1] != -1 ) P[i][j] = P[P[i][j-1]][j-1];
			/*printf("%d %d -> %d\n", i, j, P[i][j]);*/
		}
}

long process(){
	short log;
	long v = ver;
	
	while ( 1 ){
		for ( log = 0 ; P[v][log] != -1 ; log++ ){
			/*printf("%d %d -> %d, %d\n", v, log, P[v][log], val[P[v][log]]);*/
			if ( val[P[v][log]] < ind ) break;
		}

		log--;
		if ( log < 0 ) break;
		v = P[v][log];
	}
	
	return v;
}

int main(){
	int test, ks;
	long i, q;
	
	val[0] = 1;
	parent[0] = -1;
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%ld%ld", &n, &q);
			for ( i = 1 ; i < n ; i++ ) scanf("%ld%ld", &parent[i], &val[i]);
			
			preprocess();
			
			printf("Case %d:\n", ks);
			while (q--){
				scanf("%ld%ld", &ver, &ind);
				printf("%ld\n", process());
			}
		}
	}
	
	return 0;
}

