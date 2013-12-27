#include <stdio.h>
#define SIZE 100005

long arr[SIZE], modulo[SIZE];

int main(){
    int test, kase;
    long ans, n, m, i;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld%ld", &n, &m);
            
            ans = 0;
            for ( i = 0 ; i < m ; i++ ) modulo[i] = 0;
            for ( i = 0 ; i < n ; i++ ) scanf("%ld", &arr[i]);
            
            arr[0] %= m;
            modulo[arr[0]]++;
            if ( arr[0] == 0 ) ans++;
            
            for ( i = 1 ; i < n ; i++ ){
                arr[i] = ( arr[i-1] + arr[i] ) % m;
                if ( modulo[arr[i]] ) ans += modulo[arr[i]];
                if ( arr[i] == 0 ) ans++;
                modulo[arr[i]]++;
            }
            
            printf("Case %d: %ld\n", kase, ans);
        }
    }

    return 0;
}
