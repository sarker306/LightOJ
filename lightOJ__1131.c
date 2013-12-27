#include <stdio.h>
#include <string.h>
#define SIZE 7

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

int main(){
    int test, kase, i, j, query;
    long res[SIZE][SIZE], base[SIZE][SIZE], arr[SIZE];
    long M, N, ans1, ans2;
    
    while ( scanf("%d", &test) != EOF ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            memset(base, 0, sizeof(base));
            for ( i = 1 ; i < 6 ; i++ ) base[i][i-1] = 1;
            for ( j = 0 ; j < 6 ; j += 3 )
                scanf("%ld%ld%ld", &base[j][j], &base[j][j+1], &base[j][(j+5)%6]);
            
            for ( j = 2 ; j >= 0 ; j-- ) scanf("%ld", &arr[j]);
            for ( j = 5 ; j >= 3 ; j-- ) scanf("%ld", &arr[j]);
            scanf("%ld", &M);
            
            for ( i = 0 ; i < 6 ; i++ ){
                for ( j = 0 ; j < 6 ; j++ ){
                    if ( base[i][j] == 0 || base[i][j] == 1 ) continue;
                    base[i][j] %= M;
                    if ( base[i][j] < 0 ) base[i][j] += M;
                }
                
                arr[i] %= M;
                if ( arr[i] < 0 ) arr[i] += M;
            }
            
            scanf("%d", &query);
            printf("Case %d:\n", kase);
            while ( query-- ){
                scanf("%ld", &N);
                memset(res, 0, sizeof(res));
                if ( N > 1 ){
                    BigModMatrix( res, base, N - 2, 6, M );
                    
                    for ( ans1 =  i = 0 ; i < 6 ; i++ )
                        ans1 = ( ans1 + arr[i] * res[0][i] ) % M;
                    for ( ans2 =  i = 0 ; i < 6 ; i++ )
                        ans2 = ( ans2 + arr[i] * res[3][i] ) % M;
                        
                    printf("%ld %ld\n", ans1, ans2);
                }
                else printf("%ld %ld\n", arr[2-N], arr[5-N]);
            }
        }
    }
    
    return 0;
}
