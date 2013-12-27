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

int mat[15][15], n, ks;
char vis[15][1<<15];
int dp[15][1<<15];

int rec(int rem, int musk){
	int i, j;
	int sum;
	
	if ( rem == 0 ) return 0;
	if ( vis[rem][musk] == ks ) return dp[rem][musk];
	
	vis[rem][musk] = ks;
	dp[rem][musk] = INT_MAX;
	
	for ( i = 0 ; i < n ; i++ ){
		sum = 0;
		if ( musk & (1<<i) ) continue;
		for ( j = 0 ; j < n ; j++ )
			if ( j == i || ( musk & (1<<j))) sum += mat[i][j];

		sum += rec(rem-1, musk | (1<<i));
		if ( sum < dp[rem][musk] ) dp[rem][musk] = sum;
	}
	
	return dp[rem][musk];
}

int main(){
	int test, i, j;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			
			for ( i = 0 ; i < n ; i++ )
				for ( j = 0 ; j < n ; j++ )
					scanf("%d", &mat[i][j]);

			printf("Case %d: %d\n", ks, rec(n, 0));
		}
	}
	
	return 0;
}

