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

int vis[101][101], ks;
int dp[101][101];
char res[101][101][101];
char first[101], second[101];

int LCS(int i, int j){
	if ( i < 0 || j < 0 ) return 0;
	if ( vis[i][j] == ks ) return dp[i][j];
	
	vis[i][j] = ks;
	if ( first[i] == second[j] ){
		dp[i][j] = 1 + LCS(i-1, j-1);
		//parent[i][j].set(i-1, j-1);
		if ( i && j ) sprintf(res[i][j], "%c%s", first[i], res[i-1][j-1]);
		else sprintf(res[i][j], "%c", first[i]);
	}
	else{
		dp[i][j] = MAX(LCS(i-1, j), LCS(i, j-1));
		if ( dp[i][j] == dp[i-1][j] && dp[i][j] == dp[i][j-1] ){
		/*	if ( first[parent[i-1][j].i] <= first[parent[i][j-1].i] )
				parent[i][j] = parent[i-1][j];
			else parent[i][j] = parent[i][j-1];*/
			if ( strcmp(res[i-1][j], res[i][j-1]) < 0 ) strcpy(res[i][j], res[i-1][j]);
			else strcpy(res[i][j], res[i][j-1]);
		}
		//else if ( dp[i][j] == dp[i-1][j] ) parent[i][j] = parent[i-1][j];
		else if ( dp[i][j] == dp[i-1][j] ) strcpy(res[i][j], res[i-1][j]);
	//	else parent[i][j] = parent[i][j-1];
		else strcpy(res[i][j], res[i][j-1]);
	}
	
	return dp[i][j];
}

void strRev(char *str){
	int i, j;
	
	for ( j = 0 ; str[j] ; j++ );
	for ( i = 0, --j ; i < j ; i++, j-- )
		if ( str[i] != str[j] ) str[i] ^= str[j] ^= str[i] ^= str[j];
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%s%s", first, second);
			strRev(first), strRev(second);
			printf("Case %d: ", ks);
			if(LCS(strlen(first)-1, strlen(second)-1)){
				//printLCS(strlen(first)-1, strlen(second)-1);
				puts(res[strlen(first)-1][strlen(second)-1]);
			}
			else puts(":(");
		}
	}
	
	return 0;
}

