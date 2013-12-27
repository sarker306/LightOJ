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
#define Pii pair<int, int>
#define INF 1000000000

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

int n, m, c, s, t;
int oil[105], cost[105][105];
vector< pair<int, int> > adj[105];

class Cmp{
public:
	bool operator()(Pii &x, Pii &y){ return cost[x.first][x.second] > cost[y.first][y.second]; }
};

void relax(int a, int b, int c, int d, int w, priority_queue<Pii, vector<Pii>, Cmp> &pq){
	if ( cost[a][b] > cost[c][d] + w ){
		cost[a][b] = cost[c][d] + w;
		pq.push(Pii(a, b));
	}
}

int dij(){
	int res = INF;
	priority_queue<Pii, vector<Pii>, Cmp> pq;
	
	for ( int i = 0 ; i < n ; i++ ) for ( int j = 0 ; j <= c ; j++ ) cost[i][j] = INF;
	cost[s][0] = 0;
	pq.push(Pii(s, 0));
	
	while ( pq.empty() == false ){
		Pii u = pq.top();
		int uu = u.first, uc = u.second;
		pq.pop();
		
		if ( uc + 1 <= c ) relax(uu, uc + 1, uu, uc, oil[uu], pq);
		for ( int i = 0 ; i < adj[uu].size() ; i++ ){
			int v = adj[uu][i].first;
			int w = adj[uu][i].second;
			
			if ( c < w ) continue;
			int nU, nC;
			nC = uc - w;
			if ( nC >= 0 ) relax(v, nC, uu, uc, 0, pq);
		}
	}
	
	for ( int i = 0 ; i <= c ; i++ ){
		res = min(res, cost[t][i]);
	}
	
	return res;
}
	
int main(){
	int test, ks;
	
	while ( cin >> test ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			cin >> n >> m;
			for ( int i = 0 ; i < n ; i++ ) cin >> oil[i];
			
			for ( int i = 0 ; i < m ; i++ ){
				int u, v, w;
				cin >> u >> v >> w;
				adj[u].pb(pair<int, int>(v, w));
				adj[v].pb(pair<int, int>(u, w));
			}
			
			int q;
			cin >> q;
			while ( q-- ){
				cin >> c >> s >> t;
				int res = dij();
				if ( res == INF ) cout << "impossible" << endl;
				else cout << res << endl;
			}
			
			for ( int i = 0 ; i < n ; i++ ) adj[i].clear();
		}
	}
	
	return 0;
}

