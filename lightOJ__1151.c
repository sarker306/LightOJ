#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 101
double EPS = 1e-10;

double Abs(double val){
    return (val < 0 ) ? -val : val;
}
/*
void initializeMatrix(double coeff[SIZE][SIZE+1], int snake[SIZE+1]){
    int i, j;
    
    for ( i = 1 ; i < 100 ; i++ ){
        if ( snake[i] ) continue;
        coeff[i][i] += 1;
        for ( j = 1 ; j <= 6 ; j++ ){
            coeff[i][101] += 1.0/6.0;
            if ( i + j < SIZE ) coeff[i][i+j] -= 1.0/6.0;
            else coeff[i][i] -= 1.0/6.0;
        }
    }
    
    coeff[100][100] += 1.0;
}
*/

void initializeMatrix(double coeff[SIZE][SIZE+1], double B[], int snake[SIZE+1]){
    int i, j;
    
    for ( i = 0 ; i < 100 ; i++ ){
        if ( snake[i] ) continue;
        coeff[i][i] += 1;
        for ( j = 1 ; j <= 6 ; j++ ){
            B[i] += 1.0/6.0;
            if ( i + j < SIZE ) coeff[i][i+j] -= 1.0/6.0;
            else coeff[i][i] -= 1.0/6.0;
        }
    }
    
    coeff[100][100] += 1.0;
}

void LUP_Decomp( double A[SIZE][SIZE+1], int pi[SIZE], int n ){
	int i, j, k, k1;
	double p, absol;

	for( i = 0 ; i < n ; i++ )  pi[i]=i;

	for( k = 0 ; k < n ; k++ ){
		p = 0;
		for ( i = k , k1 = i ; i < n ; i++ ){
			absol = A[i][k];
			if(absol < 0) absol = -absol;
			if(absol > p) p = absol, k1 = i;
		}

		if(k != k1) pi[k] ^= pi[k1] ^= pi[k] ^= pi[k1];

		for(i = 0 ; i < n ; i++ ){
			p = A[k][i];
			A[k][i] = A[k1][i];
			A[k1][i] = p;
		}

		for(i = k + 1 ; i < n ; i++ ){
			A[i][k] = A[i][k] / A[k][k];

			for(j = k + 1 ; j < n ; j++ ) A[i][j] = A[i][j] - A[i][k] * A[k][j];
		}
	}
}

void LUP_Solve(double A[SIZE][SIZE+1], double B[SIZE], int n ){
	int i, j;
	double y[SIZE], x[SIZE];
	int pi[SIZE];

	LUP_Decomp(A, pi, n);

	for(i = 0 ; i < n ; i++ ){
		y[i]=0;

		for(j=0;j<i;j++) y[i]=y[i]+A[i][j]*y[j];
		y[i]=B[pi[i]]-y[i];
    }
    
	for(i=n-1;i+1;i--){
		x[i]=0;

		for(j=i+1;j<n;j++) x[i]=x[i]+A[i][j]*x[j];
		x[i]=(y[i]-x[i])/A[i][i];
	}
	
	printf("%.10lf\n", x[1]);
}

void GaussianElimination(double coeff[SIZE][SIZE+1]){
    int i, j, k, k1;
    double p, temp, sum;
    double x[SIZE];
    
    for ( k = 1 ; k < 101 ; k++ ){
        p = 0, k1 = k;
        for ( i = k ; i < 101 ; i++ ){
            temp = Abs(coeff[i][k]);
            if ( p < temp )
                p = temp, k1 = i;
        }
        
        if ( Abs(p) < EPS ) exit(2);
        if ( k1 != k ){
            for ( i = 0 ; i <= 101 ; i++ ){
                temp = coeff[k][i];
                coeff[k][i] = coeff[k1][i];
                coeff[k1][i] = temp;
            }
        }
        
        for ( i = k + 1 ; i < 101 ; i++ ){
            if ( Abs(coeff[i][k]) < EPS ) continue;
            for ( j = k+1 ; j <= 101 ; j++ )
                coeff[i][j] = coeff[k][j] - coeff[i][j] / coeff[i][k] * coeff[k][k];
            
            coeff[i][k] = 0.0;
        }
    }
    
    for ( i = 101 - 1 ; i ; i-- ){
        sum = 0;
        for ( j = i+1 ; j < 101 ; j++ ) sum += coeff[i][j] * x[j];
        x[i] = (coeff[i][101] - sum) / coeff[i][i];
    }
    
    printf("%.10lf\n", x[1]);
}

int main(){
    int test, kase, jumps, i;
    int snake[101], x, y;
    double coeff[SIZE][SIZE+1], B[SIZE];
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            for ( i = 0 ; i <= 100 ; i++ )
                for ( B[i] = snake[i] = 0, x = 0 ; x <= 101 ; x++ )
                    coeff[i][x] = 0;
            scanf("%d", &jumps);
            for ( i = 0 ; i < jumps ; i++ ){
                scanf("%d%d", &x, &y);
                snake[x] = 1;
                coeff[x][y] -= 1.0, coeff[x][x] += 1.0;
            }
            
            printf("Case %d: ", kase);
            initializeMatrix(coeff, B, snake);
            /*GaussianElimination(coeff);*/
            LUP_Solve(coeff, B, 100);
        }
    }

    return 0;
}
