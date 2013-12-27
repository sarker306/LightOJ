#include <stdio.h>
#define VERTEX 10001
#define EDGE 40002

int edges[EDGE][2];
unsigned edgeCnt, vertices, cntArt;
int leftChild[VERTEX], rightSibling[EDGE];
int low[VERTEX], start[VERTEX], parent[VERTEX], time;
char color[VERTEX];
enum { WHITE, GRAY, BLACK };

void dfs(unsigned u){
    unsigned v, i, cntChildren = 0;
    char flag = 1;
    
    color[u] = GRAY;
    start[u] = low[u] = ++time;
    for ( i = leftChild[u] ; i != -1 ; i = rightSibling[i] ){
        v = edges[i][1];
        if ( color[v] == WHITE ){
            parent[v] = u;
            cntChildren++;
            dfs(v);
            if ( low[u] > low[v] ) low[u] = low[v];
            if ( low[v] >= start[u] ) flag = 0;
        }
        else if ( parent[u] != v )
            if ( low[u] > start[v] ) low[u] = start[v];
    }
    
    color[u] = BLACK;
    if (( parent[u] == -1 && cntChildren > 1 ) || ( parent[u] != -1 &&!flag )) cntArt++;
}

void graphInit(){
    int i;
    
    for ( cntArt = time = i = 0 ; i <= vertices ; i++ ){
        low[i] = start[i] = color[i] = 0;
        parent[i] = leftChild[i] = -1;
    }
}

int main(){
    int test, kase;
    int n, i, x, y;
    
    while ( scanf("%d", &test) != EOF ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%u%u", &vertices, &edgeCnt);
            
            graphInit();
            for ( i = 0 ; i < edgeCnt ; i++ ){
                scanf("%d%d", &x, &y);
                edges[i][0] = x, edges[i][1] = y;
                rightSibling[i] = leftChild[x];
                leftChild[x] = i;
                
                edges[i + edgeCnt][0] = y, edges[i + edgeCnt][1] = x;
                rightSibling[i + edgeCnt] = leftChild[y];
                leftChild[y] = i + edgeCnt;
            }
            
            edgeCnt <<= 1;
            dfs(1);
            printf("Case %d: %u\n", kase, cntArt);
        }
    }
    
    return 0;
}
