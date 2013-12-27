#include <stdio.h>

void MatrixMultiply(unsigned long long res[2][2], unsigned long long fir[2][2], unsigned long long sec[2][2]){
    unsigned long long temp[2][2];
    
    temp[0][0] = fir[0][0] * sec[0][0] + fir[0][1] * sec[1][0];
    temp[0][1] = fir[0][0] * sec[0][1] + fir[0][1] * sec[1][1];
    temp[1][0] = fir[1][0] * sec[0][0] + fir[1][1] * sec[1][0];
    temp[1][1] = fir[1][0] * sec[0][1] + fir[1][1] * sec[1][1];
    res[0][0] = temp[0][0];
    res[0][1] = temp[0][1];
    res[1][0] = temp[1][0];
    res[1][1] = temp[1][1];
}

unsigned long long CalcSumPower(long p, long q, long n){
    unsigned long long base[2][2], res[2][2], temp[2][2];
    
    if ( n == 0 ) return p;
    temp[0][0] = base[0][0] = p, temp[0][1] = base[0][1] = -q;
    temp[1][0] = base[1][0] = 1, temp[1][1] = base[1][1] = 0;
    res[0][0] = res[1][1] = 1;
    res[1][0] = res[0][1] = 0;
    
    while ( n ){
        if ( n&1 ) MatrixMultiply(res, res, temp);
        MatrixMultiply(temp, temp, temp);
        
        n >>= 1;
    }
    
    return res[0][0]*p + res[0][1]*2;
}

int main(){
    int test, kase;
    long p, q, n;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld%ld%ld", &p, &q, &n);
            
            printf("Case %d: %llu\n", kase, n ? CalcSumPower(p, q, n-1) : 2 );
        }
    }
    
    return 0;
}
