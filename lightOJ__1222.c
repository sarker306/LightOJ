#include <stdio.h>
#include <limits.h>
#include <string.h>
#define SIZE 55
#define MAXVERTICES 120 /* size * 2 + 2 */
#define INF INT_MAX
#define NIL 0

int pair[MAXVERTICES], degree[MAXVERTICES], adj[MAXVERTICES>>1][MAXVERTICES>>1];
int dist[MAXVERTICES], T[MAXVERTICES];

int dfsAugment(int u){
	int i, v;
	
	if ( u == NIL ) return 1;
	for ( i = 0 ; i < degree[u] ; i++ ){
		v = adj[u][i];
		if ( dist[pair[v]] == dist[u] + 1 )
			if ( dfsAugment(pair[v]) ){
				pair[u] = v;
				pair[v] = u;
				return 1;
			}
	}
	
	dist[u] = INF;
	return 0;
}

int queue[MAXVERTICES + 2], head, tail;
int rightEncountered[MAXVERTICES + 2], rightIndex;

int bfsAugment(int leftNodes){
	int i, u, v;
	
	rightIndex = head = tail = 0;
	dist[NIL] = INF;
	for ( i = 1 ; i <= leftNodes ; i++ )
		if ( pair[i] == NIL )
			queue[tail++] = i, dist[i] = 0;
		else dist[i] = INF;
		
	while ( head != tail ){
		u = queue[head++];
		
		for ( i = 0; i < degree[u] ; i++ ){
			v = adj[u][i];
			if ( dist[pair[v]] == INF ){
				rightEncountered[rightIndex++] = v;
				dist[pair[v]] = dist[u] + 1;
				queue[tail++] = pair[v];
			}
		}
	}
	
	return (dist[NIL] != INF);
}

void graphInit( int nodes ){
	int i;
	
	for ( i = 0 ; i < nodes ; i++ )
		pair[i] = NIL, degree[i] = 0;
}

int HopcroftKarp(int leftNodes, int rightNodes){
	int i, matching = 0;
	
	while ( bfsAugment(leftNodes) ){
		for ( i = 1 ; i <= leftNodes ; i++ )
			if ( pair[i] == NIL && dfsAugment( i ) ) matching++;
	}
	
	memset(T, 1, sizeof(T));
	
	for ( i = 0 ; i < tail ; i++ ) T[queue[i]] = 0;
	for ( i = 0 ; i < rightIndex ; i++ ) T[rightEncountered[i]] = 0;
	
	return matching;
}

int ExactMatch( int array[SIZE][SIZE], int match[SIZE], int n ){
    int i, j;
    int zeroes[SIZE], minZero, minZeroInd;
    char isRowSelected[SIZE], isColSelected[SIZE];
    
    for ( i = 1 ; i <= n ; i++ ){
        zeroes[i] = 0;
        isRowSelected[i] = 0;
        isColSelected[i] = 0;
        for ( j = 1 ; j <= n ; j++ )
            if ( array[i][j] == 0 ) zeroes[i]++;
    }
    
    for ( i = 1 ; i <= n ; i++ ){
        minZero = SIZE + 1, minZeroInd = -SIZE;
        for ( j = 1 ; j <= n ; j++ ){
            if ( isRowSelected[j] ) continue;
            /*printf("(%d->%d) ", j, zeroes[j]);*/
            if ( minZero > zeroes[j] )
                minZero = zeroes[j], minZeroInd = j;
        }
        
        if ( minZero == 0 ){
            /*printf("\nNo row contains 0, No further matching found\n");*/
            return 0;
        }
        
        for ( j = 1 ; j <= n ; j++ )
            if ( isColSelected[j] == 0 && array[minZeroInd][j] == 0 ) break;
        
        if ( j > n ){
            /*printf("\nColumns containing 0 previously selected.... No further matching found\n");*/
            return 0;
        }
        
        isRowSelected[minZeroInd] = 1;
        match[minZeroInd] = j;
        isColSelected[j] = 1;
        
        /*printf("\n%dth row matched to %dth column....\n", minZeroInd, j);*/
        for ( j = 1 ; j <= n ; j++ )
            if ( array[j][match[minZeroInd]] == 0 ) zeroes[j]--;
    }
    
    /*for ( i = 1 ; i <= n ; i++ ) printf("%dth row -> %dth column\n", i, match[i]);*/
    return 1;
}

void printMatrix( int array[SIZE][SIZE], int n ){
    int i, j;
    
    puts("");
    for ( i = 1 ; i <= n ; i++ ){
        for ( j = 1 ; j <= n ; j++ ) printf("%5d", array[i][j] );
        puts("");
    }
    puts("");
}

void MinimumWeightedMatch( int array[SIZE][SIZE], int match[SIZE], int n ){
    int i, j;
    int mini;
                
    for ( i = 1 ; i <= n ; i++ ){
        mini = INT_MAX;
        for ( j = 1 ; j <= n ; j++ )
            if ( mini > array[i][j] ) mini = array[i][j];
        
        for ( j = 1 ; j <= n ; j++ ) array[i][j] -= mini;
    }
    
    /*printMatrix(array, n);
    printf("For row...\n\n");*/
    if ( ExactMatch(array, match, n) ) return;
    
    for ( j = 1 ; j <= n ; j++ ){
        mini = INT_MAX;
        for ( i = 1 ; i <= n ; i++ )
            if ( mini > array[i][j] ) mini = array[i][j];
        
        for ( i = 1 ; i <= n ; i++ ) array[i][j] -= mini;
    }
    
    /*printMatrix(array, n);
    printf("For column...\n\n");*/
    if ( ExactMatch(array, match, n) ) return;
    
    while ( 1 ){
        graphInit( 2 * n + 1 );
        
        mini = INT_MAX;
        for ( i = 1 ; i <= n ; i++ )
            for ( j = 1 ; j <= n ; j++ )
                if ( array[i][j] == 0 ) adj[i][degree[i]++] = n + j;
        
        if ( n == HopcroftKarp(n, n) ){
            /*printf("Matching about to be found...\n");*/
            for ( i = 1 ; i <= n ; i++ ){
                match[i] = pair[i] - n;
                /*printf("HKarp matches row %d to col %d\n", i, pair[i] - n);*/
            }
            return;
        }
        
        for ( i = 1 ; i <= n ; i++ )
            for ( j = 1 ; j <= n ; j++ )
                if ( !T[i] && T[j+n] && mini > array[i][j] )
                    mini = array[i][j];

    	for ( i = 1 ; i <= n ; i++ ){
            if ( T[i] ){
                /*printf(" r%d", i);*/
                for ( j = 1 ; j <= n ; j++ )
                    array[i][j] += mini;
            }
        }
        
    	for ( i = 1 ; i <= n ; i++ ){
            if ( !T[i + n] ){
                /*printf(" c%d", i);*/
                for ( j = 1 ; j <= n ; j++ )
                    array[j][i] += mini;
            }
        }
        
        /*puts("");*/
        for ( i = 1 ; i <= n ; i++ )
            for ( j = 1 ; j <= n ; j++ )
                array[i][j] -= mini;
        
        /*printMatrix(array, n);*/
        /*getchar();*/
    }
    
    ExactMatch(array, match, n);
}

int main(){
    int n, i, j, test, kase, x, profit;
    int array[SIZE][SIZE], matching[SIZE], tmp[SIZE][SIZE];
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%d", &n);
            for ( i = 1 ; i <= n ; i++ )
                for ( j = 1 ; j <= n ; j++ ){
                    scanf("%d", &x);
                    tmp[i][j] = x;
                    array[i][j] = -x;
                }
            
            MinimumWeightedMatch(array, matching, n);
            for ( profit = 0, i = 1 ; i <= n ; i++ ) profit += tmp[i][matching[i]];
            printf("Case %d: %d\n", kase, profit);
            /*ExactMatch(array, matching, n);*/
        }
    }
    
    return 0;
}
/*
5
10 19 8 15 19
10 18 7 17 19
13 16 9 14 19
12 19 8 18 19
14 17 10 19 19
*/
