#include <stdio.h>
#define SIZE 500

enum TShirtSize{ XS = 1, S, M, L, XL, XXL };
enum NodeColor{ WHITE = 101, GRAY, BLACK};

const int INF = 1<<14;
int capacity[SIZE+1][SIZE+1], residualCap[SIZE+1][SIZE+1];
int parent[SIZE+1], color[SIZE+1], queue[SIZE<<1];
int min_capacity[SIZE+1];
int head, tail;

int getSizeCode(char *s){
    if ( s[0] == 'X' ){
        if ( s[1] == 'S' ) return XS;
        else if ( s[1] == 'X' ) return XXL;
        return XL;
    }
    else if ( s[0] == 'S' ) return S;
    else if ( s[0] == 'M' ) return M;
    return L;
}

void initGraph(int size){
    int i, j;

    for ( i = 0; i < size; i++)
        for ( j = 0; j < size; j++)
            capacity[i][j] = 0;
}

int min(int a, int b){ return (a>b) ? b : a; }

int BFS(int source, int sink){
    int i, u, v, size = sink + 1;

	for (i = 0; i < size; i++){
		color[i] = WHITE;
		min_capacity[i] = INF;
	}

	head = tail = 0;
	queue[tail++] = source;
	color[source] = GRAY;

	while (head != tail)  /* While "queue" not empty.. */
	{
		v = queue[head++];
		for (u = 0; u < size; u++)
			if (color[u] == WHITE && residualCap[v][u] > 0)
			{
				min_capacity[u] = min(min_capacity[v], residualCap[v][u]);
				parent[u] = v;
				color[u] = GRAY;
				if (u == sink) return 1;
				queue[tail++] = u;
			}
	}

	return 0;
}

int maxFlow(int source, int sink){  /* Edmonds-Karp algorithm with O(V³E) complexity */
    int i, j, v, u, max_flow, size = sink + 1;

	for (i = 0; i < size; i++)
		for (parent[i]=i, j = 0; j < size; j++){
			residualCap[i][j] = capacity[i][j];
        }

    max_flow = 0;
	while (BFS(source, sink)){
		max_flow += min_capacity[sink];
		v = sink;
		while (v != source){
			u = parent[v];
			residualCap[u][v] -= min_capacity[sink];
			residualCap[v][u] += min_capacity[sink];
			v = u;
		}
	}

	return max_flow;
}

int main(){
    int test, ks, n, m, i, edges, u;
    char first[4], second[4];

    while ( scanf("%d", &test) != EOF ){
        for ( ks = 1 ; ks <= test; ks++ ){
            edges = 0;
            initGraph(m+8);
            scanf("%d%d", &n, &m);
            for ( i = 1 ; i <= 6 ; i++ ){
                capacity[0][i] = n;
                capacity[i][0] = n;
            }

            for ( i = 1 ; i <= m ; i++ ){
                scanf("%s%s", first, second);
                u = getSizeCode(first);

                capacity[u][i+6] = capacity[i+6][u] = 1;


                u = getSizeCode(second);

                capacity[u][i+6] = capacity[i+6][u] = 1;
            }

            for ( i = 1 ; i <= m ; i++){
                capacity[i+6][m+7] = 1;
                capacity[m+7][i+6] = 1;
            }

            printf("Case %d: %s\n", ks, maxFlow(0, m+7) == m ? "YES" : "NO");
        }
    }

    return 0;
}

