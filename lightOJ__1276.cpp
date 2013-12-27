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

typedef long long ll;
typedef unsigned long long llu;

ll LIMIT = 2000000000000LL;
set<ll>verylucky;
vector<ll>lucky;
queue<ll>q;
vector<ll>arr;

void backtrack(ll val, int ind){
	ll max = LIMIT / val;
	//cout<<val<<endl;
	verylucky.insert(val);
	
	for ( int i = ind; i < lucky.size() && lucky[i] <= max ; i++ ){
		if ( verylucky.find(lucky[i] * val) == verylucky.end())
			backtrack(lucky[i] * val, i);
	}
}

int main(){
	int test;
	
	q.push(4);
	q.push(7);
	
	while (q.empty() == false ){
		ll u = q.front();
		q.pop();
		
		//cout<<u<<endl;
		lucky.pb(u);

		ll v = u * 10 + 4;
		if ( v <= LIMIT ) q.push(v);
		v = u * 10 + 7;
		if ( v <= LIMIT ) q.push(v);
	}
	
	//cout<<lucky.size()<<endl;
	for ( int i = 0 ; i < lucky.size() ; i++ ) backtrack(lucky[i], i);
	//cout<<verylucky.size()<<endl;
	
	lucky.clear();
	for( set<ll>::iterator ptr = verylucky.begin() ; ptr != verylucky.end() ; ptr++ )
		arr.push_back(*ptr);

	verylucky.clear();
	
	while ( cin >> test ){
		for ( int kase = 1 ; kase <= test ; kase++ ){
			ll a, b;
			scanf("%lld%lld", &a, &b);
			printf("Case %d: ", kase);
			printf("%ld\n", lower_bound(arr.begin(), arr.end(), b+1)-upper_bound(arr.begin(), arr.end(), a-1));
		}
	}
	
	return 0;
}

