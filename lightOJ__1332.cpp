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

typedef long long ll;
typedef unsigned long long llu;

int countConf[12], tot = 1;
char grid[37][12];
int faka[36];
int base[37][37];
unsigned final[3][3] = {{12,36,12},{36,68,16},{12,16,2}};
unsigned groundCase[] = {15,18,3};

void matrixMult(unsigned to[37][37], unsigned one[37][37], unsigned two[37][37]){
	unsigned tmp[37][37];
	
	for ( int i = 0 ; i < 37 ; i++ )
		for ( int j = 0 ; j < 37 ; j++ ){
			tmp[i][j] = 0;
			for ( int k = 0 ; k < 37 ; k++ ) tmp[i][j] += one[i][k] * two[k][j];
		}

	for ( int i = 0 ; i < 37 ; i++ )
		for ( int j = 0 ; j < 37 ; j++ )
			to[i][j] = tmp[i][j];
}

unsigned matrixExp(int pwr){
	unsigned tmp[37][37], res[37][37], sum = 0;
	
	if ( pwr == 0 ) return 36;
	for ( int i = 0 ; i < 37 ; i++ ){
		for ( int j = 0 ; j < 37 ; j++ ) res[i][j] = 0, tmp[i][j] = base[i][j];
		res[i][i] = 1;
	}
	
	while ( pwr ){
		if ( pwr & 1 ) matrixMult(res, res, tmp);
		matrixMult(tmp, tmp, tmp);
		pwr >>= 1;
	}
	
	for ( int i = 0 ; i < 37 ; i++ )
		for ( int j = 0 ; j < 37 ; j++ )
			sum += res[i][j];
			
	return sum;
}

void init(){
	for ( int i = 0 ; i < 37 ; i++ )
		for ( int j = 0 ; j < 10 ; j++ ) grid[i][j] = '-';

	for ( int i = 0 ; i < 10 ; i++ ){
		grid[0][i] = '*';
		for ( int j = 0 ; j + 1 < i ; j++ ){
			grid[0][j] = '*';
			int cnt = 0;
			for ( int k = 0 ; k < 10 ; k++ ){
				if ( grid[0][k] == '*' ) continue;
				if ( k && grid[0][k-1] == '*' ) continue;
				if ( k + 1 < 10 && grid[0][k+1] == '*' ) continue;
				cnt++;
			}

			strcpy(grid[tot], grid[0]);
			faka[tot++] = cnt;
			countConf[cnt]++;
			grid[0][j] = '-';
		}
		
		grid[0][i] = '-';
	}
	
	for ( int i = 1 ; i < tot ; i++ )
		for ( int j = 1 ; j < tot ; j++ ){
			int k;
			for ( k = 0 ; k < 10 ; k++ ){
				if ( grid[j][k] == '*' ){
					if ( grid[i][k] == '*' ) break;
					if ( k && grid[i][k-1] == '*' ) break;
					if ( k + 1 < 10 && grid[i][k+1] == '*' ) break;
				}
			}
			
			if ( k == 10 ) base[i][j]++;
		}
}

int main(){
	int test, n;
	init();
	
	while ( scanf("%d", &test) == 1 ){
		for ( int ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			printf("Case %d: %u\n", ks, matrixExp(n-1));
		}
	}
	
	return 0;
}

