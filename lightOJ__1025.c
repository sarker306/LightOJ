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

ll dp[61][61];
int vis[61][61], ks;
char arr[61];

ll rec(int st, int en){
	ll res = 0;
	
	if ( st == en ) return 2;
	if ( st > en ) return 1;
	if ( vis[st][en] == ks ) return dp[st][en];
	vis[st][en] = ks;
	
	if ( arr[st] == arr[en] ) res += rec(st + 1, en - 1);
	res += rec( st + 1, en ) + rec( st, en - 1 ) - rec(st + 1, en - 1);
	
	return dp[st][en] = res;
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		getchar();
		for ( ks = 1 ; ks <= test ; ks++ ){
			gets(arr);
			printf("Case %d: %lld\n", ks, rec(0, strlen(arr) - 1) - 1); /* 1 minus, don't want all characters deleted */
		}
	}
	
	return 0;
}

