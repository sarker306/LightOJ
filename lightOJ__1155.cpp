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
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

#define SIZE 205

enum Colors{WHITE = 1, GRAY, BLACK};
int resCap[SIZE][SIZE], cap[SIZE][SIZE];
int quu[SIZE<<1], head, tail;
int color[SIZE], parent[SIZE];
int minCap[SIZE];

int bfs(int source, int sink, int size){
	for ( int i = 0 ; i < size ; i++ )
		minCap[i] = INT_MAX, color[i] = WHITE;

	head = tail = 0;
	quu[tail++] = source;
	color[source] = GRAY;
	//cout<<"hmm"<<endl;
	while ( head != tail ){
		int u = quu[head++];
		//cout<<"# "<<u<<" "<<minCap[u]<<endl;

		if ( u == sink ) return 1;
		for ( int v = 0 ; v < size ; v++ ){
			if ( resCap[u][v] > 0 && color[v] == WHITE ){
				minCap[v] = minCap[u];
				if ( minCap[v] > resCap[u][v] )
					minCap[v] = resCap[u][v];

				//cout<<" ("<<v<<' '<<minCap[v]<<")";
				parent[v] = u;
				color[v] = GRAY;
				quu[tail++] = v;
			}
		}
		//cout<<endl;
		color[u] = BLACK;
	}

	return 0;
}

int MaxFlow( int source, int sink, int size ){
	int maxFlow = 0;

	for ( int i = 0 ; i < size ; i++ ){
		parent[i] = i;
		for ( int j = 0 ; j < size ; j++ )
			resCap[i][j] = cap[i][j];
	}
	//cout<<"In maxflow"<<endl;
	while ( bfs(source, sink, size) ){
		//cout<<"Now maxFlow increases by "<<minCap[sink]<<endl;
		for ( int v = sink ; v != source ; v = parent[v] ){
			resCap[parent[v]][v] -= minCap[sink];
			resCap[v][parent[v]] += minCap[sink];
		}

		maxFlow += minCap[sink];
	}

	return maxFlow;
}

void initGraph(int size){
	for ( int i = 0 ; i < size ; i++ )
		for ( int j = 0 ; j < size ; j++ )
			cap[i][j] = 0;
}

int main(){
	int outVer[SIZE], node, edge, size, source, sink;
	int test;

	cin >> test;
	for ( int kase = 1 ; kase <= test ; kase++ ){
		cin >> node;
		source = 0;
		sink = 2 * node + 1;
		size = sink + 1;

		initGraph(size);

		outVer[source] = source, outVer[sink] = sink;
		for ( int i = 1 ; i <= node ; i++ ){
			outVer[i] = node + i;
			cin>>cap[i][outVer[i]];
		}

		cin >> edge;
		while ( edge-- ){
			int u, v, cost;
			cin >> u >> v >> cost;

			cap[outVer[u]][v] += cost;
		}

		int B, D;
		cin >> B >> D;

		for ( int i = 0 ; i < B ; i++ ){
			int u;
			cin >> u;
			cap[outVer[source]][u] = INT_MAX;
		}

		for ( int i = 0 ; i < D ; i++ ){
			int u;
			cin >> u;
			cap[outVer[u]][sink] = INT_MAX;
		}

		cout<<"Case "<<kase<<": ";
		cout<<MaxFlow(source, sink, size)<<endl;
	}

	return 0;
}

