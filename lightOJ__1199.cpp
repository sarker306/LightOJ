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
#define SIZE 10001
#define MOD 7340033

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

int grundy[SIZE];

int findGrundy(int x){
	int i;
	set<int>avl;
	
	if ( grundy[x] != -1 ) return grundy[x];
	
	for ( i = 1 ; 2 * i < x ; i++ ){
		avl.insert(findGrundy(i) ^ findGrundy(x-i));
	}
	
	for ( i = 0 ; ; i++ ) if ( avl.find(i) == avl.end() ) break;
	return grundy[x] = i;
}

int main(){
	int n, res, test, ks;
	int x;
	memset(grundy, -1, sizeof(grundy));
	
	/*for ( int i = 1 ; i < SIZE ; i++ ){
		cout << i << " - " << findGrundy(i) << endl;
	}*/
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			res = 0;
			for ( int i = 0 ; i < n ; i++ ){
				scanf("%d", &x);;
				res ^= findGrundy(x);
			}

			printf("Case %d: %s\n", ks, ( res ? "Alice":"Bob" ));
		}
	}
	
	return 0;
}

