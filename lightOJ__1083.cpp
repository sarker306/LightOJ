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

int height[30005];
int lft[30005], rght[30005];

int main(){
	int test, kase, n;
	
	while ( scanf("%d", &test) == 1 ){
		for ( kase = 1 ; kase <= test ; kase++ ){
			scanf("%d", &n);
			for ( int i = 0 ; i < n ; i++ ) scanf("%d", &height[i]);
			
			lft[0] = 0;
			stack<int>stck;
			stck.push(0);
			
			for ( int i = 1 ; i < n ; i++ ){
				while ( stck.empty() == false ){
					if ( height[stck.top()] < height[i] ) break;
					stck.pop();
				}
				
				if ( stck.empty() ) lft[i] = i;
				else lft[i] = i - stck.top() - 1;
				stck.push(i);
			//	printf("Left %d : %d\n", i, lft[i]);
			}
			
			while ( stck.empty() == false ) stck.pop();
			
			rght[n-1] = 0;
			stck.push(n-1);
			
			for ( int i = n - 2 ; i >= 0 ; i-- ){
				while ( stck.empty() == false ){
					if ( height[stck.top()] < height[i] ) break;
					stck.pop();
				}
				
				if ( stck.empty() ) rght[i] = n - i - 1;
				else rght[i] = stck.top() - i - 1;
				stck.push(i);
				//printf("Right %d : %d\n", i, rght[i]);
			}
			
			ll max = LLONG_MIN;
			for ( int i = 0 ; i < n ; i++ ){
				ll tmp = (lft[i] + rght[i] + 1) * height[i];
				if ( max < tmp ) max = tmp;
			}
			
			printf("Case %d: %lld\n", kase, max);
		}
	}
	
	return 0;
}

