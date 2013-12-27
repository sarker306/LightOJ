#include <stdio.h>
#include <string.h>
#define SIZE 100005

char binaryNum[SIZE + 2];
typedef struct{
    char updated;
    long left, right;
}Pos;

Pos tree[((SIZE+2)<<2)];

void initializeTree(long index, long left, long right){
    long mid;
    
    tree[index].left = left, tree[index].right = right;
    tree[index].updated = 0;
    if ( left == right ) return;
    initializeTree( 1 + (index<<1), left, mid = (left+right)>>1);
    initializeTree( (1 + index)<<1 , mid + 1, right );
}

long x, y;

void update(long index, char updateVal){
    if ( tree[index].right < x || tree[index].left > y ) return;
    
    if ( tree[index].left >= x && tree[index].right <= y ){
        tree[index].updated ^= updateVal;
        return;
    }
    
    tree[1+(index<<1)].updated ^= tree[index].updated; /* update children */
    tree[(1+index)<<1].updated ^= tree[index].updated;
    update( 1 + (index<<1), updateVal);                /* push the updateVal further down */
    update( ( 1 + index )<<1, updateVal);
    tree[index].updated = 0;                           /* as updates have been pushed to
                                                          children, no updates for parent */
}

char query( long index, char updateVal ){
    char l, r;
    long mid = (tree[index].left + tree[index].right ) >>1;
    
    if ( tree[index].right < x || tree[index].left > y ) return 0;
    
    if ( tree[index].left == x && tree[index].right == x ){
        return binaryNum[x] ^ updateVal ^ tree[index].updated;
    }
    
    if ( x <= mid )
        return query( 1 + (index << 1), updateVal ^ tree[index].updated );
    else return query( ( 1+ index) <<1, updateVal ^ tree[index].updated );
}

int main(){
    int test, kase;
    long queries;
    char command[3];
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            printf("Case %d:\n", kase);
            scanf("%s", binaryNum + 1);
            initializeTree(0, 1, strlen(binaryNum + 1));
            scanf("%ld", &queries);
            while ( queries-- ){
                scanf("%s", command);
                if ( *command == 'Q' ){
                    scanf("%ld", &x);
                    y = x;
                    printf("%c\n", query(0, 0));
                }
                else{
                    scanf("%ld%ld", &x, &y);
                    update(0, 1);
                }
            }
        }
    }
    
    return 0;
}
