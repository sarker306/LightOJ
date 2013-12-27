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

int dig[15];
int ks, m, n;
int vis[12][12];
unsigned dp[12][12];

unsigned rec(int pos, int last){
	unsigned sum = 0;
	int i;
	
	if ( pos == n ) return 1;
	if ( vis[pos][last] == ks ) return dp[pos][last];
	vis[pos][last] = ks;
	
	for ( i = 0 ; i < m ; i++ ){
		if ( last && abs(last - dig[i]) > 2 ) continue;
		sum += rec(pos + 1, dig[i]);
	}
	
	return dp[pos][last] = sum;
}

int main(){
	int test, x, tmp[12], i;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &m, &n);
			
			memset(tmp, 0, sizeof(tmp));
			for ( i = 0 ; i < m ; i++ ){
				scanf("%d", &x);
				tmp[x] = 1;
			}
			x = 0;
			for ( i = 0 ; i < 12 ; i++ )
				if ( tmp[i] ) dig[x++] = i;
			
			printf("Case %d: %u\n", ks, rec(0, 0));
		}
	}
	
	return 0;
}

