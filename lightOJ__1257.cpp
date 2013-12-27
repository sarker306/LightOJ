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
#define SIZE 30003

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

list<pair<int, int> > adj[SIZE];
int n;
int distDown[SIZE], distUp[SIZE], parent[SIZE];
char visited[SIZE];

void init(){
	for ( int i = 0 ; i <= n ; i++ ) parent[i] = -1, visited[i] = 0;
	distUp[0] = 0;
}

int dfsDown(int u){
	list<pair<int, int> >::iterator ptr;
	
	distDown[u] = 0;
	visited[u] = 1;
	for ( ptr = adj[u].begin() ; ptr != adj[u].end() ; ptr++ ){
		int v = ptr->first;
		int w = ptr->second;
		
		if ( visited[v] != 1 ){
			distDown[u] = max(distDown[u], dfsDown(v) + w);
		}
	}
	
	return distDown[u];
}

void dfsUp(int u){
	list<pair<int, int> >::iterator ptr;
	int maxDistDown[2] = {0, 0}, indMax = -1;

	visited[u] = 2;
	for ( ptr = adj[u].begin() ; ptr != adj[u].end() ; ptr++ ){
		int v = ptr->first;
		int w = ptr->second;
		
		if ( visited[v] == 2 ) continue;
		int tmp = w + distDown[v];
		if ( tmp > maxDistDown[1] ){
			if ( tmp > maxDistDown[0] ){
				maxDistDown[1] = maxDistDown[0];
				maxDistDown[0] = tmp;
				indMax = v;
			}
			else maxDistDown[1] = tmp;
		}
	}
	
//	printf("For %d, %d %d %d\n", u, maxDistDown[0], maxDistDown[1], indMax);
	
	for ( ptr = adj[u].begin() ; ptr != adj[u].end() ; ptr++ ){
		int v = ptr->first;
		int w = ptr->second;
		
		if ( visited[v] == 2 ) continue;
		if ( v == indMax ) distUp[v] = max(distUp[u] + w, maxDistDown[1] + w);
		else distUp[v] = max(distUp[u] + w, maxDistDown[0] + w);
		//printf("DistUp %d %d\n", v, distUp[v]);
	}
	
	for ( ptr = adj[u].begin() ; ptr != adj[u].end() ; ptr++ ){
		int v = ptr->first;
		int w = ptr->second;
		
		if ( visited[v] != 2 ){
			dfsUp(v);
		}
	}
}

int main(){
	int test, ks;
	int u, v, w;

	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			for ( int i = 1 ; i < n ; i++ ){
				scanf("%d%d%d", &u, &v, &w);
				adj[u].pb(pair<int, int>(v, w));
				adj[v].pb(pair<int, int>(u, w));
			}
			
			init();
			dfsDown(0);
			dfsUp(0);
			
			printf("Case %d:\n", ks);
			for ( int i = 0 ; i < n ; i++ ){
				printf("%d\n", max(distUp[i], distDown[i]));
				adj[i].clear();
			}
		}
	}
	
	return 0;
}

