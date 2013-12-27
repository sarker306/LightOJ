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

int n, k, ks;
vector<int> sticks[2];
//double dp[5001][5001];
double tot[2], avgIndist, Hn[5001];
//int vis[5001][5001];

/* p = currently untouched, q = currently untouched distinguishable
	p - q currently untouched indistinguishable
	n - p currently touched, k - q currently touched distinguishable
	n + q - p - k currently touched indistinguishable
	currently n - k + q sticks onboard

	(n - k + q)*E(p,q) = (E(p-1, q) + sid)*(p-q) + (E(p, q) + sid)*(n+q-p-k) + (E(p-1,q-1)+sd)*q
	p*E(p,q) = E(p-1,q)*(p-q) + (E(p-1,q-1 + sd)*(q) + totalIndist
*/
double calc(int p, int q){
	double tmp[5001], dp1[5001];
	
	for ( int i = 0 ; i <= p ; i++ ){
		dp1[i] = tmp[i] = 0;
	}
	
	for ( int i = 1 ; i <= p ; i++ ){
		for ( int j = 0 ; j <= q ; j++ ) tmp[j] = dp1[j];
		for ( int j = 0 ; j <= q ; j++ ){
			if ( i - j > p - q|| j > i ){
				dp1[j] = 0;
				continue;
			}
			dp1[j] = tot[1] + (i - j) * tmp[j];
			if ( j ) dp1[j] += j * ( tmp[j-1] + tot[0] / k );
			dp1[j] /= i;
		}
	}
	
	return dp1[q];
}

/*double calc(int p, int q){
	return Hn[p] * tot[1] + tot[0];
}
*/
int main(){
	int test, u, v;
	
	Hn[0] = 0;
	for ( int i = 1 ; i <= 5000 ; i++ ) Hn[i] = Hn[i-1] + 1.0/i;
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			k = 0;
			tot[0] = tot[1] = 0; // tot[i], total weight of sticks of type i
			sticks[0].clear();
			sticks[1].clear();
			for ( int i = 0 ; i < n ; i++ ){
				scanf("%d%d", &u, &v); // u = weight, v = type, v == 1, the stick is distinguishable by touch, v==2 it isn't
				v--;
				sticks[v].pb(u);
				if ( !v ) k++;

				tot[v] += u;
			}
			
			printf("Case %d: %.10lf\n", ks, calc(n, k));
		}
	}
	
	return 0;
}

