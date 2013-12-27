#include <stdio.h>
#define SIZE 55

int arrStirling2[SIZE][SIZE];

int stirling2(int n, int k){
    int ans = 0;
    
    if ( n >= 0 && n < SIZE && k >= 0 && k < SIZE && arrStirling2[n][k] )
        return arrStirling2[n][k];
        
    if ( n == k ) return 1;
    if ( n < k || n < 0 || k <= 0 ) return 0;
    ans = stirling2(n-1,k) * k + stirling2(n-1, k-1);
    if ( n >= 0 && n < SIZE && k >= 0 && k < SIZE )
        arrStirling2[n][k] = ans;
    
    return ans;
}

unsigned int SumOfPowers(unsigned long long n, int power){
    int i, j, x;
    unsigned long long tmp;
    unsigned int res = 0;
    
    if ( power == 0 ) return n;
    for ( j = 0 ; j <= power ; j++ ){
        for ( tmp = 1, x = j + 1, i = 0 ; i < j + 1 ; i++ ){
            if ( x > 1 && (n - i + 1) % x == 0 )
                tmp *= (n-i+1)/x, x = 1;
            else tmp *= n - i + 1;
        }
        
        /*printf("%d %d %llu %llu\n", power, j, tmp, stirling2(power,j));*/
        res += tmp * stirling2(power, j);
    }
    
    return res;
}

int main(){
    int test, kase, k;
    unsigned long long n, ans;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%llu%d", &n, &k);
            printf("Case %d: %lu\n", kase, SumOfPowers(n, k) );
        }
    }
    
    return 0;
}
