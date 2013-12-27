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
#define SIZE 151
#define LOW 100000

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

unsigned dp[7][LOW + 1][6];
char vis[7][LOW + 1][6];
int base, lowLimit = LOW;

unsigned rec(int score, int last){
    unsigned res = 0;
    int i;

    if ( score < 0 ) return 0;
    if ( score == 0 ) return 1;
    if ( vis[base][score][last] ) return dp[base][score][last];
    vis[base][score][last] = 1;

    for ( i = 0 ; i < base ; i++ ) if ( last != i ) res += rec(score - (last - i) * (last - i), i);

    return dp[base][score][last] = res;
}

unsigned bM[SIZE][SIZE], fnl[SIZE][SIZE], basis[SIZE];
int N;

void initMatrices(){
    int i, j;

    N = (base - 1) * (base - 1) * base;
    memset(bM, 0, sizeof(bM));

    for ( i = 0 ; i < N ; i++ ){
        basis[i] = rec( lowLimit - i/base - 1, i % base );
    }

    for ( i = 0 ; i < base ; i++ ){
        for ( j = 0 ; j < base ; j++ ){
            if ( i != j ) bM[i][((i-j)*(i-j)-1)*base + j] = 1;
        }
    }

    for ( i = base ; i < N ; i++ ) bM[i][i - base] = 1;
}

void matrixMult(unsigned to[][SIZE], unsigned one[][SIZE], unsigned two[][SIZE]){
    int i, j, k;
    unsigned tmp[SIZE][SIZE];

    for ( i = 0 ; i < N ; i++ )
        for ( j = 0 ; j < N ; j++ ){
            tmp[i][j] = 0;
            for ( k = 0 ;  k < N ; k++ ) tmp[i][j] += one[i][k] * two[k][j];
        }

    for ( i = 0 ; i < N ; i++ )
        for ( j = 0 ; j < N ; j++ )
            to[i][j] = tmp[i][j];
}

void matrixExpo(int pwr){
    unsigned tmp[SIZE][SIZE];
    int i, j;

    for ( i = 0 ; i < N ; i++ ) for ( j = 0 ; j < N ; j++ ) tmp[i][j] = bM[i][j];
    memset(fnl, 0, sizeof(fnl));
    for ( i = 0 ; i < N ; i++ ) fnl[i][i] = 1;

    while ( pwr ){
        if ( pwr & 1 ) matrixMult(fnl, fnl, tmp);
        matrixMult(tmp, tmp, tmp);
        pwr >>= 1;
    }
}

unsigned calcNumbers(int score){
    unsigned res = 0, tmp;
    int i, j;

    if ( score <= lowLimit ){
        for ( i = 1 ; i < base ; i++ ) res += rec(score,i);
        return res;
    }

    initMatrices();
    matrixExpo(score - lowLimit + 1);
    for ( j = 1 ; j < base ; j++ )
        for ( i = 0 ; i < N ; i++ ) res += fnl[j][i] * basis[i];

    return res;
}

int main(){
    int score, i, test, ks;
    unsigned res;

    while ( scanf("%d", &test) != EOF ){
        for ( ks = 1 ; ks <= test ; ks++ ){
            scanf("%d%d", &base, &score);
            printf("Case %d: %u\n", ks, calcNumbers(score));
        }
    }

    return 0;
}

