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

int arr[102], N;
int ks;
int dp[102][102][102];
int vis[102][102][102];

int rec(int pos, int left, int right){
	int res = 0, now;
	
	if ( pos == N ) return 0;
	if ( vis[pos][left][right] == ks ) return dp[pos][left][right];
	vis[pos][left][right] = ks;
	if ( arr[pos] >= left && arr[pos] <= right ){
		now = 1 + rec(pos + 1, arr[pos], right);
		if ( res < now ) res = now;
		now = 1 + rec(pos + 1, left, arr[pos]);
		if ( res < now ) res = now;
	}
	
	now = rec(pos + 1, left, right);
	if ( res < now ) res = now;
	return dp[pos][left][right] = res;
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			set<int>heights;
			scanf("%d", &N);
			for ( int i = 0 ; i < N ; i++ ){
				scanf("%d", &arr[i]);
				heights.insert(arr[i]);
			}
			
			vector<int>sorted(heights.size());
			copy(heights.begin(), heights.end(), sorted.begin());
			sorted.push_back(INT_MAX);
			for ( int i = 0 ; i < N ; i++ ){
				arr[i] = upper_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin();
				//printf(" %d", arr[i]);
			}
			
			//puts("");
			
			printf("Case %d: %d\n", ks, rec(0, 0, N + 1));
		}
	}
	
	return 0;
}

