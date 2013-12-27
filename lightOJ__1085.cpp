#include <cstdio>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define ALL(v) (v).begin(), (v).end()
#define SET(a, x) memset((a), (x), sizeof(a))
#define SZ(a) ((int)(a).size())
#define CL(a) ((a).clear())
#define SORT(x) sort(ALL(x))
#define mp make_pair
#define pb push_back
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)
#define SIZE 100000

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

long MOD = 1000000007;
long TREE[SIZE<<2];
long lo, hi;
long lChild(long ind){ return 1 + (ind<<1); }
long rChild(long ind){ return (1+ind)<<1; }

long indx;

void update(long ind, long left, long right, long val){
	long mid = ( left + right ) >> 1, lC = lChild(ind), rC = rChild(ind);
	
	if ( left > indx || right < indx ) return;
	
	if ( left == right ) TREE[ind] = ( TREE[ind] + val ) % MOD;
	else{
		if ( indx <= mid ) update(lC, left, mid, val);
		else update(rC, mid + 1, right, val);
		TREE[ind] = (TREE[lC] + TREE[rC]) % MOD;
	}
}

long query(long ind, long left, long right){
	long mid = ( left + right ) >> 1, lC = lChild(ind), rC = rChild(ind);

	if ( hi < left || lo > right ) return 0;
	if ( left >= lo && right <= hi ) return TREE[ind];
	return (query(lC, left, mid) + query(rC, mid + 1, right)) % MOD;
}

long arr[SIZE+2], sorted[SIZE+2];

long binarySearch(long *vec, long size, long val){
	long low = 0, high = size;
	
	while ( low + 1 < high ){
		long mid = ( low + high )>>1;
		if ( vec[mid] > val ) high = mid;
		else low = mid;
	}
	
	return low;
}

int main(){
	int test, kase;
	long n, now, total;
	
	while ( scanf("%d", &test) == 1 ){
		for ( kase = 1 ; kase <= test ; kase++ ){
			set<long> mappd;
			now = 0;
			total = 0;
			scanf("%ld", &n);
			
			for ( int i = 0 ; i < n ; i++ ){
				scanf("%ld", arr + i);
				mappd.insert(arr[i]);
			}

			now = 0;
			for ( set<long>::iterator ptr = mappd.begin() ; ptr != mappd.end() ; ptr++ )
				sorted[now++] = *ptr;

			memset(TREE, 0, sizeof(TREE));
			
			for ( int i = 0 ; i < n ; i++ ){
				/*printf("-> %ld ", arr[i]);*/
				indx = binarySearch(sorted, now, arr[i]);
				hi = indx - 1;
				lo = 0;
				total = 1;
				if ( lo <= hi ) total = (query(0, 0, now) + 1) % MOD;
				/*printf(" %ld\n", total);*/
				update(0, 0, now, total);
			}
			/*puts("");*/
			
			lo = 0, hi = now;
			printf("Case %d: %ld\n", kase, query(0, 0, now));
		}
	}
	
	return 0;
}

