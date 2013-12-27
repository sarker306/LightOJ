#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define SIZE 100001
#define LOGSIZE 20

long A[SIZE+2];
long val[SIZE+2];
long TREE[SIZE<<2];

long leftC(long ind){ return 1 + (ind<<1); }
long rightC(long ind){ return (1 + ind)<<1; }

void initTree(long ind, long left, long right){
	long mid = (left + right)>>1, lC = leftC(ind), rC = rightC(ind);
	
	if ( left == right ){
		TREE[ind] = A[left];
		return;
	}
	
	initTree(lC, left, mid);
	initTree(rC, mid + 1, right);
	TREE[ind] = (TREE[lC] > TREE[rC])? TREE[lC] : TREE[rC];
}

long lo, hi;

long query(long ind, long left, long right){
	long mid = (left + right)>>1, lC = leftC(ind), rC = rightC(ind), lR, rR;
	
	if ( hi < left || right < lo ) return LONG_MIN;
	if ( left >= lo && right <= hi ) return TREE[ind];
	
	lR = query(lC, left, mid);
	rR = query(rC, mid + 1, right);
	return (lR > rR)? lR : rR;
}

unsigned long upperBound(long *arr, unsigned long n, long num ){
    unsigned long low = 0, high = n, mid;

    while ( low + 1 < high ) {
        mid = ( low + high ) >> 1;
        if ( arr[mid] > num ) high = mid;
        else low = mid;
    }

    return high;
}

int main(){
    long n, q, i, x, y, a, b, c;
    int test, kase;

	val[0] = INT_MIN;
    while( scanf("%ld", &test)!= EOF){
    	for ( kase = 1 ; kase <= test ; kase++ ){
    		
    		memset(pre, 0, sizeof(pre));
    		
    		b = 1;
	        scanf("%ld%ld%ld", &n, &a, &q);
	        for ( i = 1 ; i <= n ; i++ ){
				scanf("%ld", val + i);
			}
	        
	        x = INT_MIN, y = 0;
	        for ( i = 1 ; i <= n ; i++ ){
	            if ( x == val[i] ) A[i] = A[i-1] + 1, val[i] = y;
	            else{
					A[i] = 1, x = val[i];
					val[i] = ++y;
				}
	        }

	        val[i] = SIZE + 10;
	        
	        initTree(0, 1, n);
	        printf("Case %d:\n", kase);
	        while ( q-- ){
	            a = b = c = -1;
	            scanf("%ld%ld", &x, &y); /* index count from 1 to n*/
	            if ( (y - x) == (A[y] - A[x]) ) printf("%ld\n", y - x + 1);
	            else{
	                lo = upperBound(val, n + 2, val[x]);
	                hi = y - A[y];
	                a = A[lo-1] - A[x] + 1;
	                if ( lo <= hi ){
	                    b = query(0, 1, n);
	                   /* printf("RMQ = %ld  ", b);*/
	                }
	               /* printf("low = %ld, high = %ld\n", lo, hi);*/
	                c = A[y];
	                if ( c < b ) c = b;
	                if ( c < a ) c = a;
	                printf("%ld\n", c);
	            }
	        }
	    }
    }

    return 0;
}
/*
15 3 100
1 1 1 1 1 3 3 3 3 2 2 2 1 3 2
*/
