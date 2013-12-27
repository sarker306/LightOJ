#include<stdio.h>
#include<stdlib.h>
#define MAXR 901
#define MAXC 8101
#define SIZE 900

double dp[501][501];
int vis[501][501];

double rec(int r, int b){
	double res = 0;
	
	if ( r == 0 ) return 1;
	if ( b == 0 ) return 0;
	if ( vis[r][b] ) return dp[r][b];
	
	vis[r][b] = 1;
	res += r * rec(r - 1, b - 1);
	if ( b >= 2 ) res += b * rec(r, b - 2);
	
	return dp[r][b] = res / (r + b);
}

int main(){
	int test, ks, r, b;
	int i, j;

	dp[0][0] = 0;
	for ( i = 1 ; i <= 500 ; i++ ) dp[0][i] = 1;
	for ( i = 1 ; i <= 500 ; i++ ) dp[i][0] = 0;
	
	for ( i = 1 ; i <= 500 ; i++ ){
		for ( j = 1 ; j <= 500 ; j++ ){
			dp[i][j] = i * dp[i-1][j-1];
			if ( j >= 2 ) dp[i][j] += j * dp[i][j-2];
			dp[i][j] /= (i + j);
		}
	}
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &r, &b);
			printf("Case %d: %.10lf\n", ks, dp[r][b]);
		}
	}
	
	return 0;
}

