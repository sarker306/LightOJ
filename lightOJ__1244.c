#include <stdio.h>
#include <string.h>
#define SIZE 3

void MatrixMultiply(long c[SIZE][SIZE], long a[SIZE][SIZE], long b[SIZE][SIZE], int size, long mod){
    int i, j, k;
    long temp[SIZE][SIZE];
    
    for ( i = 0 ; i < size ; i++ )
        for ( j = 0 ; j < size ; j++ ){
            temp[i][j] = 0;
            for ( k = 0 ; k < size ; k++ )
                temp[i][j] = ( temp[i][j] + a[i][k] * b[k][j] ) % mod;
        }
    
    for ( i = 0 ; i < size ; i++ )
        for ( j = 0 ; j < size ; j++ )
            c[i][j] = temp[i][j];
}

void BigModMatrix(long res[SIZE][SIZE], long base[SIZE][SIZE], long power, int size, long mod){
    int i, j;
    long temp[SIZE][SIZE];
    
    for ( i = 0 ; i < size ; i++ )
        for ( j = 0 ; j < size ; j++ ){
            res[i][j] = 0;
            temp[i][j] = base[i][j];
        }
    
    for ( i = 0 ; i < size ; i++ ) res[i][i] = 1;
    
    while ( power ){
        if ( power & 1 ) MatrixMultiply( res, temp, res, size, mod );
        power >>= 1;
        MatrixMultiply(temp, temp, temp, size, mod );
    }
}

/**
    Solution of this problem :
    If u[i] is the solution of configurations for 2*i rectangle
    and v[i] is the solution of configurations for 2*i rectangle with
    the corner missing, then
    v[i] = ( u[i-2] + v[i-1] ) % 10007;
    u[i] = ( u[i-1] + u[i-2] + 2*v[i-1] ) % 10007;
**
    Solution two :
        u[i] = u[i-1] + u[i-2] + 2*u[i-3] + 2*u[i-4] + ....
        u[i-1] = u[i-2] + u[i-3] + 2*u[i-4] + ...
        u[i] - u[i-1] = u[i-1] + u[i-3]
        u[i] = 2*u[i-1] + u[i-3]
*/

int main(){
    int test, kase, i;
    long base[SIZE][SIZE], res[SIZE][SIZE], arr[SIZE], ans, n;
    
    memset(base, 0, sizeof(base));
    for ( i = 1 ; i < 3 ; i++ ) base[i][i-1] = 1;
    arr[0] = 1, arr[1] = 1, arr[2] = 0;
    base[0][0] = base[0][1] = base[2][2] = 1, base[0][2] = 2;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld", &n);
            printf("Case %d: ", kase);
            if ( n > 1 ) {
                BigModMatrix(res, base, n - 1, 3, 10007);
                for ( i = ans = 0; i < 3 ; i++ )
                    ans = ( ans + arr[i] * res[0][i] ) % 10007;
                
                printf("%ld\n", ans);
            }
            
            else printf("%ld\n", arr[1-n]);
        }
    }
    
    return 0;
}
