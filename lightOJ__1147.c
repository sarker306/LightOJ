#include <stdio.h>
#include <string.h>

long n, arr[105], ks, maxTeamA;
long total, sum;
long long dp[100005];
/*
Res(Pos, TeamA, Weight) = MAX( Res(Pos-1, TeamA-1, Weight - arr[Pos]) + arr[Pos], Res(Pos-1, TeamA, Weight) )
*/

long MAX(long a, long b) {
	return a > b ? a : b;
}

long MIN(long a, long b){
	return a < b ? a : b;
}

int cmp(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
}

int main(){
	int test, i, j;
	long k, teamA, teamB, temp, temp1;

	while ( scanf("%d", &test) == 1 ) {
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%ld", &n);
			total = 0;
			for ( i = 1 ; i <= n ; i++ ){
				scanf("%ld", &arr[i]);
				total += arr[i];
			}

			qsort(arr, n + 1, sizeof(long), cmp);

			sum = total;
			maxTeamA = (n>>1);
			memset(dp, 0, sizeof(dp));

			dp[0] = 1;
			for ( i = 1 ; i <= n ; i++ ){
				for ( k = total ; k >= 0 ; k-- ){
					if ( k >= arr[i] ) dp[k] |= (dp[k-arr[i]]<<1);
				}
			}

			for ( teamA = sum>>1, teamB = sum - (sum>>1) ; teamA >= 0 && teamB <= total ; teamA++, teamB-- ){
				if ( dp[teamA] & (1LL << (n/2) )) break;
				if ( dp[teamB] & (1LL << (n/2) )) break;
			}

			if ( teamA > teamB ) teamA ^= teamB ^= teamA ^= teamB;
			printf("Case %d: %ld %ld\n", ks, teamA, teamB);
		}
	}

	return 0;
}

