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
#define SIZE 30001
using namespace std;

typedef long long ll;
typedef unsigned long long llu;

list<int> adj[SIZE];
int n;
int parent[SIZE], subTree[SIZE];
int fact[SIZE], invFact[SIZE];
int MOD = 1000000007;

int bigMod(int base, int pwr, int mod){
	ll tmp = base, res = 1LL;
	
	while ( pwr ){
		if ( pwr & 1 ) res = ( res * tmp ) % mod;
		pwr >>= 1;
		tmp = ( tmp * tmp ) % mod;
	}
	
	return (int)(res);
}

void initTables(){
	fact[0] = fact[1] = invFact[0] = invFact[1] = 1;
	
	for ( int i = 1 ; i < SIZE ; i++ ){
		ll tmp = fact[i-1];
		tmp *= i;
		fact[i] = tmp % MOD;
		invFact[i] = bigMod(fact[i], MOD - 2, MOD);
	}
}

int dfs(int u){
	ll res = 1;
	list<int>::iterator ptr;
	
	subTree[u] = 1;
	for ( ptr = adj[u].begin() ; ptr != adj[u].end() ; ptr++ ){
		int v = *ptr;
		if ( parent[v] == u ){
			res = ( res * dfs(v) ) % MOD;
			subTree[u] += subTree[v];
			res = ( res * invFact[subTree[v]] ) % MOD;
		}
	}
	
	adj[u].clear();
	res = ( res * fact[subTree[u]-1] ) % MOD;
//	printf("%d %d %lld\n", u, subTree[u], res);
	return (int)(res);
}
		
int main(){
	int test, ks;
	
	initTables();
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			for ( int i = 0 ; i < n ; i++ ) parent[i] = -1, subTree[i] = 0;
			
			for ( int i = 1 ; i < n ; i++ ){
				int u, v;
				scanf("%d%d", &u, &v);
				u--, v--;
				parent[v] = u;
				adj[u].pb(v);
			}
			
			int ceo = -1;
			for ( int i = 0 ; i < n ; i++ ){
				if ( parent[i] == -1 ){
					ceo = i;
					break;
				}
			}
			
			printf("Case %d: %d\n", ks, dfs(ceo));
		}
	}
	
	return 0;
}
/*
5
2 1
2 3
3 4
3 5
*/
/*
8
*/
