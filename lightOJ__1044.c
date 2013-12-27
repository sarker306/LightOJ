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
#define SIZE 1001

typedef unsigned long long llu;
typedef long long ll;

char isPalin[SIZE][SIZE];
int minCut[SIZE][SIZE];
char str[SIZE];

int main(){
	int test, ks, i, j, ln;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%s", str);
			
			for ( i = 0 ; str[i] ; i++ ) isPalin[i][i] = 1;
			
			for ( ln = 1 ; str[ln] ; ln++ ){
				for ( i = 0 ; str[i+ln] ; i++ ){
					j = i + ln;
					if ( str[i] != str[j] ) isPalin[i][j] = 0;
					else if ( ln == 1 ) isPalin[i][j] = (str[i] == str[j]);
					else isPalin[i][j] = isPalin[i+1][j-1];
				}
			}
			
			ln--;
			for ( i = ln ; i >= 0 ; i-- ){
				if ( isPalin[i][ln] ){
					minCut[i][ln] = 0;
					continue;
				}
				
				minCut[i][ln] = INT_MAX;
				
				for ( j = ln ; j > i ; j-- ){
					if ( i < j && isPalin[i][j-1] ) minCut[i][ln] = MIN(minCut[i][ln], minCut[j][ln] + 1);
				}
			}
					
			printf("Case %d: %d\n", ks, minCut[0][ln] + 1);
		}
	}
	
	return 0;
}

