#include <cstdio>

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

char word[11];
int d, finalMask;

int dp2[1001][1<<10];
int vis[1001][1<<10], ks;
int checkList[10];

int rec2(int mod, int mask){
	int i;
	
	if ( mask == finalMask ) return ( mod == 0 );
	if ( vis[mod][mask] == ks ) return dp2[mod][mask];
	
	vis[mod][mask] = ks;
	dp2[mod][mask] = 0;
	for ( i = 0 ; word[i] ; i++ ){
		if ( (checkList[i] | mask) == finalMask && !( mask & (1<<i))) dp2[mod][mask] += rec2(((mod<<3)+(mod<<1) + word[i]-'0')%d, mask | (1<<i));
	}
	
	return dp2[mod][mask];
}

int main(){
	int test, i, j;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%s%d", word, &d);
			for ( finalMask = i = 0 ; word[i] ; i++ )
				finalMask |= 1<<i;

			for ( i = 0 ; word[i] ; i++ ) checkList[i] = finalMask;
			for ( i = 0 ; word[i] ; i++ )
				for ( j = 0 ; j < i ; j++ )
					if ( word[i] == word[j] ) checkList[i] &= ~(1U<<j);

			printf("Case %d: %d\n", ks, rec2(0,0));
		}
	}
	
	return 0;
}

