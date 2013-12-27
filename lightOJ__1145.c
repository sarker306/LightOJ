#include <stdio.h>
#include <string.h>

typedef long long ll;
ll Sum[15005], Dp[15005];

int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a < b ? b : a; }

int main(){
    int test, i, j, lim, ks, N, K, S;
    ll mod = 100000007;

    while ( scanf("%d", &test) == 1 ){
        for ( ks = 1 ; ks <= test ; ks++ ){
            scanf("%d%d%d", &N, &K, &S);

            Sum[0] = Dp[0] = 0;
            for ( i = 1 ; i <= K ; i++ ) Dp[i] = 1;
            for ( i = K + 1 ; i <= S ; i++ ) Dp[i] = 0;
            for ( i = 1 ; i <= S ; i++ ) Sum[i] = Sum[i-1] + Dp[i];

            for ( i = 2 ; i <= N ; i++ ){
                lim = min(i*K, S);
                
                Dp[i-1] = 0;
                for ( j = S ; j >= i ; j-- ){
                    Dp[j] = Sum[j-1] - Sum[max(j-K-1, 0)];
                    Dp[j] %= mod;
                    if ( Dp[j] < 0 ) Dp[j] += mod;
                }

                Sum[i-1] = 0;
                for ( j = i ; j <= S ; j++ ){
                    Sum[j] = Sum[j-1] + Dp[j];
                    Sum[j] %= mod;
                }
            }

            printf("Case %d: %lld\n", ks, Dp[S]);
        }
    }

    return 0;
}

