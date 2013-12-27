#include <stdio.h>
#include <string.h>

#define SZ 15001
#define MOD 100000007
typedef long long ll;

ll X[2][SZ], XX[SZ];

int main(){
	int N, S, K, i, j, test, ks;

	scanf("%d", &test);
	for ( ks = 1 ; ks <= test ; ks++ ){
		scanf("%d%d%d", &N, &K, &S);
		memset(X, 0, sizeof(X));
		memset(XX, 0, sizeof(XX));
		for ( j = 1 ; j <= K ; j++ ){
			X[0][j] = X[1][j] = j;
			XX[j] = XX[j-1] + X[1][j];
		}

		for ( j = K + 1 ; j <= S ; j++ ) XX[j] = XX[j-1];
		
		for ( i = 2 ; i <= N ; i++ ){
			for ( j = 1 ; j <= S ; j++ ){
				X[1][j] = X[1][j-1] + XX[j-1];
				if ( j >= K + 1 ) X[1][j] -= XX[j-K-1] + K * X[0][j-K-1];
				X[1][j] %= MOD;
				if ( X[1][j] < 0 ) X[1][j] += MOD;
			}

			for ( j = 1 ; j <= S ; j++ ){
				X[0][j] = X[1][j];
				XX[j] = XX[j-1] + X[1][j];
				if ( XX[j] >= MOD ) XX[j] -= MOD;
			}
		}

		printf("Case %d: %lld\n", ks, X[1][S]);
	}
	
	return 0;
}

