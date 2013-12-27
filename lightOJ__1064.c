#include <stdio.h>

typedef long long ll;
typedef unsigned long long llu;

llu F[25][150], f[25][150];
llu arr[25];

void init(){
	int i, j;
	
	f[0][0] = 1;
	for ( i = 0 ; i < 150 ; i++ ) F[0][i] = 1;
	for ( i = 1 ; i < 7 ; i++ ) f[1][i] = 1;
	for ( i = 1 ; i < 150 ; i++ ) F[1][i] = F[1][i-1] + f[1][i];

	for ( i = 2 ; i < 25 ; i++ ){
		for ( j = i ; j < 150 ; j++ ){
			f[i][j] = F[i-1][j-1];
			if ( j >= 7 ) f[i][j] -= F[i-1][j-7];
			F[i][j] = F[i][j-1] + f[i][j];
		}
	}
	
	arr[0] = 1;
	for ( i = 1 ; i < 25 ; i++ ) arr[i] = arr[i-1] * 6;
}

llu gcd(llu m, llu n){
	llu temp;
	
	if ( m == n ) return m;
	if ( m < n ) m ^= n ^= m ^= n;
	
	while ( n ){
		temp = m;
		m = n;
		n = temp % n;
	}
	
	return m;
}

int main(){
	int test, ks, n, x;
	llu a, b, c = 1;
	
	init();
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &n, &x);
			a = F[n][149];
			if ( x ) a -= F[n][x-1];
			b = arr[n];
			c = gcd(a, b);
			a /= c, b /= c;
			printf("Case %d: %llu", ks, a);
			if ( b > 1 ) printf("/%llu", b);
			puts("");
		}
	}
	
	return 0;
}

