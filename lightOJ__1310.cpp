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

int R, C;
map<unsigned, short> dp[100][8];
short ks;
char grid[100][9];

int rec(int row, int col, unsigned mask){
	int res = 0, flag, now;
	
	if ( row == R ) return 0;
	if ( dp[row][col].find(mask) != dp[row][col].end() ) return dp[row][col][mask];
	
	/*
	33
	22
	11
	*/
	//printf("In %d %d %x\n", row, col, mask);
	if ( row + 3 <= R && col + 2 <= C ){
		flag = 1;
		for ( int i = 0 ; i < 3 && flag ; i++ )
			for ( int j = 0 ; j < 2 ; j++ ){
				if ( grid[row + i][col + j] == '#' ){
					flag = 0;
					break;
				}
				
				if ( mask & (3 << ((col+j)<<1)) ){
					flag = 0;
					break;
				}
			}

		if ( flag == 1 ){
			if ( col + 2 < C ) now = 1 + rec(row, col + 2, mask | (2<<(col<<1)) | (2<<((col+1)<<1)));
			else now = 1 + rec(row + 1, 0, mask | (2<<(col<<1)) | (2<<((col+1)<<1)));
			if ( res < now ) res = now;
		}
	}
	
	/*
	222
	111
	*/
	if ( row + 2 <= R && col + 3 <= C ){
		flag = 1;
		for ( int i = 0 ; i < 2 && flag ; i++ )
			for ( int j = 0 ; j < 3 ; j++ ){
				if ( grid[row + i][col + j] == '#' ){
					flag = 0;
					break;
				}
				
				if ( mask & (3 << ((col + j)<<1)) ){
					flag = 0;
					break;
				}
			}

		if ( flag == 1 ){
			if ( col + 3 < C ) now = 1 + rec(row, col + 3, mask | (1<<(col<<1)) | (1<<((col + 1)<<1)) | (1<<((col+2)<<1)));
			else now = 1 + rec(row + 1, 0, mask | (1<<(col<<1)) | (1<<((col + 1)<<1)) | (1<<((col+2)<<1)));
			if ( res < now ) res = now;
		}
	}
	
	if ( mask & (3<<(col<<1))){
		if ( col + 1 < C ) now = rec(row, col + 1, mask - (1<<(col<<1)));
		else now = rec(row + 1, 0, mask - (1<<(col<<1)));
	}
	else{
		if ( col + 1 < C ) now = rec(row, col + 1, mask);
		else now = rec(row + 1, 0, mask);
	}
	if ( res < now ) res = now;
	
	return dp[row][col][mask] = res;
}

int main(){
	short test;
	char inp[102];
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &C, &R);
			for ( int i = 0 ; i < C ; i++ ){
				scanf("%s", inp);
				for ( int j = 0 ; j < R ; j++ ) grid[j][i] = inp[j];
			}
			
			printf("Case %d: %d\n", ks, rec(0, 0, 0));
			for ( int i = 0 ; i < R ; i++ )
				for ( int j = 0 ; j < C ; j++ ) dp[i][j].clear();
		}
	}
	
	return 0;
}

