#include <cstdio>
#include <cstdlib>

#define SIZE 55

unsigned int combination[SIZE][SIZE];

unsigned int nCk( int n, int k ){
    unsigned int ans;
    
    if ( n >= 0 && n < SIZE && k >= 0 && k < SIZE && combination[n][k] ) return combination[n][k];
    if ( k > n ) return 0;
    if ( k == 0 ) return combination[n][k] = 1;
    else ans = nCk( n - 1, k - 1 ) + nCk ( n - 1, k );
    if ( n >= 0 && n < SIZE && k >= 0 && k < SIZE )
        combination[n][k] = ans;
    
    return ans;
}

void MatrixMultiply(unsigned int c[SIZE][SIZE], unsigned int a[SIZE][SIZE], unsigned int b[SIZE][SIZE], int size){
    int i, j, k;
    unsigned int temp[SIZE][SIZE];
    
    for ( i = 0 ; i < size ; i++ )
        for ( j = 0 ; j < size ; j++ ){
            temp[i][j] = 0;
            for ( k = 0 ; k < size ; k++ )
                temp[i][j] += a[i][k] * b[k][j];
        }
    
    for ( i = 0 ; i < size ; i++ )
        for ( j = 0 ; j < size ; j++ )
            c[i][j] = temp[i][j];
}

void BigModMatrix(unsigned int res[SIZE][SIZE], unsigned int base[SIZE][SIZE], unsigned long long power, int size){
    int i, j;
    unsigned int temp[SIZE][SIZE];
    
    for ( i = 0 ; i < size ; i++ )
        for ( j = 0 ; j < size ; j++ ){
            res[i][j] = 0;
            temp[i][j] = base[i][j];
        }
    
    for ( i = 0 ; i < size ; i++ ) res[i][i] = 1;
    
    while ( power ){
        if ( power & 1 ) MatrixMultiply( res, temp, res, size );
        power >>= 1;
        MatrixMultiply(temp, temp, temp, size);
    }
}

unsigned int Sum( unsigned long long n, int k){
    unsigned int base[SIZE][SIZE], res[SIZE][SIZE];
    
    for ( int i = 1 ; i <= k + 1 ; i++ ){
        for ( int j = 0 ; j < i ; j++ ) base[i][j] = 0;
        for ( int j = i ; j <= k + 1 ; j++ ){
            base[i][j] = nCk(k - i + 1, j - i );
        }
    }
    
    for ( int j = 1 ; j <= k + 1 ; j++ ) base[0][j] = base[1][j];
    base[0][0] = 1;
    /*
    for ( int i = 0 ; i <= k + 1 ; i++ ){
        for ( int j = 0 ; j <= k + 1 ; j++ ) printf("%5u ", base[i][j]);
        puts("");
    }*/
    
    BigModMatrix(res, base, n, k+2);
    /*for ( int i = 0 ; i <= k + 1 ; i++ ){
        for ( int j = 0 ; j <= k + 1 ; j++ ) printf("%5u ", res[i][j]);
        puts("");
    }*/
    
    return res[0][k+1];
}

int main(){
    unsigned long long n;
    int kase, test, k;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%llu%d", &n, &k);
            printf("Case %d: %lu\n", kase, Sum(n,k));
        }
    }
    
    return 0;
}
