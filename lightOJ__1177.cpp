#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <climits>
#define INF INT_MAX
#define SIZE 105
using namespace std;

enum NodeColor{ WHITE = 101, GRAY, BLACK};

int capacity[SIZE+1][SIZE+1], residualCap[SIZE+1][SIZE+1];
int parent[SIZE+1], color[SIZE+1], queue[SIZE<<1];
int min_capacity[SIZE+1];
int head, tail;

void initGraph(int size){
    int i, j;

    for ( i = 0; i < size; i++)
        for ( j = 0; j < size; j++)
            capacity[i][j] = 0;
}

int min(int a, int b){ return (a>b) ? b : a; }

int BFS(int source, int sink, int size){
    int i, u, v;

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

int maxFlow(int source, int sink, int size){  /* Edmonds-Karp algorithm with O(V³E) complexity */
    int i, j, v, u, max_flow;

	for (i = 0; i < size; i++)
		for (parent[i]=i, j = 0; j < size; j++){
			residualCap[i][j] = capacity[i][j];
        }

    max_flow = 0;
	while (BFS(source, sink, size)){
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
	int machines, wires, size;
	int mirror[SIZE];
	int test, kase;

	cin>>test;
	for ( kase = 1 ; kase <= test ; kase++ ){
		cin>>machines>>wires;

		size = (machines<<1) - 1;
		initGraph(size);
		for ( int i = 2 ; i < machines ; i++ ) mirror[i] = machines + i - 1;
		mirror[1] = 1, mirror[machines] = machines;

		int u, v, cost;
		for ( int i = 2 ; i < machines ; i++ ){
			cin>>v;
			capacity[i][mirror[i]] = v;
		}

		while ( wires-- ){
			cin>>u>>v>>cost;
			capacity[mirror[u]][v] += cost;
			capacity[mirror[v]][u] += cost;
		}

		cout<<"Case "<<kase<<": "<<maxFlow(1, machines, size)<<endl;
	}

	return 0;
}

