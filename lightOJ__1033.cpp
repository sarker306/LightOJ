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

char word[101];
unsigned char vis[101][101], ks;
unsigned char dp[101][101];

unsigned char rec(int lft, int rgt){
	if ( lft >= rgt ) return 0;
	if ( vis[lft][rgt] == ks ) return dp[lft][rgt];
	
	vis[lft][rgt] = ks;
	if ( word[lft] == word[rgt] ) dp[lft][rgt] = rec(lft + 1, rgt - 1);
	else dp[lft][rgt] = 1 + MIN(rec(lft, rgt-1), rec(lft+1, rgt));
	
	return dp[lft][rgt];
}

int main(){
	unsigned test;
	
	while ( scanf("%u", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%s", word);
			printf("Case %d: %u\n", ks, rec(0, strlen(word)-1));
		}
	}

	return 0;
}

