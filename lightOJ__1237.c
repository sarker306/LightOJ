#include <stdio.h>
#include <string.h>
#include <limits.h>
#define SIZE 55
#define MAXVERTICES 120
#define INF (1<<29)
#define NEGINF (-INF)
#define NIL 0

int pair[MAXVERTICES], degree[MAXVERTICES], adj[MAXVERTICES][MAXVERTICES];
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
        /*puts("");*/
        
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
        mini = INF;
        for ( j = 1 ; j <= n ; j++ )
            if ( mini > array[i][j] ) mini = array[i][j];
        
        for ( j = 1 ; j <= n ; j++ ) array[i][j] -= mini;
    }
    
    if ( ExactMatch(array, match, n) ) return;
    
    for ( j = 1 ; j <= n ; j++ ){
        mini = INF;
        for ( i = 1 ; i <= n ; i++ )
            if ( mini > array[i][j] ) mini = array[i][j];
        
        for ( i = 1 ; i <= n ; i++ ) array[i][j] -= mini;
    }
    
    if ( ExactMatch(array, match, n) ) return;
    
    while ( 1 ){
        graphInit( 2 * n + 1 );
        
        mini = INF;
        for ( i = 1 ; i <= n ; i++ )
            for ( j = 1 ; j <= n ; j++ )
                if ( array[i][j] == 0 ) adj[i][degree[i]++] = n + j;
        
        if ( n == HopcroftKarp(n, n) ){
            for ( i = 1 ; i <= n ; i++ ) match[i] = pair[i] - n;
            
            break;
        }
        
        for ( i = 1 ; i <= n ; i++ )
            for ( j = 1 ; j <= n ; j++ )
                if ( !T[i] && T[j+n] && (mini > array[i][j]) )
                    mini = array[i][j];

    	for ( i = 1 ; i <= n ; i++ ){
            if ( T[i] ){
                for ( j = 1 ; j <= n ; j++ )
                    array[i][j] += mini;
            }
        }
        
    	for ( i = 1 ; i <= n ; i++ ){
            if ( !T[i + n] ){
                for ( j = 1 ; j <= n ; j++ )
                    array[j][i] += mini;
            }
        }
        
        for ( i = 1 ; i <= n ; i++ )
            for ( j = 1 ; j <= n ; j++ )
                array[i][j] -= mini;
    }
}

int mini( int a, int b ){ return a > b ? b : a; }

void ProcessMaxMoney( int *enters, int *exits, int n, int k, int g ){
    int i, j, x;
    int array[SIZE][SIZE], tmp[SIZE][SIZE], match[SIZE];
    int minMoney = 0, maxMoney = 0;
    
    for ( i = 1 ; i <= n ; i++ )
        for ( j = 1 ; j <= n ; j++ ){
            if ( enters[i] < exits[j] ){
                x = exits[j] - enters[i] - k;
                array[i][j] = mini( x * x, g );
            }
            else array[i][j] = INF;
            tmp[i][j] = array[i][j];
        }
    
    x = 1;
    MinimumWeightedMatch(tmp, match, n);
    for ( i = 1 ; i <= n && x ; i++ )
        if ( array[i][match[i]] == INF ) x = 0;
        else minMoney += array[i][match[i]];
    
    for ( i = 1 ; i <= n && x ; i++ )    
        for ( j = 1 ; j <= n ; j++ )
            if ( array[i][j] == INF ) tmp[i][j] = INF;
            else tmp[i][j] = -array[i][j];
    
    MinimumWeightedMatch(tmp, match, n);
    for ( i = 1 ; i <= n && x ; i++ )
        if ( array[i][match[i]] == INF ) x = 0;
        else maxMoney += array[i][match[i]];
    
    if ( x && minMoney <= maxMoney && minMoney >= 0 )
        printf(" %d %d\n", minMoney, maxMoney);
    else puts(" impossible");
}

int main(){
    int test, kase, i;
    int n, k, g;
    int enters[SIZE], exits[SIZE];
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%d%d%d", &n, &k, &g);
            
            for ( i = 1 ; i <= n ; i++ ) scanf("%d", &enters[i]);
            for ( i = 1 ; i <= n ; i++ ) scanf("%d", &exits[i]);
            printf("Case %d:", kase);
            ProcessMaxMoney( enters, exits, n, k, g );
        }
    }
    
    return 0;
}
