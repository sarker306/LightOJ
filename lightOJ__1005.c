#include <stdio.h>

unsigned long long combination[32][32];
unsigned long long factorial[32];
void initComb(){
    int i, j;
    
    for ( factorial[0] = i = 1 ; i < 32 ; i++ )
        factorial[i] = i * factorial[i-1];
        
    for ( i = 0 ; i < 32 ; i++ )
        combination[i][0] = combination[i][i] = 1;
    
    for ( i = 1 ; i < 32 ; i++ )
        for ( j = 1 ; j < i ; j++ )
            combination[i][j] = combination[i-1][j] + combination[i-1][j-1];
}

int main(){
    int test, kase, k, n;
    
    initComb();
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%d%d", &n, &k);
            printf("Case %d: ", kase);
            if ( k > n ) puts("0");
            else printf("%llu\n", combination[n][k] * combination[n][k] * factorial[k] );
        }
    }
    
    return 0;
}
