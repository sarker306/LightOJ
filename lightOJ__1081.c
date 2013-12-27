#include <stdio.h>
#include <string.h>
#define ROW 513
#define NOTFOUND -9999

typedef struct{
    int x, y;
}point;

typedef struct{
    point leftCorner, rightCorner, value;
}node;

long nwChild( long index ) { index++; return(index<<2) - 3 ; }
long neChild( long index ) { index++; return (index<<2) - 2 ; }
long seChild( long index ) { index++; return (index<<2) - 1 ; }
long swChild( long index ) { index++; return (index<<2) ; }

long array[ROW][ROW];
node tree[(ROW*ROW)<<2];

void maximumValue(point *res, point *childRes){
    int i;
    
    *res = childRes[0];
    for ( i = 1 ; i < 4 ; i++ ){
        if ( res->x == NOTFOUND ) *res = childRes[i];
        else if ( childRes[i].x != NOTFOUND && res->x != NOTFOUND
            && array[childRes[i].x][childRes[i].y] > array[res->x][res->y] )
            *res = childRes[i];
    }
}

void initializeTree( point *result, long index, int startx, int starty, int endx, int endy ){
    point childResult[4];
    int midx, midy;
    int i;
    
    tree[index].leftCorner.x = startx, tree[index].rightCorner.x = endx;
    tree[index].leftCorner.y = starty, tree[index].rightCorner.y = endy;
    if ( startx == endx && starty == endy ){
        tree[index].value.x = startx, tree[index].value.y = starty;
        *result = tree[index].value;
        return;
    }
    
    if ( startx > endx || starty > endy ){
        tree[index].value.x = NOTFOUND, tree[index].value.y = NOTFOUND;
        *result = tree[index].value;
        return;
    }
    
    midx = ( startx + endx ) >> 1, midy = ( starty + endy ) >> 1;
    initializeTree( childResult, nwChild(index), startx, starty, midx, midy);
    initializeTree( childResult+1, neChild(index), startx, midy + 1 , midx, endy);
    initializeTree( childResult+2, seChild(index), midx + 1, midy + 1, endx, endy);
    initializeTree( childResult+3, swChild(index), midx + 1, starty, endx, midy);
    maximumValue(result, childResult);
    tree[index].value = *result;
}

int _startx, _starty, _endx, _endy;

void query( point *result, long index){
    point childResult[4];
    
    if ( tree[index].leftCorner.x > tree[index].rightCorner.x || tree[index].leftCorner.y > tree[index].rightCorner.y ){
        result->x = NOTFOUND, result->y = NOTFOUND;
        return;
    }
    
    if ( tree[index].leftCorner.x > _endx || tree[index].leftCorner.y > _endy 
        || tree[index].rightCorner.x < _startx || tree[index].rightCorner.y < _starty ){
        result->x = NOTFOUND, result->y = NOTFOUND;
        return;
    }
    
    if ( tree[index].leftCorner.x >= _startx && tree[index].leftCorner.y >=_starty &&
        tree[index].rightCorner.x <= _endx && tree[index].rightCorner.y <= _endy ){
        *result = tree[index].value;
        return;
    }
    
    query( childResult, nwChild(index));
    query( childResult + 1, neChild(index));
    query( childResult + 2, seChild(index));
    query( childResult + 3, swChild(index));
    maximumValue(result, childResult);
}

int main(){
    int i, j, n, x, test, kase;
    long q;
    point tmp;
    int powerTwo[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    
    /*freopen("lightOJ__1081.in", "r", stdin);*/
    /*freopen("lightOJ__1081.out", "w", stdout);*/
    while (  scanf("%d", &test ) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%d%ld", &n, &q);
            
            for ( i = 0 ; i < n ; i++ ){
                for ( j = 0 ; j < n ; j++ ) scanf("%ld", &array[i][j]);
            }
            
            initializeTree(&tmp, 0, 0, 0, n-1, n-1);
            printf("Case %d:\n", kase);
            while (q--){
                scanf("%d%d%d", &i, &j, &x);
                i--, j--;
                _startx = i, _starty = j;
                _endx = i + x - 1, _endy = j + x - 1;
                query(&tmp, 0);
                printf("%ld\n", array[tmp.x][tmp.y]);
            }
        }
    }
    
    return 0;
}
/*
3

4 10
67  1  2  3
 8 88 21  1
89 12  0 12
 5  5  5  5
1 1 2
1 3 2
3 3 2
1 1 4
2 2 3
1 1 3
2 2 2
1 3 2
3 1 2
2 3 2

4 10
 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15 16
1 1 2
1 3 2
3 3 2
1 1 4
2 2 3
1 1 3
2 2 2
1 3 2
3 1 2
2 3 2

5 5
17 24  1  8 15
23  5  7 14 16
 4  6 13 20 22
10 12 19 21  3
11 18 25  2  9
1 1 3
2 2 3
3 3 3
3 1 2
1 2 4
*/
