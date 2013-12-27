#include <stdio.h>
#include <string.h>
#define SIZE 100005

long long val[((SIZE+2)<<2)];
long updateVal[((SIZE+2)<<2)];
char toUpdate[((SIZE+2)<<2)];

void initializeTree(long index, long left, long right){
    long mid = (left + right)>>1;
    long lc = 1 + (index<<1), rc = (1 + index)<<1;
    
    updateVal[index] = 0;
    val[index] = 0;
    toUpdate[index] = 0;
    
    if ( left == right ) return;
    initializeTree( lc, left, mid);
    initializeTree( rc, mid + 1, right );
}

long x, y;

void Update ( long index, long ud, long left, long right ){
    long tmp, mid = (left + right)>>1;
    long lc = (1 + (index<<1)), rc = ((1+index)<<1);
    
    /* if previous update is pending */
    if ( toUpdate[index] ){
        val[index] = ( right - left + 1 ) * updateVal[index];
        
        if ( left != right ){ /* if it has children, push update value */
            toUpdate[rc] = toUpdate[lc] = 1;
            updateVal[rc] = updateVal[index];
            updateVal[lc] = updateVal[index];
        }
        
        toUpdate[index] = 0;
    }
    
    /* ok, no update pending */
    
    if ( left > y || right < x ){
        return;
    }
    
    if ( left >=x && right <= y ){
        /* all value set to ud, update */
        val[index] = ( right - left + 1 ) * ud;
        
        if ( left != right ){ /* if it has children, push update value */
            updateVal[rc] = ud;
            updateVal[lc] = ud;
            toUpdate[rc] = toUpdate[lc] = 1;
        }
        
        return;
    }
    
    Update( lc , ud, left, mid );
    Update( rc , ud, mid + 1, right );
    
    val[index] = val[lc] + val[rc];
}

long long Query ( long index, long left, long right ){
    long tmp, mid = (left + right)>>1;
    long lc = 1 + (index<<1), rc = (1+index)<<1;
    
    /* check if previous update is pending */
    if ( toUpdate[index] ){
        val[index] = ( right - left + 1 ) * updateVal[index];
        
        if ( left != right ){ /* if it has children, push update value */
            updateVal[rc] = updateVal[index];
            updateVal[lc] = updateVal[index];
            toUpdate[rc] = toUpdate[lc] = 1;
        }
    
        toUpdate[index] = 0;
    }
    /* ok, no update is pending */
    
    if ( left > y || right < x ) return 0;
    if ( left >=x && right <= y ) return val[index];
    
    return Query( lc, left, mid ) + Query( rc, mid + 1, right );
}

long long gcd( long long m, long n ){
    long long tmp;
    
    if ( m < 0 ) m = -m;
    if ( n < 0 ) n = -n;
    while ( n ){
        tmp = m;
        m = n;
        n = tmp%n;
    }
    
    return m;
}

int main(){
    long queries, n, ud;
    int command, test, kase;
    long long tmp;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            printf("Case %d:\n", kase);
            scanf("%ld%ld", &n, &queries);
            initializeTree(0, 0, n - 1);
            while ( queries-- ){
                scanf("%d", &command);
                if ( command == 2 ){
                    scanf("%ld%ld", &x, &y);
                    tmp = Query(0, 0, n - 1);
                    y -= x - 1;
                    ud = gcd(tmp, (long long)(y));
                    if ( ud == y )
                        printf("%lld\n", tmp / ud );
                    else printf("%lld/%ld\n", tmp/ud, y/ud);
                }
                else{
                    scanf("%ld%ld%ld", &x, &y, &ud);
                    Update(0, ud, 0, n - 1);
                }
            }
        }
    }
    
    return 0;
}
