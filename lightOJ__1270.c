#include <stdio.h>

typedef unsigned long long _ull;

char grid[101][9];
_ull config2[101][8][1<<8][2];
char visited[101][8][1<<8][2], now = 1;
int R, C;

_ull backtrack( int row, int col, int conf, int id ){
    int i;
    
    if ( row == 0 && conf == 0 ) return 1;
    if ( row == 0 ) return 0;
    if ( col == C ) return backtrack( row - 1, 0, conf, id );
    if ( visited[row][col][conf][id] == now ) return config2[row][col][conf][id];
    
    visited[row][col][conf][id] = now;
    config2[row][col][conf][id] = 0;
    
    if ( grid[row][col] == '#' || ( (conf & ( 1 << col )) && id )){
        config2[row][col][conf][id] +=
            backtrack( row, col + 1, conf & (~(1<<col)), 1 );
        return config2[row][col][conf][id];
    }
    
    if ( col < (C-1) && grid[row][col+1]!='#' && !( conf & ( 1 << ( col + 1 )))){
        config2[row][col][conf][id] +=
            backtrack( row, col + 2, conf, 1 );
        if ( row > 1 && id && grid[row-1][col] != '#' )
            config2[row][col][conf][id] +=
                backtrack( row, col + 2, conf | (1<<col), 1);
        if ( row > 1 && grid[row-1][col+1] != '#')
            config2[row][col][conf][id] +=
                backtrack( row, col + 2, conf | (1<<(col+1)), 1);
    }
    
    if ( row > 1 && id && grid[row-1][col] != '#'){
        config2[row][col][conf][id] +=
            backtrack( row, col + 1, conf | ( 1 << col ), 1 );
        if ( col < ( C - 1 ) && grid[row-1][col+1] != '#'){ 
            if ( grid[row][col+1] == '#' || ( conf & ( 1 << ( col + 1 )) ))
                config2[row][col][conf][id] +=
                    backtrack( row, col + 2, conf | (3<<col), 1 );
            else
                config2[row][col][conf][id] += 
                    backtrack( row, col + 1, conf | (3<<col), 0 );
        }

        if ( col > 0 && grid[row-1][col-1] != '#' && !(conf & ( 1 << ( col - 1 )))){
            config2[row][col][conf][id] +=
                backtrack( row, col + 1, conf | (3<<(col-1)), 1 );
        }
    }
    
    return config2[row][col][conf][id];
}

void input( int isColWise ){
    int i, j;
    char ch;
    
    getchar();
    if ( isColWise ){
        R ^= C ^= R ^= C;
        for ( i = 0 ; i < C ; i++ )
            for ( j = R ; j ; ){
                 ch = getchar();
                 if ( ch == '\n' ) continue;
                 grid[j--][i] = ch;
                 if ( j == 0 ) break;
            }
        
        for ( i = R ; i ; i-- ) grid[i][C] = 0;
    }
    else
        for ( i = R ; i ; i-- ) gets(grid[i]);
}

void printGrid( void ){
    int i ;
    
    puts("");
    for ( i = R ; i ; i-- ) puts(grid[i]);
    puts("");
}

int main(){
    int test, kase;
    
    while ( scanf("%d", &test) == 1 ){
        for( kase = 1 ; kase <= test ; kase++ ){
            scanf("%d%d", &R, &C);
            if ( C > R ) input(1);
            else input(0);
            /*printGrid();*/
            printf("Case %d: %llu\n", kase, backtrack(R, 0, 0, 1));
            now++;
        } break;
    }

    return 0;
}
