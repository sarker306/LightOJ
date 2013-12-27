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

vector<ll> coll;
ll arr[1500];
ll MOD = 100000007;

void init(){
	set<ll> pwrs;
	
	for ( ll i = 2 ; i <= 100000 ; i++ ){
		ll p = i * i;
		//cout<<p<<' '<<i<<endl;
		while ( p <= 10000000000LL ){
			pwrs.insert(p);
			p *= i;
		}
	}
	
	//cout<<pwrs.size()<<endl;
	coll.resize(pwrs.size() + 1);
	coll[0] = 0;
	copy(pwrs.begin(), pwrs.end(), coll.begin() + 1);
	coll.pb(10000000001LL);
	
	arr[0] = arr[1] = 1;
	for ( int i = 2 ; i < 1500 ; i++ ){
		ll res = 0;
		for ( int j = 0 ; j < i ; j++ ){
			res += arr[j] * arr[i - j - 1];
			res %= MOD;
		}
		
		arr[i] = res;
	}
	
	arr[0] = 0;
}

int main(){
	ll a, b;
	int test;
	init();
	
	while ( scanf("%d", &test) == 1 ){
		for ( int ks = 1 ; ks <= test ; ks++ ){
			scanf("%lld%lld", &a, &b);
			int n = upper_bound(coll.begin(), coll.end(), b) - upper_bound(coll.begin(), coll.end(), a - 1);
			printf("Case %d: %d\n", ks, arr[n]);
		}
	}
	
	return 0;
}

