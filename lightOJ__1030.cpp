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

int main(){
	int arr[101];
	double expected[101];
	int test, kase, n;
	
	while ( cin >> test ){
		for ( kase = 1 ; kase <= test ; kase++ ){
			cin >> n;
			for ( int i = 0 ; i < n ; i++ ) cin >> arr[i];
			
			SET(expected, 0);
			expected[n-1] = arr[n-1];
			//printf("Expected[%d] = %lf\n", n-1, expected[n-1]);
			for ( int i = n - 2 ; i >= 0 ; i-- ){
				int j = MIN ( n - i - 1, 6 );
				//cout<<j<<endl;
				for ( int k = 1 ; k <= j ; k++ )
					expected[i] += expected[i+k];

				expected[i] /= j;
				expected[i] += arr[i];
				//printf("Expected[%d] = %lf\n", i, expected[i]);
			}
			
			printf("Case %d: %.10lf\n", kase, expected[0]);
		}
	}
				
	return 0;
}

