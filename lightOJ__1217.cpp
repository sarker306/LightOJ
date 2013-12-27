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

int arr[1001];
int ks, n;
int dp[1001][2][2];
int vis[1001][2][2];

int rec(int pos, int take, int fTaken){
	int res = 0;
	
	if ( pos + 1 == n ){
		if ( fTaken || !take ) return 0;
		return arr[pos];
	}
	if ( vis[pos][take][fTaken] == ks ) return dp[pos][take][fTaken];
	vis[pos][take][fTaken] = ks;
	
	if ( take == 0 ) res = max(rec(pos + 1, 0, fTaken), rec(pos + 1, 1, fTaken));
	else res = arr[pos] + rec(pos + 1, 0, fTaken);
	return dp[pos][take][fTaken] = res;
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			for ( int i = 0 ; i < n ; i++ ) scanf("%d", &arr[i]);
			printf("Case %d: %d\n", ks, max(rec(0, 0, 0), rec(0, 1, 1)));
		}
	}
	
	return 0;
}

