#include <stdio.h>

long zeroFactorial( long long n ){
	long res = 0, temp = 1;
	
	for ( ; temp ; n = temp ){
		temp = n / 5;
		res += temp;
	}
	
	return res;
}

long bisection( long x ){
	long low = 0, high = 1000000000, mid;
	long fl = zeroFactorial(low), fh = zeroFactorial(high), fm;
	
	while ( low + 1 < high ){
		mid = ( low + high ) >> 1;
		fm = zeroFactorial(mid);
		if ( fm >= x ) high = mid;
		else low = mid;
	}
	
	low++;
	if ( zeroFactorial(low) != x ) return -1;
	return low;
}
	
int main(){
	long n;
	int test, kase;
	
	while( scanf("%d", &test) == 1 ){
		for ( kase = 1 ; kase <= test ; kase++ ){
			scanf("%ld", &n);
			printf("Case %d: ", kase);
			n = bisection(n);
			if ( n < 0 ) puts("impossible");
			else printf("%ld\n", n);
		}
	}
	
	return 0;
}

