#include <cstdio>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define ALL(v) (v).begin(), (v).end()
#define SET(a, x) memset((a), (x), sizeof(a))
#define SZ(a) ((int)(a).size())
#define CL(a) ((a).clear())
#define SORT(x) sort(ALL(x))
#define mp make_pair
#define pb push_back
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)
#define SIZE 240005

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

vector<int>coord[2];

struct Event{
	int x, y1, y2;
	char type;

	void set(int _x, int _y1, int _y2, int _type){
		x = _x, y1 = _y1, y2 = _y2, type = _type;
	}
	
	void print(){
		cout << "->" << x << ' ' << y1 << ' ' << y2 << ' ' << type << endl;
	}
};

struct Cmp{
	bool operator()(const Event &a, const Event &b){
		return a.x < b.x;
	}
};

vector<Event>events;

int toUpdate[SIZE<<2];
int tree[SIZE<<2];
int cover[SIZE<<2];

int lChild(int ind){ return (ind<<1) + 1; }
int rChild(int ind){ return (ind + 1)<<1; }
int lo, hi;

void update(int ind, int left, int right, int val){
	int mid = (left + right)>>1, lc = lChild(ind), rc = rChild(ind);
	/*
	if ( toUpdate[ind] ){
		cover[ind] += toUpdate[ind];
		if ( cover[ind] ) tree[ind] = coord[1][right] - coord[1][left-1];
		else if ( left != right ){
			update(lc, left, mid, toUpdate[ind]);
			update(rc, mid + 1, right, toUpdate[ind]);
			toUpdate[ind] = 0;
			tree[ind] = tree[rc] + tree[lc];
		}
		else tree[ind] = 0;
		if ( left != right ){
			toUpdate[lc] += toUpdate[ind];
			toUpdate[rc] += toUpdate[ind];
		}
		
		toUpdate[ind] = 0;
	}*/
	
	if ( hi < left || lo > right ) return;
	if ( left >= lo && right <= hi ){
		cover[ind] += val;
		if ( cover[ind] ) tree[ind] = coord[1][right] - coord[1][left-1];
		else if ( left != right ){
			/*update(lc, left, mid, toUpdate[ind]);
			update(rc, mid + 1, right, toUpdate[ind]);
			toUpdate[ind] = 0;*/
			tree[ind] = tree[rc] + tree[lc];
		}
		else tree[ind] = 0;
	/*	if ( left != right ){
			toUpdate[lc] += val;
			toUpdate[rc] += val;
		}*/
		
		return;
	}

	update(lc, left, mid, val);
	update(rc, mid + 1, right, val);
	if ( cover[ind] == 0 )	tree[ind] = tree[lc] + tree[rc];
}
/*
int query(int ind, int left, int right){
	int mid = (left + right)>>1, lc = lChild(ind), rc = rChild(ind);
	int res = 0;

	if ( toUpdate[ind] ){
		cover[ind] += toUpdate[ind];
		if ( cover[ind] ) tree[ind] = coord[1][right] - coord[1][left-1];
		else tree[ind] = 0;
		if ( left != right ){
			toUpdate[lc] += toUpdate[ind];
			toUpdate[rc] += toUpdate[ind];
		}

		toUpdate[ind] = 0;
	}

	if ( hi < left || lo > right ) return 0;
	if ( left >= lo && right <= hi ) return tree[ind];
	if ( lo <= mid ) res += query(lc, left, mid);
	if ( hi > mid ) res += query(rc, mid + 1, right);
	return res;
}*/

int main(){
	int test, ks, n;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			coord[0].clear(), coord[1].clear();
			events.clear();
			set<int>xx, yy;
			for ( int i = 0 ; i < n ; i++ ){
				int x1, x2, y1, y2;
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				xx.insert(x1), xx.insert(x2);
				xx.insert(x1+1), xx.insert(x2+1);
				xx.insert(x1-1), xx.insert(x2-1);
				yy.insert(y1), yy.insert(y2);
				yy.insert(y1+1), yy.insert(y2+1);
				yy.insert(y1-1), yy.insert(y2-1);
				Event p;
				p.set(x1, y1+1, y2, 1);
				events.pb(p);
				p.set(x2, y1+1, y2, -1);
				events.pb(p);
			}
			
			coord[0].resize(xx.size() + 1);
			coord[1].resize(yy.size() + 1);
			copy(xx.begin(), xx.end(), coord[0].begin());
			copy(yy.begin(), yy.end(), coord[1].begin());
			coord[0][xx.size()] = coord[1][yy.size()] = INT_MAX;
			
			sort(events.begin(), events.end(), Cmp());
			memset(cover, 0, sizeof(cover));
			memset(tree, 0, sizeof(tree));
			memset(toUpdate, 0, sizeof(toUpdate));
			
			int prevPt = events[0].x;
			ll res = 0;
			for ( int i = 0 ; i < events.size() ; i++ ){
				Event p = events[i];
			//	p.print();
				lo = lower_bound(coord[1].begin(), coord[1].end(), p.y1) - coord[1].begin();
				hi = lower_bound(coord[1].begin(), coord[1].end(), p.y2) - coord[1].begin();
				if ( prevPt != p.x ){
					ll tmp = tree[0];
					//cout<<tmp<< ' ' << tmp * ( p.x - prevPt ) <<endl;
					res += tmp * (p.x - prevPt);
				}

				update(0, 0, coord[1].size() - 1, p.type);
				prevPt = p.x;
			}
			
			printf("Case %d: %lld\n", ks, res);
		}
	}
	
	return 0;
}
/*
2
3
0 2 3 6
1 3 6 7
2 1 5 4
2
0 0 4 4
1 1 2 5
*/
