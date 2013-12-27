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
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#define SIZE 100005
using namespace std;

typedef long long ll;
typedef unsigned long long llu;

int arr[SIZE], d;
int maxi[SIZE<<2], mini[SIZE<<2];

int leftC(int ind) { return 1 + (ind<<1); }
int rightC(int ind){ return (1 + ind)<<1; }

void init(int ind, int left, int right){
	int lc = leftC(ind), rc = rightC(ind), mid = (left+right)>>1;
	int diff = INT_MIN;
	
	if ( left == right ){
		mini[ind] = maxi[ind] = arr[left];
		return;
	}
	
	init(lc, left, mid);
	init(rc, mid+1, right);
	maxi[ind] = max(maxi[lc], maxi[rc]);
	mini[ind] = min(mini[lc], mini[rc]);
}

int x, y;

int queryMax(int ind, int left, int right){
	int lc = leftC(ind), rc = rightC(ind), mid = (left+ right)>>1;

	if ( left > y || right < x ) return INT_MIN;

	if ( left >= x && right <= y ) return maxi[ind];

	int lM = queryMax(lc, left, mid);
	int rM = queryMax(rc, mid + 1, right);

	return ( lM > rM ) ? lM : rM;
}

int queryMin(int ind, int left, int right){
	int lc = leftC(ind), rc = rightC(ind), mid = (left+ right)>>1;

	if ( left > y || right < x ) return INT_MAX;

	if ( left >= x && right <= y ) return mini[ind];

	int lM = queryMin(lc, left, mid);
	int rM = queryMin(rc, mid + 1, right);

	return ( lM < rM ) ? lM : rM;
}

int main(){
	int test, n;
	
	while ( scanf("%d", &test) == 1 ){
		for ( int kase = 1 ; kase <= test ; kase++ ){
			scanf("%d%d", &n, &d);
			
			for ( int i = 0 ; i < n ; i++ ) scanf("%d", &arr[i]);
			init(0, 0, n-1);
			
			int diff = 0;
			for ( int i = 0 ; i < n - d ; i++ ){
				x = i, y = i + d - 1;
				//cout << x << ' ' << y << " : " << queryMax(0, 0, n-1)<<' '<<queryMin(0, 0, n-1)<<endl;
				int tmp = queryMax(0, 0, n - 1) - queryMin(0, 0, n - 1);
				if ( diff < tmp ) diff = tmp;
			}
			
			printf("Case %d: %d\n", kase, diff);
		}
	}

	return 0;
}

