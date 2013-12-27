#include<stdio.h>
#include<stdlib.h>
#define MAXR 901
#define MAXC 8101
#define SIZE 75

char str[SIZE + 1];
typedef long long ll;
ll dp[SIZE][SIZE];
int vis[SIZE][SIZE], n, ks;
ll MOD = 1007;

int isOkay(int x, int y, int z){
	return (str[x] == 'R') + (str[y] == 'R') + (str[z] == 'R');
}

ll rec(int st, int en){
	ll res = 0;
	int i, j;

/*	printf("%d %d\n", st, en);*/
	if ( st > en ) return 1;
	if ( (en - st + 1) % 3 ) return 0;
	if ( vis[st][en] == ks ) return dp[st][en];
	
	vis[st][en]= ks;
	if ( st + 2 == en ){
		if ( isOkay(st, st + 1, st + 2) <= 1 ) return dp[st][en] = 1;
		else return dp[st][en] = 0;
	}
	for ( i = st + 1 ; i <= en ; i++ ){
		for ( j = i + 1 ; j <= en ; j++ ){
			if ( isOkay(st, i, j) > 1 ) continue;
			ll tmp = rec(st + 1, i - 1);
			/*tmp %= MOD;*/
			tmp *= rec(i + 1, j - 1);
			/*tmp %= MOD;*/
			tmp *= rec(j + 1, en);
			/*tmp %= MOD;*/
		/*	printf("%d %d %d selected, %lld\n", st, i, j, tmp);*/
			
			res += tmp;
			/*if ( res >= MOD ) res -= MOD;*/
		}
	}
	
/*	printf("dp[%d][%d] = %lld\n", st, en, res);*/
	return dp[st][en] = res;
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%s", str);
			printf("Case %d: %lld\n", ks, rec(0, strlen(str) - 1));
		}
	}
	
    return 0;
}

