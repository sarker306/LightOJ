#include <stdio.h>
#include <string.h>
#define SIZE 100005

long long val[((SIZE+2)<<2)];
long updateVal[((SIZE+2)<<2)];

void initializeTree(long index, long left, long right){
    long mid = (left + right)>>1;
    long lc = 1 + (index<<1), rc = (1 + index)<<1;
    
    updateVal[index] = 0;
    val[index] = 0;
    
    if ( left == right ) return;
    initializeTree( lc, left, mid);
    initializeTree( rc, mid + 1, right );
}

long x, y;

void Update ( long index, long ud, long left, long right ){
    long tmp, mid = (left + right)>>1;
    long lc = (1 + (index<<1)), rc = ((1+index)<<1);
    
    /* check if previous update is pending */
    if ( updateVal[index] ){
        val[index] += ( right - left + 1 ) * updateVal[index];
    }
    
    if ( left != right ){ /* if it has children, push update value */
        updateVal[rc] = (updateVal[rc] + updateVal[index]);
        updateVal[lc] = (updateVal[lc] + updateVal[index]);
    }
    
    updateVal[index] = 0;
    /* ok, no update pending */
    
    if ( left > y || right < x ){
        return;
    }
    
    if ( left >=x && right <= y ){
        /* ud added to all value, update */
        val[index] += ( right - left + 1 ) * ud;
        
        if ( left != right ){ /* if it has children, push update value */
            updateVal[rc] = (updateVal[rc] + ud);
            updateVal[lc] = (updateVal[lc] + ud);
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
    if ( updateVal[index] ){
        val[index] += ( right - left + 1 ) * updateVal[index];
    }
    
    if ( left != right ){ /* if it has children, push update value */
        updateVal[rc] = (updateVal[rc] + updateVal[index]);
        updateVal[lc] = (updateVal[lc] + updateVal[index]);
    }
    
    updateVal[index] = 0;
    /* ok, no update is pending */
    
    if ( left > y || right < x ) return 0;
    if ( left >=x && right <= y ) return val[index];
    
    return Query( lc, left, mid ) + Query( rc, mid + 1, right );
}

int main(){
    long queries, n, ud;
    int command, test, kase;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            printf("Case %d:\n", kase);
            scanf("%ld%ld", &n, &queries);
            initializeTree(0, 0, n - 1);
            while ( queries-- ){
                scanf("%d", &command);
                if ( command == 1 ){
                    scanf("%ld%ld", &x, &y);
                    printf("%lld\n", Query(0, 0, n - 1));
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
