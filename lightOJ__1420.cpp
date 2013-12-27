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

int kase;
//ll ways[102][102][102];
int dp[102][102][102], dp2[102][102][102], dp3[102][102][102];
//int vis[102][102][102];
int vis1[102][102][102], vis2[102][102][102], vis3[102][102][102];
char A[102], B[102], C[102];
int MOD = 1000000007;

int len_a, len_b, len_c;
int DP1(int, int, int);

int DP2(int a, int b, int c){
	ll res = 0;
	
	if ( C[c] == 0 ) return 1;
	if ( A[a] == 0 && B[b] == 0 ) return 0;
	if ( vis2[a][b][c] == kase ) return dp2[a][b][c];
	
	vis2[a][b][c] = kase;
	if ( A[a] == C[c] && A[a] ) res = ( res + DP1(a + 1, b, c + 1) ) % MOD;
	if ( A[a] ) res = ( res + DP2(a + 1, b, c) ) % MOD;
	
	return dp2[a][b][c] = res;
}

int DP3(int a, int b, int c){
	ll res = 0;
	
	if ( C[c] == 0 ) return 1;
	if ( A[a] == 0 && B[b] == 0 ) return 0;
	if ( vis3[a][b][c] == kase ) return dp3[a][b][c];
	
	vis3[a][b][c] = kase;
	if ( B[b] == C[c] && B[b] ) res = ( res + DP1(a, b + 1, c + 1) ) % MOD;
	if ( B[b] ) res = ( res + DP3(a, b + 1, c) ) % MOD;
	
	return dp3[a][b][c] = res;
}

int DP1(int a, int b, int c){
	ll res = 0;
	
	if ( C[c] == 0 ) return 1;
	if ( A[a] == 0 && B[b] == 0 ) return 0;
	if ( vis1[a][b][c] == kase ) return dp[a][b][c];
	
	vis1[a][b][c] = kase;
	if ( A[a] == C[c] && A[a] ) res = ( res + DP1(a + 1, b, c + 1) ) % MOD;
	if ( A[a] ) res = ( res + DP2(a + 1, b, c) ) % MOD;
	if ( B[b] == C[c] && B[b] ) res = ( res + DP1(a, b + 1, c + 1) ) % MOD;
	if ( B[b] ) res = ( res + DP3(a, b + 1, c) ) % MOD;
	
	return dp[a][b][c] = res;
}
/*
ll DP(int idxa,int idxb,int idxc)
{      //printf("idxa:: %d idxb::%d idxc::%d\n",idxa,idxb,idxc);
       if(vis[idxa][idxb][idxc] == kase) return ways[idxa][idxb][idxc];

       if(idxc==len_c) return ways[idxa][idxb][idxc]=1;
       vis[idxa][idxb][idxc]=kase;
       ways[idxa][idxb][idxc]=0;
       int i;
       for(i=idxa;i<len_a;i++)
       {      if(len_a-i+len_b-idxb<len_c-idxc)
              break;
              if(A[i]==C[idxc])
              {
                     ways[idxa][idxb][idxc]+=DP(i+1,idxb,idxc+1);
                     ways[idxa][idxb][idxc]%=MOD;
              }
       }
         for(i=idxb;i<len_b;i++)
       {      if(len_a-idxa+len_b-i<len_c-idxc)
               break;
              if(B[i]==C[idxc])
              {
                     ways[idxa][idxb][idxc]+=DP(idxa,i+1,idxc+1);
                     ways[idxa][idxb][idxc]%=MOD;
              }
       }
       return ways[idxa][idxb][idxc];

}
*/
int main(){
	int test;
	
	while ( cin >> test ){
		for ( kase = 1 ; kase <= test ; kase++ ){
			cin>>A>>B>>C;
			printf("Case %d: ", kase);
			len_a = strlen(A), len_b = strlen(B), len_c = strlen(C);
			/*cout<<DP(0,0,0)<<endl;*/
			cout<<DP1(0,0,0)<<endl;
		}
	}
	
	return 0;
}

