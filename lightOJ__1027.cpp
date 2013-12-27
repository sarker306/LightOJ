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

int gcd(int m, int n){
	while ( n ){
		int tmp = m;
		m = n;
		n = tmp%m;
	}
	
	return m;
}

int main(){
	int test, kase;
	
	while ( cin >> test ){
		for ( kase = 1; kase <= test ; kase++ ){
			int neg = 0, n, x, sum = 0;
			
			cin >> n;
			for ( int i = 0 ; i < n ; i++ ){
				cin >> x;
				if ( x < 0 ) neg++;
				sum += x > 0 ? x : -x;
			}
			
			cout<<"Case "<<kase<<": ";
			if ( neg == n ) cout<<"inf"<<endl;
			else {
				int d = gcd(sum, n - neg);
				cout<<sum/d<<'/'<<(n-neg)/d<<endl;
			}
		}
	}
	
	return 0;
}

