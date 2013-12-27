#include <stdio.h>
#define SIZE 55

void MatrixAdd(unsigned int c[SIZE][SIZE], unsigned int a[SIZE][SIZE], unsigned int b[SIZE][SIZE], int size ){
    int i, j;
    unsigned int tmp[SIZE][SIZE];
    
    for ( i = 0 ; i < size ; i++ )
        for ( j = 0 ; j < size ; j++ ){
            tmp[i][j] = a[i][j] + b[i][j];
            if ( tmp[i][j] >= 10 ) tmp[i][j] -= 10;
        }
    
    for ( i = 0 ; i < size ; i++ )
        for ( j = 0 ; j < size ; j++ )
            c[i][j] = tmp[i][j];
}

void MatrixCopy(unsigned int c[SIZE][SIZE], unsigned int a[SIZE][SIZE], int size ){
    int i, j;
    
    for ( i = 0 ; i < size ; i++ )
        for ( j = 0 ; j < size ; j++ )
            c[i][j] = a[i][j];
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
            c[i][j] = temp[i][j] % 10;
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

void input(unsigned int array[SIZE][SIZE], int size){
    int i, j;
    
    for ( i = 0 ; i < size ; i++ )
        for ( j = 0 ; j < size ; j++ ){
            scanf("%lu", &array[i][j]);
            array[i][j] %= 10;
        }
}

void output(unsigned int array[SIZE][SIZE], int size){
    int i, j;
    
    for ( i = 0 ; i < size ; i++ ){
        for ( j = 0 ; j < size ; j++ )
            putchar(array[i][j] + '0');
        
        puts("");
    }
}

void EvaluateMatrixPowerSeries( unsigned int res[SIZE][SIZE], unsigned int base[SIZE][SIZE], unsigned long long power, int size ){
    unsigned int tmp[SIZE][SIZE], temp2[SIZE][SIZE];
    int i, j;
    if ( power == 1 ){
        for ( i = 0 ; i < size ; i++ )
            for ( j = 0 ; j < size ; j++ )
                res[i][j] = base[i][j];
        return;
    }
    
    BigModMatrix(tmp, base, (power+1)>>1, size);
    
    if ( power & 1 ){
        MatrixCopy(res, tmp, size);
        for ( i = 0 ; i < size ; i++ ){
            tmp[i][i] = tmp[i][i] + 1;
            if ( tmp[i][i] >= 10 ) tmp[i][i] -= 10;
        }
        
        EvaluateMatrixPowerSeries(temp2, base, power>>1, size);
        MatrixMultiply(temp2, tmp, temp2, size);
        MatrixAdd(res, temp2, res, size);
    }
    else{
        for ( i = 0 ; i < size ; i++ ){
            tmp[i][i] = tmp[i][i] + 1;
            if ( tmp[i][i] >= 10 ) tmp[i][i] -= 10;
        }
        
        EvaluateMatrixPowerSeries(temp2, base, power>>1, size);
        MatrixMultiply(res, tmp, temp2, size);
    }
}

int main(){
    int n, k, test, kase;
    unsigned int base[SIZE][SIZE], res[SIZE][SIZE], arr[SIZE];
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%d%d", &n, &k);
            input(base, n);
            EvaluateMatrixPowerSeries(res, base, k, n);
            printf("Case %d:\n", kase);
            output(res, n);
        }
    }
    
    return 0;
}
