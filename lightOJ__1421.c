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

long val[100005], n;
long srt[100005];
long parent[100005];
long length[100005][2];
long ind;

long lBound(long x){
	long mid, lo = 0, hi = ind;

	if ( val[srt[hi - 1]] < x ) return hi - 1;
	while ( lo + 1 < hi ){
		mid = (lo + hi)>>1;
		if ( val[srt[mid]] >= x ) hi = mid;
		else lo = mid;
	}

	return lo;
}

int main(){
	int test, ks;
	long i, j, now, maxi;

	val[0] = INT_MIN;
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%ld", &n);
			for ( i = 1 ; i <= n ; i++ ) scanf("%ld", &val[i]);
			val[n+1] = INT_MIN;

			srt[0] = 0;
			length[0][0] = 0;
			ind = 1;
			for ( i = 1 ; i <= n ; i++ ){
				now = lBound(val[i]);
				parent[i] = srt[now];
				srt[now+1] = i;
				length[i][0] = length[srt[now]][0] + 1;
				if ( now + 1 == ind ) ind++;
			}

			srt[0] = n + 1;
			length[n+1][1] = 0;
			ind = 1;
			for ( i = n ; i ; i-- ){
				now = lBound(val[i]);
				parent[i] = srt[now];
				srt[now+1] = i;
				length[i][1] = length[srt[now]][1] + 1;
				if ( now + 1 == ind ) ind++;
			}

			maxi = 0;
			for ( i = 1 ; i <= n ; i++ ) maxi = MAX(maxi, MIN(length[i][0], length[i][1]));
			printf("Case %d: %ld\n", ks, 2*maxi - 1);
		}
	}

	return 0;
}

