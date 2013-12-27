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

llu dp[51][51][51];
char vis[51][51][51];

llu rec(int N, int K, int S){
	int i;
	llu res = 0;
	
	if ( N == 0 && S == 0 ) return 1;
	if ( N == 0 || S <= 0 ) return 0;
	if ( vis[N][K][S] ) return dp[N][K][S];
	
	vis[N][K][S] = 1;
	//printf("%d %d %d\n", N, K, S);
	for ( i = 1 ; i <= K && i <= S ; i++ ) res += rec(N-1, K, S-i);
	return dp[N][K][S] = res;
}

int main(){
	int test, ks;
	int N, K, S;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d%d", &S, &N, &K);
			printf("Case %d: %llu\n", ks, rec(N, K, S));
		}
	}
	
	return 0;
}

