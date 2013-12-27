#include <stdio.h>
#include <math.h>
#define SIZE 100005

double power( double base, long long n ){
    double res;
    if ( n == 0 ) return 1;
    
    res = power(base, n>>1);
    res *= res;
    if ( n & 1 ) res *= base;
    return res;
}

double exactBDayParadox(long n, long long p){
    long i;
    double res = 1;

	for ( i = 1 ; i <= p ; i++ ) res *= (( n - i + 1 ) *1.0) / n;
    return 1 - res;
}

double funcBDayParadox( long n, long long p ){
    long long pC2 = p;
    long i;
    double res = 1;
    
	pC2 *= p - 1;
	pC2 >>= 1;
	
    return 1 - power(1 - 1.0/n, pC2);
}

long cache[SIZE];

long f( long n ){
    double res = 0;
    long low = 0, mid, high = n + 1;
    if ( cache[n] ) return cache[n];
    
    while ( low + 1 < high ){
        mid = ( low + high ) >> 1;
        /*printf("low %d high %ld mid %ld...... res previously %lf\n", low, high, mid, res);
        getchar();*/
        if ( (res = funcBDayParadox(n, mid)) < 0.5 ) low = mid;
        else high = mid;
    }
    /*printf("res now %lf, func(%ld) = %lf\n", res, mid + 1, funcBDayParadox(n, mid + 1));*/
    
    while ( exactBDayParadox(n, low) >= 0.5 ) low--;
    return cache[n] = low;
}

int main(){
    long n;
    int test, kase;
    double res;
    
    cache[1] = 1, cache[2] = 1;
    /*for ( n = 1 ; n <= 100000 ; n++ ){
        res = funcBDayParadox(n, f(n));
        if ( res < 0.5 ) printf("%ld %ld\n", n, f(n));
    }*/
    
    while ( scanf("%d", &test ) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld", &n);
            /*n = 100000 - kase;*/
            printf("Case %d: %ld\n", kase, f(n));
        }
    }
    
    return 0;
}

