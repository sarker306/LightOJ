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

#define SIZE 150005

vector<int>initial;

int sTree[SIZE<<2];
int x;

int lChld(int ind){ return 1 + (ind<<1); }
int rChld(int ind){ return ( 1+ind )<<1; }

void init(int ind, int left, int right){
	int mid = (left+right)>>1, lc = lChld(ind), rc = rChld(ind);

	if ( left == right ){
		sTree[ind] = 0;
		return;
	}

	init(lc, left, mid);
	init(rc, mid + 1, right);
	sTree[ind] = 0;
}

void update(int ind, int left, int right, int val){
	int mid = (left+right)>>1, lc = lChld(ind), rc = rChld(ind);
	if ( left > x || right < x ) return;
	
	if ( left == right ){
		sTree[ind] += val;
		return;
	}
	
	if ( x <= mid ) update(lc, left, mid, val);
	else update(rc, mid + 1, right, val);
	sTree[ind] = sTree[lc] + sTree[rc];
}

int query(int ind, int left, int right, int K){
	int mid = (left+right)>>1, lc = lChld(ind), rc = rChld(ind);
	
	if ( left == right ) return left;
	if ( sTree[lc] >= K ) return query(lc, left, mid, K);
	else return query(rc, mid + 1, right, K - sTree[lc]);
}

int main(){
	int test;
	char qCom[10];
	int qArg;
	
	while ( scanf("%d", &test) == 1 ){
		for ( int kase = 1 ; kase <= test ; kase++ ){
			int n, q;
			
			scanf("%d%d", &n, &q);
			initial.clear();
			
			init(0, 0, SIZE - 2);
			
			for ( int i = 0 ; i < n ; i++ ){
				int p;
				scanf("%d", &p);
				initial.pb(p);
				x = i;
				update(0, 0, SIZE - 2, 1);
			}

			printf("Case %d:\n", kase);
			for ( int i = 0 ; i < q ; i++ ){
				scanf("%s%d", qCom, &qArg);
				if ( qCom[0] == 'a' ){
					initial.pb(qArg);
					x = initial.size() - 1;
					update(0, 0, SIZE - 2, 1);
				}
				else{
					if ( sTree[0] < qArg ){
						puts("none");
						continue;
					}
					int val = query(0, 0, SIZE - 2, qArg);
					printf("%d\n", initial[val]);
					x = val;
					update(0, 0, SIZE - 2, -1);
				}
			}
		}
	}
	
	return 0;
}

