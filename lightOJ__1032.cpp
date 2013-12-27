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

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

int ks, n;
char pattern[33];
int vis[33][2][2], vis2[33][2][2];
ll dp[33][2][2], dp2[33][2][2];

ll rec2(int pos, int less, int last){
	char ch;
	ll sum = 0;
	int nless;

	if ( pos == 32 ) return 1;
	if ( vis2[pos][less][last] == ks ) return dp2[pos][less][last];

	vis2[pos][less][last] = ks;

	for ( ch = '0' ; ch < '2' ; ch++ ){
		nless = less;
		if ( less == 0 && ch > pattern[pos] ) continue;
		if ( less == 0 && ch < pattern[pos] ) nless = 1;

		sum += rec2(pos+1, nless, ch - '0');
	}

	return dp2[pos][less][last] = sum;
}

ll rec(int pos, int less, int last){
	char ch;
	ll sum = 0;
	int nless;
	
	if ( pos == 32 ) return 0;
	if ( vis[pos][less][last] == ks ) return dp[pos][less][last];
	
	vis[pos][less][last] = ks;
	
	for ( ch = '0' ; ch < '2' ; ch++ ){
		nless = less;
		if ( less == 0 && ch > pattern[pos] ) continue;
		if ( less == 0 && ch < pattern[pos] ) nless = 1;
		
		if ( last == 1 && ch == '1' ) sum += rec2(pos+1, nless, ch-'0') + rec(pos+1, nless, ch - '0');
		else sum += rec(pos+1, nless, ch - '0');
	}

	return dp[pos][less][last] = sum;
}

int main(){
	int test, i;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			
			for ( i = 31 ; i >= 0 ; i-- ) pattern[31-i] = '0' + (( n & (1<<i) ) ? 1 : 0);
			pattern[32] = 0;

			printf("Case %d: %lld\n", ks, rec(0, 0, 0));
		}
	}
	
	return 0;
}

