#include <stdio.h>
#include <string.h>
#define POSTRS 100005
#define TREESZ (POSTRS<<3)

using namespace std;
long x, y;

char isVisible[POSTRS];
long poster[TREESZ];
char toUpdate[TREESZ];

void init( long index, long left, long right ){
    long mid = ( left + right ) >> 1, lc = (index<<1)|1, rc = (index+1)<<1;

    toUpdate[index] = 0;
    poster[index] = 0;
    if ( left == right ) return;
    init( lc, left, mid );
    init( rc, mid + 1, right);
}

void update( long index, long left, long right, long n ){
    long mid = ( left + right ) >> 1, lc = (index<<1)|1, rc = (index+1)<<1;

    if ( toUpdate[index] ){
        if ( left != right ){
            toUpdate[lc] = toUpdate[rc] = 1;
            poster[lc] = poster[rc] = poster[index];
        }

        toUpdate[index] = 0;
    }

    if ( left > y || right < x ) return;

    toUpdate[index] = 0;
    if ( left >= x && right <= y ){
        poster[index] = n;
        /*printf("(%ld-%ld) covered with %u\n", left, right, n);*/
        if ( left != right ){
            toUpdate[lc] = toUpdate[rc] = 1;
            poster[lc] = poster[rc] = n;
        }

        return;
    }

    update(lc, left, mid, n );
    update( rc, mid + 1, right, n );
}

void query( long index, long left, long right ){
    long mid = ( left + right ) >> 1, lc = (index<<1)|1, rc = (index+1)<<1;

    if ( toUpdate[index] == 1 ){
        if ( left != right ){
            toUpdate[lc] = toUpdate[rc] = 1;
            poster[lc] = poster[rc] = poster[index];
        }

        toUpdate[index] = 0;
    }

    if ( left > y || right < x ) return;

    if ( left == right ){
        /*printf("%ld %ld %ld %u\n", index, left, right, poster[index]);*/
        if ( isVisible[poster[index]] == 0 ){
            isVisible[poster[index]] = 1;
        }
    }

    if ( left != right ){
        query( lc, left, mid );
        query( rc, mid + 1, right );
    }
}

int main(){
    int test, kase;
    long n, i, cnt;
    long range;

    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld", &n);

            memset(isVisible, 0, sizeof(isVisible));

			init( 0, 1, 2*n);
            for ( i = 1 ; i <= n ; i++ ){
                scanf("%ld%ld", &x, &y);
                update( 0, 1, 2*n, i );
            }

            x = 1, y = 2*n;
            query( 0, 1, 2*n );
            for ( i = 1, cnt = 0 ; i <= n ; i++ ) cnt += isVisible[i];
            printf("Case %d: %ld\n", kase, cnt);
        }
    }

    return 0;
}
/*
4
5
1 4
2 6
8 10
3 4
7 10
4
1 100
40 50
1 39
52 100
3
100 200
200 300
1 198
3
3 7
1 4
5 10
*/
