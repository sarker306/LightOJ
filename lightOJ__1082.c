#include <stdio.h>
#define SIZE 1000005
#define TREESIZE 1<<18
#define NOTFOUND 9999

long array[SIZE];
typedef struct{
    long left, right, val;
}node;

node tree[SIZE<<1];

long leftChild(long index) { return (index<<1) + 1; }
long rightChild(long index) { return (index+1)<<1; }
long minimumValue(long *arr, long x, long y){
    if ( x == NOTFOUND ) return y;
    else if ( y == NOTFOUND ) return x;
    else return arr[x] > arr[y] ? y : x;
}

long initializeTree(long index, long *arr, node *tree, long start, long end){
    long mid, l, r;
    
    tree[index].left = start, tree[index].right = end;
    if ( start == end ) return tree[index].val = start;
    mid = (start + end)>>1;
    l = initializeTree( leftChild(index), arr, tree, start, mid );
    r = initializeTree( rightChild(index), arr, tree, mid + 1, end);
    return tree[index].val = minimumValue( arr, l, r );
}

long query(long index, long *arr, node *tree, long start, long end){
    long l, r;
    
    if ( tree[index].left > end || tree[index].right < start ) return NOTFOUND;
    if ( tree[index].left >= start && tree[index].right <= end ) return tree[index].val;
    l = query( leftChild(index), arr, tree, start, end);
    r = query ( rightChild(index), arr, tree, start, end);
    return minimumValue(arr, l, r);
}

int main(){
    long i, n, q, x, y;
    int test, kase;
    
    scanf ("%d", &test);
    for ( kase = 1 ; kase <= test ; kase++ ){
        scanf("%ld%ld", &n, &q);
        for ( i = 0 ; i < n ; i++ ) scanf("%ld", &array[i]);
        initializeTree(0, array, tree, 0, n-1);
        printf("Case %d:\n", kase);
        while ( q-- ){
            scanf("%ld%ld", &x, &y);
            if ( x > y ) x ^= y ^= x ^= y;
            x--, y--;
            printf("%ld\n", array[query(0, array, tree, x, y)]);
        }
    }
    
    return 0;
}
