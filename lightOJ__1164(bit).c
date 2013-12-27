#include <stdio.h>
#include <string.h>
#define MAXN 100005

long n;
long long tree[MAXN+1];
long long X[MAXN + 1];

/*
add x over [a...b] => add(a, x), add(b+1, -x), sum(l) returns actual value of lth index.
sum over [a...b] =>
    Now, consider Sum(0..p) for all possible p
 
    1. 0 <= p <  a : 0                  : 0 * p - 0
    2. a <= p <= b : v * ( p - (a-1) )  : v * p - v * ( a - 1 )
    3. b <  p <  n : v * ( b - (a-1) )  : 0 * p - v * b + v * ( a - 1 )
*/
void add(long long *a, long ind, long x){
    while ( ind <= n ) {
        a[ind] += x;
        ind += ind & -ind;
    }
}

long long sum(long long *a, long ind){
    long long sm = 0;
    
    while ( ind ) {
        sm += a[ind];
        ind -= ind & -ind;
    }
    
    return sm;
}

int main(){
    int command, test, kase;
    long x, l, r, q;
    /* range update and range sum query */
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            printf("Case %d:\n", kase);
            
            scanf("%ld%ld", &n, &q);
            for ( l = 0 ; l <= n ; l++ ) tree[l] = X[l] = 0;
            while ( q-- ){
                scanf("%d", &command);
                if ( command == 0 ){
                    scanf("%ld%ld%ld", &l, &r, &x);
                    l++, r++;
                    add(tree, l, x);
                    add(tree, r + 1, -x);
                    add(X, l, x * ( l - 1));
                    add(X, r + 1, -x * r );
                }
                else if ( command == 1 ){
                    scanf("%ld%ld", &l, &r);
                    r++;
                    /*printf("Element at %d = %d\n", l, sum(tree, l));*/
                    printf("%lld\n", (r * sum(tree, r) - sum(X, r)) - (l * sum(tree, l) - sum(X, l)));
                }
            }
        }
    }
    
    return 0;
}
