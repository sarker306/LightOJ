#include <stdio.h>

long mod = 10007;

void MatrixMultiply(long c[4][4], long a[4][4], long b[4][4]){
    int i, j, k;
    long temp[4][4];
    
    for ( i = 0 ; i < 4 ; i++ )
        for ( j = 0 ; j < 4 ; j++ ){
            temp[i][j] = 0;
            for ( k = 0 ; k < 4 ; k++ )
                temp[i][j] = ( temp[i][j] + a[i][k] * b[k][j] ) % mod;
        }
    
    for ( i = 0 ; i < 4 ; i++ )
        for ( j = 0 ; j < 4 ; j++ )
            c[i][j] = temp[i][j];
}

void BigModMatrix(long res[4][4], long base[4][4], long power){
    int i, j;
    long temp[4][4];
    
    for ( i = 0 ; i < 4 ; i++ )
        for ( j = 0 ; j < 4 ; j++ ){
            res[i][j] = 0;
            temp[i][j] = base[i][j];
        }
    
    for ( i = 0 ; i < 4 ; i++ ) res[i][i] = 1;
    
    while ( power ){
        if ( power & 1 ) MatrixMultiply( res, temp, res );
        power >>= 1;
        MatrixMultiply(temp, temp, temp);
    }
}

int main(){
    int test, kase, i, j;
    long base[4][4], res[4][4], n;
    
    for ( i = 0 ; i < 4 ; i++ )
        for ( j = 0 ; j < 4 ; j++ )
            base[i][j] = 0;
    
    base[1][0] = base[2][1] = 1, base[3][3] = 1;
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld%ld%ld%ld", &n, &base[0][0], &base[0][2], &base[0][3]);
            if ( n > 2 ) BigModMatrix(res, base, n - 2);
            printf("Case %d: %ld\n", kase, (n < 3 ) ? 0 : res[0][3]);
        }
    }
    
    return 0;
}
