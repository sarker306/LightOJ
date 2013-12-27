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

#define LOGSZ 18
#define SIZE 100005

typedef unsigned long long llu;
typedef long long ll;

long n;
long par[SIZE], level[SIZE], wght[SIZE];
list<pair<long, long> > adj[SIZE];
long P[SIZE][LOGSZ], mini[SIZE][LOGSZ], maxi[SIZE][LOGSZ];

void init(){
	long i;
	
	for ( i = 0 ; i < n ; i++ ){
		par[i] = level[i] = -1;
		adj[i].clear();
	}
	
	level[0] = 0;
}

void dfs(long u){
	list<pair<long, long> >::iterator ptr;
	long v;
	
	for ( ptr = adj[u].begin() ; ptr != adj[u].end() ; ptr++ ){
		v = ptr->first;
		if ( level[v] == -1 ){
			level[v] = level[u] + 1;
			par[v] = u;
			wght[v] = ptr->second;
			dfs(v);
		}
	}
}

void preprocess(){
	long i, j;
	
	for ( i = 0 ; i < n ; i++ )
		for ( j = 0 ; ( 1 << j ) < n ; j++ ){
			P[i][j] = -1;
			mini[i][j] = LONG_MAX;
			maxi[i][j] = LONG_MIN;
		}
		
	for ( i = 1 ; i < n ; i++ ){
		P[i][0] = par[i];
		mini[i][0] = maxi[i][0] = wght[i];
	}
	
	for ( j = 1 ; ( 1 << j ) < n ; j++ ){ // does it need another level to be sure?
		for ( i = 0 ; i < n ; i++ ){
			if ( P[i][j-1] != -1 ){
				P[i][j] = P[P[i][j-1]][j-1];
				mini[i][j] = MIN(mini[i][j-1], mini[P[i][j-1]][j-1]);
				maxi[i][j] = MAX(maxi[i][j-1], maxi[P[i][j-1]][j-1]);
			}
		}
	}
}

long process(long u, long v, long &maxCost, long &minCost){
	int log, i;
	
	maxCost = LONG_MIN, minCost = LONG_MAX;
	
	if ( level[u] < level[v] ) u ^= v ^= u ^= v; // u != v

	for ( log = 0 ; ( 1 << log ) <= level[u] ; log++ );
	log--;
	
	for ( i = log ; i >= 0 ; i-- ){
		if ( level[u] - (1<<i) >= level[v] ){
			if ( maxCost < maxi[u][i] ) maxCost = maxi[u][i];
			if ( minCost > mini[u][i] ) minCost = mini[u][i];
			u = P[u][i];
		}
	}
	
	if ( u == v ) return v;
	
	for ( i = log ; i >= 0 ; i-- ){
		if ( P[u][i] != -1 && P[u][i] != P[v][i] ){
			if ( maxCost < maxi[u][i] ) maxCost = maxi[u][i];
			if ( minCost > mini[u][i] ) minCost = mini[u][i];
			if ( maxCost < maxi[v][i] ) maxCost = maxi[v][i];
			if ( minCost > mini[v][i] ) minCost = mini[v][i];
			u = P[u][i], v = P[v][i];
		}
	}
	
	if ( minCost > wght[u] ) minCost = wght[u];
	if ( minCost > wght[v] ) minCost = wght[v];
	if ( maxCost < wght[u] ) maxCost = wght[u];
	if ( maxCost < wght[v] ) maxCost = wght[v];
	
	return par[u];
}

int main(){
	int test, ks;
	long u, v, w, mn, mx, q, i;

	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%ld", &n);
			
			init();
			for ( i = 1 ; i < n ; i++ ){
				scanf("%ld%ld%ld", &u, &v, &w);
				u--, v--;
				pair<long, long> p;
				p.first = v, p.second = w;
				adj[u].pb(p);
				p.first = u;
				adj[v].pb(p);
			}
			
			dfs(0);
			preprocess();
			
			scanf("%ld", &q);
			printf("Case %d:\n", ks);
			while ( q-- ){
				scanf("%ld%ld", &u, &v);
				u--, v--;
				w = process(u, v, mx, mn) + 1;
				//printf("%ld\n", w);
				printf("%ld %ld\n", mn, mx);
			}
		}
	}

	return 0;
}

