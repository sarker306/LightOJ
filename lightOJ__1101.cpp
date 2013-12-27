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

#define MAXEDGE 100005
#define SIZE 50005
#define LOGSZ 17

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

struct Edge{
	int u, v, w;
	
	bool operator<(const Edge &p) const{
		return w > p.w;
	}
	
	int scan(){ return scanf("%d%d%d", &u, &v, &w) == 3; }
	void print(){ printf("%d %d %d\n", u, v, w); }
};

int n, e;
Edge edges[MAXEDGE];
Edge treeEdges[SIZE];

int rank[SIZE], parent[SIZE], val[SIZE];
list<Edge> adj[SIZE];
int P[SIZE][LOGSZ], maxi[SIZE][LOGSZ];

int getParent(int u){
	if ( parent[u] != u ) parent[u] = getParent(parent[u]);
	return parent[u];
}

void link( int u, int v ){
	if ( rank[u] > rank[v] ) parent[v] = u;
	else parent[u] = v;
	if ( rank[u] == rank[v] ) rank[v]++;
}

void mstInit(){
	int i;
	
	for ( i = 0 ; i <= n ; i++ ) parent[i] = i, rank[i] = 0;
}

void dfsInit(){
	int i;
	
	for ( i = 0 ; i <= n ; i++ ) parent[i] = -1, rank[i] = -1;
	rank[1] = 0;
}

void adjClear(){
	int i;
	
	for ( i = 0 ; i <= n ; i++ ) adj[i].clear();
}

void dfs(int u){
	int v;
	
	for ( list<Edge>::iterator ptr = adj[u].begin() ; ptr != adj[u].end() ; ptr++ ){
		v = ptr->v;
		if ( rank[v] == -1 ){
			rank[v] = rank[u] + 1;
			parent[v] = u;
			val[v] = ptr->w;
			dfs(v);
		}
	}
}

void Kruskal(){
	int i, x, y, k = 0;
	Edge now;

	mstInit();
	make_heap(edges, edges + e);
	
	for ( i = 0 ; i < e ; i++ ){
		now = edges[0];
		
		if ( ( x = getParent(now.u)) != ( y = getParent(now.v)) ){
			link(x, y);
			treeEdges[k++] = now;
			adj[now.u].pb(now);
			now.u ^= now.v ^= now.u ^= now.v;
			adj[now.u].pb(now);
			//now.print();
		}
		
		if ( k + 1 == n ) break;
		pop_heap(edges, edges + e - i);
	}
}

void preprocess(){
	int i, log;
	
	for ( i = 1 ; i <= n ; i++ )
		for ( log = 0 ; ( 1 << log ) < n ; log++ )
			P[i][log] = -1, maxi[i][log] = INT_MIN;

	for ( i = 2 ; i <= n ; i++ ) P[i][0] = parent[i], maxi[i][0] = val[i];
	
	for ( log = 1 ; ( 1 << log ) < n ; log++ )
		for ( i = 1 ; i <= n ; i++ )
			if ( P[i][log-1] != -1 ){
				P[i][log] = P[P[i][log-1]][log-1];
				maxi[i][log] = MAX(maxi[i][log-1], maxi[P[i][log-1]][log-1]);
			}
}

int findMax(int u, int v){
	int i, log, curMax = INT_MIN;
	
	if ( rank[u] < rank[v] ) u ^= v ^= u ^= v;
	for ( log = 0 ; ( 1 << log ) <= rank[u] ; log++ );
	log--;
	
	for ( i = log ; i >= 0 ; i-- )
		if ( rank[u] - ( 1 << i ) >= rank[v] ){
			curMax = MAX( curMax, maxi[u][i] );
			u = P[u][i];
		}

	if ( u != v ){
		for ( i = log ; i >= 0 ; i-- ){
			if ( P[u][i] != -1 && P[u][i] != P[v][i] ){
				curMax = MAX(curMax, maxi[u][i]);
				curMax = MAX(curMax, maxi[v][i]);
				u = P[u][i], v = P[v][i];
			}
		}
		
		curMax = MAX(curMax, val[u]);
		curMax = MAX(curMax, val[v]);
	}
	
	return curMax;
}

int main(){
	int test, ks, i, u, v;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &n, &e);
			for ( i = 0 ; i < e ; i++ ) edges[i].scan();
			
			Kruskal();
			dfsInit();
			dfs(1);
			preprocess();
			
			printf("Case %d:\n", ks);
			scanf("%d", &i);
			while ( i-- ){
				scanf("%d%d", &u, &v);
				printf("%d\n", findMax(u, v));
			}
			
			adjClear();
		}
	}
	
	return 0;
}
/*
1
4 6
1 2 20
2 3 30
3 4 40
2 4 10
1 4 10
1 3 50
6
1 2
1 3
1 4
2 3
2 4
3 4
*/
