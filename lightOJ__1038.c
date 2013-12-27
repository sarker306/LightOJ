#include <stdio.h>
#include <math.h>
#define SIZE 100005

double probab[SIZE];

double calcProbability( long n ){
    long i, countFactor = 2;
    double res = 0;
    
    if ( n == 1 ) return 0;
    if ( probab[n] ) return probab[n];
    
    for ( i = 2 ; i * i < n ; i++ ){
        if ( n % i == 0 ){
            res += calcProbability( i ) + calcProbability( n / i );
            countFactor += 2;
        }
    }
    
    if ( i * i == n ) res += calcProbability(i), countFactor++;
    return probab[n] = ( countFactor + res ) / ( countFactor - 1 );
}

int main(){
    int test, kase;
    long n;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld", &n);
            printf("Case %d: %.10lf\n", kase, calcProbability(n));
        }
    }
    
    return 0;
}
