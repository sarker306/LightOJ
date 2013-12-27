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

int arr[100005];

int main(){
	int test, ks, n, i, k, j;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			n++;
			for ( i = 1  ; i < n ; i++ ) scanf("%d", arr + i);
			k = INT_MIN;
			for ( i = 1 ; i < n ; i++ ) if ( k < arr[i] - arr[i-1] ) k = arr[i] - arr[i-1];
			j = k;
			for ( i = 0 ; i < n - 1; i++ ){
				if ( arr[i] + j == arr[i+1] ) j--;
				else if ( arr[i] + j < arr[i+1] ) break;
			}
			
			if ( i != n - 1 ) k++;
			printf("Case %d: %d\n", ks, k);
		}
	}
	
	return 0;
}

