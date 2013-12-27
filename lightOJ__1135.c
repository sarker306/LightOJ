#include <stdio.h>
#include <string.h>
#define SIZE 100005

long val[((SIZE+2)<<2)][3];
char updateVal[((SIZE+2)<<2)];

void initializeTree(long index, long left, long right){
    long mid = (left + right)>>1;
    long lc = 1 + (index<<1), rc = (1 + index)<<1;
    
    updateVal[index] = 0;
    val[index][1] = val[index][2] = 0;
    val[index][0] = right - left + 1;
    
    if ( left == right ) return;
    initializeTree( lc, left, mid);
    initializeTree( rc, mid + 1, right );
}

long x, y;

void Update ( long index, char ud, long left, long right ){
    long tmp, mid = (left + right)>>1;
    long lc = (1 + (index<<1)), rc = ((1+index)<<1);
    
    /* check if previous update is pending */
    if ( updateVal[index] == 1 ){
        tmp = val[index][0];
        val[index][0] = val[index][2];
        val[index][2] = val[index][1];
        val[index][1] = tmp;
    }
    else if ( updateVal[index] == 2 ){
        tmp = val[index][0];
        val[index][0] = val[index][1];
        val[index][1] = val[index][2];
        val[index][2] = tmp;
    }
    
    if ( left != right ){ /* if it has children, push update value */
        updateVal[rc] = (updateVal[rc] + updateVal[index]);
        updateVal[lc] = (updateVal[lc] + updateVal[index]);
        if ( updateVal[rc] >= 3 ) updateVal[rc] -= 3;
        if ( updateVal[lc] >= 3 ) updateVal[lc] -= 3;
    }
    
    updateVal[index] = 0;
    /* ok, no update pending */
    
    if ( left > y || right < x ){
        return;
    }
    
    if ( left >=x && right <= y ){
        /* 1 incremented, update */
	    tmp = val[index][0];
	    val[index][0] = val[index][2];
	    val[index][2] = val[index][1];
	    val[index][1] = tmp;
        
        if ( left != right ){ /* if it has children, push update value */
            updateVal[rc] = (updateVal[rc] + ud);
            updateVal[lc] = (updateVal[lc] + ud);
            if ( updateVal[rc] >= 3 ) updateVal[rc] -= 3;
            if ( updateVal[lc] >= 3 ) updateVal[lc] -= 3;
        }
        
        return;
    }
    
    Update( lc , ud, left, mid );
    Update( rc , ud, mid + 1, right );
    
    for ( tmp = 0 ; tmp < 3 ; tmp++ ){
        val[index][tmp] = val[lc][tmp] + val[rc][tmp];
    }
}

long Query ( long index, long left, long right ){
    long tmp, mid = (left + right)>>1;
    long lc = 1 + (index<<1), rc = (1+index)<<1;
    
    /* check if previous update is pending */
    if ( updateVal[index] == 1 ){
        tmp = val[index][0];
        val[index][0] = val[index][2];
        val[index][2] = val[index][1];
        val[index][1] = tmp;
    }
    else if ( updateVal[index] == 2 ){
        tmp = val[index][0];
        val[index][0] = val[index][1];
        val[index][1] = val[index][2];
        val[index][2] = tmp;
    }
    
    if ( left != right ){ /* if it has children, push update value */
        updateVal[rc] = (updateVal[rc] + updateVal[index]);
        updateVal[lc] = (updateVal[lc] + updateVal[index]);
        if ( updateVal[rc] >= 3 ) updateVal[rc] -= 3;
        if ( updateVal[lc] >= 3 ) updateVal[lc] -= 3;
    }
    
    updateVal[index] = 0;
    /* ok, no update is pending */
    
    if ( left > y || right < x ) return 0;
    if ( left >=x && right <= y ) return val[index][0];
    
    return Query( lc, left, mid ) + Query( rc, mid + 1, right );
}

int main(){
    long queries, n;
    int command, test, kase;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            printf("Case %d:\n", kase);
            scanf("%ld%ld", &n, &queries);
            initializeTree(0, 0, n - 1);
            while ( queries-- ){
                scanf("%d%ld%ld", &command, &x, &y);
                if ( command == 1 ) printf("%ld\n", Query(0, 0, n - 1));
                else Update(0, 1, 0, n - 1);
            }
        }
    }
    
    return 0;
}
