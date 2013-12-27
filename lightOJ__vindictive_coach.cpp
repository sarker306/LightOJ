#include <stdio.h>

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef long long ll;
typedef unsigned long long llu;

llu great[51][51], less[51][51];
char visg[51][51], visl[51][51];

llu L(int, int);
llu G(int x, int y){
	int k;
	if ( x == 0 && y == 1 ) return 1;
	else if ( y == 0 ) return 0;
	if ( visg[x][y] ) return great[x][y];
	
	visg[x][y] = 1;
	for ( k = 1 ; k <= y ; k++ ) great[x][y] += L(x + k - 1, y - k);
	return great[x][y];
}

llu L(int x, int y){
	int k;
	if ( x == 1 && y == 0 ) return 1;
	else if ( x == 0 ) return 0;
	if ( visl[x][y] ) return less[x][y];
	
	visl[x][y] = 1;
	for ( k = 1 ; k <= x ; k++ ) less[x][y] += G(x - k, y + k -1);
	return less[x][y];
}

int main(){
	int n, i, j, k, tst, ks;
	
	while ( scanf("%d", &tst) == 1 ){
		for ( ks = 1 ; ks <= tst ; ks++ ){
			scanf("%d%d", &n, &k);
			printf("Case %d: ", ks);
			if ( k > 1 ) printf("%llu\n", L(k-1,n-k));
			else if ( n < 3 ) printf("1\n");
			else printf("%llu\n", L(1,n-3));
		}
	}
	
	return 0;
}

