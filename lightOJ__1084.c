#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define INF 1000000

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef long long ll;
typedef unsigned long long llu;

int arr[100005], n, k, res[100005];

int cmp(const void *a, const void *b){ return *(int*)a - *(int*)b; }

int lBound(int *a, int len, int x){
	int lo = 0, hi = len, mid;
	
	while ( lo + 1 < hi ){
		mid = ( lo + hi ) >> 1;
		if ( a[mid] > x ) hi = mid;
		else lo = mid;
	}
	
	return lo;
}

int main(){
	int test, ks, i, nxt, flag;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &n, &k);
			flag = 1;
			for ( i = 0 ; i < n ; i++ ) scanf("%d", &arr[i]);
			qsort(arr, n, sizeof(int), cmp);
			
			res[n] = 0;
			for ( i = n - 1 ; i >= 0 ; i-- ){
				res[i] = 0;
				nxt = lBound(arr, n, arr[i] + 2*k);
				if ( nxt - i >= 2 ){
					res[i] = 1 + res[nxt+1];
					if ( nxt - 1 - i >= 2 ) res[i] = MIN((1 + res[nxt]), res[i]);
					if ( nxt - 2 - i >= 2 ) res[i] = MIN((1 + res[nxt-1]), res[i]);
				}
				else res[i] = INF;
			}
			
			printf("Case %d: %d\n", ks, (res[0] < INF) ? res[0] : -1);
		}
	}
	
	return 0;
}

