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
typedef pair<int, int> pii;

list<pii>adj[15];
int n;
double expCost[15][1<<15];
char isVisitable[15][1<<15];
int vis[15][1<<15], vis2[15][1<<15], Turn;

char findVisitability(int now, int mask){
	char res = 0;
	list<pii>::iterator ptr;
	
	if ( mask == ~(~0 << n)) return 1;
	if ( vis2[now][mask] == Turn ) return isVisitable[now][mask];
	vis2[now][mask] = Turn;
	
	for ( ptr = adj[now].begin() ; ptr != adj[now].end() ; ptr++ ){
		if ( mask & (1<<(ptr->first))) continue;
		if ( !res && findVisitability(ptr->first, mask | (1<<(ptr->first))) ) res = 1;
	}
	
	return isVisitable[now][mask] = res;
}

double rec(int now, int mask){
	double res = 5;
	int ej = 0;
	list<pii>::iterator ptr;
	
	if ( vis[now][mask] == Turn ) return expCost[now][mask];
	vis[now][mask] = Turn;
	
	for ( ptr = adj[now].begin() ; ptr != adj[now].end() ; ptr++ ){
		if ( mask & (1<<(ptr->first)) ) continue;
		if (!findVisitability(ptr->first, mask | (1<<(ptr->first)))) continue;
		ej++;
		res += rec(ptr->first, mask | (1<<(ptr->first))) + ptr->second;
	}
	
	if ( ej ) res /= 1.0 * ej;
	else res = 0;
	
	return expCost[now][mask] = res;
}

int main(){
	int test, ks, e, u, v, w;

	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &n, &e);
			for ( u = 0 ; u < n ; u++ ) adj[u].clear();
			
			while ( e-- ){
				scanf("%d%d%d", &u, &v, &w);
				pii p(v, w);
				adj[u].pb(p);
				pii q(u, w);
				adj[v].pb(q);
			}
			
			++Turn;
			printf("Case %d: %.10lf\n", ks, rec(0, 1));
		}
	}
	
	return 0;
}

