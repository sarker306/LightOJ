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

char word[12];
unsigned dp[2][2][12][2], dp2[2][2][12][2];
int vis[2][2][12][2], turn = 1, vis2[2][2][12][2];

unsigned rec2(int nonZero, int less, int pos, int last){
	int nless, nNonZero;
	unsigned res = 0;
	char i;

	if ( word[pos] == 0 && last == 0 ) return 0;
	if ( word[pos] == 0 && last == 1 ) return 1;
	if ( vis2[nonZero][less][pos][last] == turn ) return dp2[nonZero][less][pos][last];

	vis2[nonZero][less][pos][last] = turn;
	for ( i = '0' ; i <= '9' ; i++ ){
		nless = less;
		nNonZero = nonZero;
		if ( less == 0 && i > word[pos] ) continue;
		if ( less == 0 && i < word[pos] ) nless = 1;

		nNonZero = nonZero;
		if ( nonZero == 0 && i > '0' ) nNonZero = 1;
		res += rec2(nNonZero, nless, pos + 1, last);
	}

	return dp2[nonZero][less][pos][last] = res;
}

unsigned rec(int nonZero, int less, int pos, int last){
	int nless, nNonZero;
	unsigned res = 0;
	char i;
	
	if ( word[pos] == 0  ) return 0;
	if ( word[pos] == 0 && last == 1 ) return 1;
	if ( vis[nonZero][less][pos][last] == turn ) return dp[nonZero][less][pos][last];
	
	vis[nonZero][less][pos][last] = turn;
	for ( i = '0' ; i <= '9' ; i++ ){
		nless = less;
		if ( less == 0 && i > word[pos] ) continue;
		if ( less == 0 && i < word[pos] ) nless = 1;

		nNonZero = nonZero;
		if ( nonZero == 0 && i > '0' ) nNonZero = 1;
		if ( i == '0' && nonZero ) res += rec2(nNonZero, nless, pos + 1, 1) + rec(nNonZero, nless, pos + 1, 1);
		else res += rec(nNonZero, nless, pos + 1, last);
	}

	return dp[nonZero][less][pos][last] = res;
}

int main(){
	int tst, ks;
	unsigned a, b, res;
	
	while ( scanf("%d", &tst) == 1 ){
		for ( ks = 1 ; ks <= tst ; ks++ ){
			scanf("%u%u", &a, &b);
			sprintf(word, "%010u", b);
			res = rec(0, 0, 0, 0);
			turn++;
			if ( a ){
				a--;
				sprintf(word, "%010u", a);
				res -= rec(0, 0, 0, 0);
			}
			else res++;

			printf("Case %d: %u\n", ks, res);
			turn++;
		}
	}
			
	return 0;
}

