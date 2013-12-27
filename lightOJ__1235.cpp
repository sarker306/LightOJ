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
int n, k;
int coins[19];

int main(){
	int test, half, flag;
	
	while ( cin >> test ){
		for ( int kase = 1 ; kase <= test ; kase++ ){
			scanf("%d%d", &n, &k);
			for ( int i = 0 ; i < n ; i++ ) scanf("%d", &coins[i]);
			sort(coins, coins + n);
			
			flag = 0;
			half = n>>1;
			set<int> payable;
			payable.insert(0);
			for ( int i = 0 ; i < half && !flag ; i++ ){
				vector<int>temp;

				for ( set<int>::iterator ptr = payable.begin() ; ptr != payable.end() ; ptr++ ){
					temp.pb(*ptr + coins[i]);
					temp.pb(*ptr + (coins[i]<<1));
				}
				
				for ( vector<int>::iterator ptr = temp.begin() ; !flag && ptr != temp.end() ; ptr++ ){
					payable.insert(*ptr);
					if ( *ptr == k ) flag = 1;
				}
			}
			
			if ( flag == 0 ){
				set<int> pay2;
				pay2.insert(0);
				for ( int i = half ; i < n && !flag ; i++ ){
					vector<int> temp;

					for ( set<int>::iterator ptr = pay2.begin() ; ptr != pay2.end() ; ptr++ ){
						temp.pb(*ptr + coins[i]);
						temp.pb(*ptr + coins[i]*2);
					}

					for ( vector<int>::iterator ptr = temp.begin() ; !flag && ptr != temp.end() ; ptr++ ){
						pay2.insert(*ptr);
						if ( payable.find(k - *ptr) != payable.end() ) flag = 1;
					}
				}
			}
			
			printf("Case %d: %s\n", kase, (flag == 0 ? "No" : "Yes"));
		}
	}
	
	return 0;
}
/*
1
18 12
1 2 5 10 20 50 100 200 500 1000 2000 5000 10000 20000 50000 100000 200000 500000
*/

