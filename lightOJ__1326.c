#include <stdio.h>
#define SIZE 1002

long arrFactorial[SIZE], arr[SIZE];
long arrStirling2[SIZE][SIZE];
long mod = 10056;

void initStirling2(){
    int i, j;
    
    arrStirling2[0][0] = 1;
    for ( i = 1 ; i < SIZE ; i++ ){
        arrStirling2[i][1] = 1;
        arrStirling2[i][i] = 1;
        for ( j = 2 ; j < i ; j++ )
            arrStirling2[i][j] = (j*arrStirling2[i-1][j] + arrStirling2[i-1][j-1]) % mod;
    }
}

void initFactorial(){
    int i;
    
    arrFactorial[0] = 1;
    for ( i = 1 ; i < SIZE ; i++ )
        arrFactorial[i] = ( i * arrFactorial[i-1] ) % mod;
}

long waysToFinishRace( int n ){
    int i;
    
    if ( arr[n] ) return arr[n];
    for ( i = 1 ; i <= n ; i++ )
        arr[n] = ( arr[n] + arrStirling2[n][i] * arrFactorial[i] ) % mod;
    
    return arr[n];
}

int main(){
    int test, kase, n;
    
    initFactorial();
    initStirling2();
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%d", &n);
            printf("Case %d: %ld\n", kase, waysToFinishRace(n));
        }
    }
    
    return 0;
}
