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

char type[101][2];
int dst[101], D, stones;
vector<int> distEv;

void constructDistEv(){
	distEv.clear();
	distEv.pb(0);
	distEv.pb(D);
	
	for ( int i = 1 ; i <= stones ; i++ ){
		distEv.pb(dst[i]);
		distEv.pb(D - dst[i]);
		//printf("Stone %d, type %s -> %d %d\n", i, type[i], dst[i], D - dst[i]);
		for ( int j = i + 1 ; j <= stones ; j++ )
			distEv.pb(abs(dst[j] - dst[i]));
	}

	sort(distEv.begin(), distEv.end());
	
	/*for ( int i = 0 ; i < distEv.size() ; i++ ) printf("%d ", distEv[i]);
	puts("");*/
}

int bSearch();

int main(){
	int test, ks;
	char input[100];
	
	ios::sync_with_stdio(true);
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &stones, &D);
			for ( int i = 1 ; i <= stones ; i++ ){
				//scanf("%s%d", type[i], &dst[i]);
				scanf("%s", input);
				int j;
				for ( j = 0 ; input[j] != '-' ; j++ );
				strncpy(type[i], input, 1);
				j++;
				sscanf(input + j, "%d", &dst[i]);
			}
			
			constructDistEv();
			printf("Case %d: %d\n", ks, bSearch());
		}
	}
	
	return 0;
}

int N, src, snk;
#define SIZE 205
int cap[SIZE][SIZE];

void constGraph(int cutOff){
	N = 2*stones + 2;
	src = 0, snk = N - 1;
	
	for ( int i = 0 ; i < N ; i++ )
		for ( int j = 0 ; j < N ; j++ ) cap[i][j] = 0;
		
	for ( int i = 1 ; i <= stones ; i++ )
		cap[src][i] = ( dst[i] <= cutOff ) ? 2 : 0;

	for ( int i = stones + 1 ; i <= 2 * stones ; i++ )
		cap[i][snk] = ( D - dst[i - stones] <= cutOff ) ? INT_MAX : 0;

	for ( int i = 1 ; i <= stones ; i++ )
		for ( int j = stones + 1 ; j <= 2 * stones ; j++ ){
			if ( i + stones == j ){
				cap[i][j] = (type[i][0] == 'B') ? INT_MAX : 1;
			}
			else{
				int tmp = abs(dst[i] - dst[j - stones]);
				cap[j][i] = (tmp <= cutOff) ? INT_MAX : 0;
			}
		}

	/*printf("For cutOff %d\n", cutOff);
	for ( int i = 0 ; i < N ; i++ ){
		for ( int j = 0 ; j < N ; j++ ) printf("%11d", cap[i][j]);
		puts("");
	}*/
}

int now[SIZE];

bool bfs();
int dfs(int, int);

int maxFlow(){
	int totFlow = 0;
	
	while ( bfs() ){
		for ( int i = 0 ; i < N ; i++ ) now[i] = 0;
		while ( true ){
			int df = dfs(src, INT_MAX);
			if ( df > 0 ) totFlow += df;
			else break;
		}
	}
	
	return totFlow;
}

int L[SIZE];

bool bfs(){
	int q[SIZE], head, tail;
	
	for ( int i = 0 ; i < N ; i++ ) L[i] = -1;
	L[src] = 0;
	head = tail = 0;
	q[tail++] = src;
	
	while ( head != tail ){
		int u = q[head++];
		if ( u == snk ) return true;
		for ( int i = 0 ; i < N ; i++ ){
			if ( cap[u][i] > 0 && L[i] == -1 ){
				L[i] = L[u] + 1;
				q[tail++] = i;
			}
		}
	}
	
	return false;
}

int dfs(int u, int fl){
	if ( u == snk ) return fl;
	
	for ( ; now[u] < N ; now[u]++ ){
		if ( cap[u][now[u]] > 0 && L[now[u]] == L[u] + 1 ){
			int df = dfs(now[u], min(cap[u][now[u]], fl));
			if ( df > 0 ){
				cap[u][now[u]] -= df;
				cap[now[u]][u] += df;
				return df;
			}
		}
	}
	
	return 0;
}

int bSearch(){
	int lo = 0, hi = distEv.size() - 1;
	
	while ( lo + 1 < hi ){
		int mid = (lo + hi) >> 1;
		constGraph(distEv[mid]);
	//	printf("%d ... %d\n", mid, distEv[mid]);
		if ( maxFlow() >= 2 ) hi = mid;
		else lo = mid;
	}
	
	return distEv[hi];
}
/*
3
1 10
B 5
1 10
S 5
2 10
B 3 S 6
*/
