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
#define SIZE 150002
#define TREESZ (SIZE<<2)

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

ll tree[TREESZ], updVal[TREESZ];
int x, y;

int lChild(int node){ return (node<<1) + 1; }
int rChild(int node){ return (1+node)<<1; }

void update(int node, int left, int right, ll val, int prev){
	int mid = ( left + right ) >> 1, lc = lChild(node), rc = rChild(node);

	if ( prev || ( x <= left && right <= y )){
		tree[node] += ( right - left + 1 ) * val;
		if ( left != right ) updVal[node] += val;
		else updVal[node] = 0;
		return;
	}
	
	if ( left == right ) return;
	
	if ( updVal[node] ){
		update(lc, left, mid, updVal[node], 1);
		update(rc, mid + 1, right, updVal[node], 1);
		updVal[node] = 0;
	}
	
	if ( x <= mid ) update(lc, left, mid, val, 0);
	if ( y > mid ) update(rc, mid + 1, right, val, 0);
	tree[node] = tree[lc] + tree[rc];
}

ll query(int node, int left, int right){
	int mid = ( left + right ) >> 1, lc = lChild(node), rc = rChild(node);
	
	if ( x <= left && right <= y ) return tree[node];
	
	if ( updVal[node] ){
		update(lc, left, mid, updVal[node], 1);
		update(rc, mid + 1, right, updVal[node], 1);
		updVal[node] = 0;
	}
	
	if ( y <= mid ) return query(lc, left, mid);
	else return query(rc, mid + 1, right);
}

int qPoints[SIZE];
int intervals[SIZE][2];
set<int>points;
vector<int>sorted;

int main(){
	int test,ks, n, q, i, pSz;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &n, &q);
			memset(tree, 0, sizeof(tree));
			memset(updVal, 0, sizeof(updVal));
			
			for ( i = 0 ; i < n ; i++ ){
				scanf("%d%d", &intervals[i][0], &intervals[i][1]);
				points.insert(intervals[i][0]);
				points.insert(intervals[i][1]);
			}
			
			for ( i = 0 ; i < q ; i++ ){
				scanf("%d", &qPoints[i]);
				points.insert(qPoints[i]);
			}
			
			pSz = points.size();
			sorted.resize(pSz);
			copy(points.begin(), points.end(), sorted.begin());
			
			pSz--;
			for ( i = 0 ; i < n ; i++ ){
				x = upper_bound(sorted.begin(), sorted.end(), intervals[i][0]) - sorted.begin() - 1;
				y = upper_bound(sorted.begin(), sorted.end(), intervals[i][1]) - sorted.begin() - 1;
				update(0, 0, pSz, 1LL, 0);
			}
			
			printf("Case %d:\n", ks);
			for ( i = 0 ; i < q ; i++ ){
				x = y = upper_bound(sorted.begin(), sorted.end(), qPoints[i]) - sorted.begin() - 1;
				//printf("%d -> ", x);
				printf("%lld\n", query(0, 0, pSz));
			}
			
			points.clear();
		}

	}
	
	return 0;
}
/*
5 13
6 12
8 8
10 12
8 11
0 12
0 1 2 3 4 5 6 7  8 9 10 11 12
*/
