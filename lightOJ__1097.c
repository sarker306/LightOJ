#include <stdio.h>
#define MAXN 2097153

int tree[MAXN + 1];
int nums[100001];

int cnt;
void add(int *a, int ind, int x){
    while ( ind < MAXN ) {
        a[ind] += x;
        ind += ind & -ind;
    }
}

int sum(int *a, int ind){
    register int sm = 0;
    
    while ( ind ) {
        sm += a[ind];
        ind -= ind & -ind;
    }
    
    return sm;
}

int findG(int cumFre){
    int idx = 0, tIdx;
    int bitMask = 1<<20;
    
    while ((bitMask != 0) && (idx < MAXN)){
        tIdx = idx + bitMask;
        if (cumFre >= tree[tIdx]){ 
            idx = tIdx;
            cumFre -= tree[tIdx];
        }
        
        bitMask >>= 1;
    }
    
    return idx;
}

int binarySearch(int xxx){
    return findG(xxx - 1) + 1;
}

int main(){
    int i, x, n, command, l, r, q, xxx, y;
    
    for ( i = 1 ; i < MAXN ; i+=2 ) add( tree, i, 1 );
    
    nums[1] = 1;
    q = 100000;
    for ( i = 2; i <= q ; i++ ){
        y = binarySearch(i);
        nums[i] = y;
        xxx = y;
        while ( sum(tree, MAXN-1) >= xxx ){
            cnt++;
            x = binarySearch(xxx);
            add( tree, x, -1 );
            xxx--;
            xxx += y;
        }
    }
    
    scanf("%d", &command);
    for ( y = 1 ; y <= command ; y++ ){
        scanf("%d", &n);
        printf("Case %d: %d\n", y, nums[n]);
    }
    
    return 0;
}
