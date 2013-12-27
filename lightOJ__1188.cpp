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

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

#define SIZE 100002

int last[SIZE], qrs[50001][2], arr[SIZE], res[50001];
list<int> intervals[SIZE];
int tree[SIZE<<2];
int lo, hi;

int Left(int ind) { return 1 + (ind<<1); }
int Right(int ind) { return ( 1 + ind )<<1; }

void update(int ind, int left, int right, int val){
	int mid = (left + right)>>1, lc = Left(ind), rc = Right(ind);
	
	if ( left > hi || right < lo ) return;
	if ( left == right ){
		tree[ind] += val;
		return;
	}
	
	update(lc, left, mid, val);
	update(rc, mid + 1, right, val);
	tree[ind] = tree[lc] + tree[rc];
}

int query(int ind, int left, int right){
	int mid = (left + right)>>1, lc = Left(ind), rc = Right(ind);
	
	if ( left > hi || right < lo ) return 0;
	if ( left >= lo && right <= hi ) return tree[ind];
	return query(lc, left, mid) + query(rc, mid + 1, right);
}

int main(){
	int test, n, q;
	
	while ( scanf("%d", &test) == 1 ){
		for ( int ks = 1; ks <= test ; ks++ ){
			scanf("%d%d", &n, &q);
			memset(last, -1, sizeof(last));
			memset(tree, 0, sizeof(tree));
			for ( int i = 1 ; i <= n ; i++ ) scanf("%d", arr + i);
			for ( int i = 0 ; i < q ; i++ ){
				scanf("%d%d", &qrs[i][0], &qrs[i][1]);
				intervals[qrs[i][1]].push_back(i);
			}
			
			for ( int i = 1 ; i <= n ; i++ ){
				lo = hi = last[arr[i]];
				update(0, 1, n, -1);
				
				lo = hi = last[arr[i]] = i;
				update(0, 1, n, 1);
				
				for ( list<int>::iterator ptr = intervals[i].begin() ; ptr != intervals[i].end() ; ptr++ ){
					lo = qrs[*ptr][0], hi = qrs[*ptr][1];
					res[*ptr] = query(0, 1, n);
				}
			}
			
			printf("Case %d:\n", ks);
			for ( int i = 0 ; i < q ; i++ ) printf("%d\n", res[i]);
			for ( int i = 1 ; i <= n ; i++ ) intervals[i].clear();
		}
	}
	
	return 0;
}

