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

int ks;
int N;
int jmp[2][1002];
int eatTime[2][1002];
int vis[2][1002][1002], dp[2][1002][1002];

int rec(int building, int story, int remFruit){
	int res = INT_MAX, now;
	
	if ( story == N ) return remFruit == 0 ? 0 : 10000;
	if ( remFruit == 0 ) return 0;
	if ( vis[building][story][remFruit] == ks ) return dp[building][story][remFruit];
	vis[building][story][remFruit] = ks;

	now = eatTime[building][story] + rec(building, story + 1, remFruit - 1);
	if ( res > now ) res = now;
	if ( story + 1 < N ){
		now = eatTime[building][story] + jmp[building][story] + rec(building ^ 1, story + 1, remFruit - 1);
		if ( res > now ) res = now;
	}
	
	return dp[building][story][remFruit] = res;
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &N);
			for ( int i = 0 ; i < 2 ; i++ )
				for ( int j = 0 ; j < N ; j++ ) scanf("%d", &eatTime[i][j]);

			for ( int i = 0 ; i < 2 ; i++ ){
				for ( int j = 0 ; j < N - 1 ; j++ ) scanf("%d", &jmp[i][j]);
				jmp[i][N-1] = 10000; // where to go from floor N-1?
			}
			
			printf("Case %d: %d\n", ks, min(rec(0, 0, N), rec(1, 0, N)));
		}
	}
	
	return 0;
}

