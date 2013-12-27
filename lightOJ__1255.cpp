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

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

void RobinKarp(string &text, string &pat, vector<int> &mod, vector<int> &matches){ /* assuming lowercase */
	vector<int> patHash(mod.size());
	vector<int> txtHash(mod.size());
	vector<int> bPwr(mod.size());
	int base = 26, modSz = mod.size(), patSz = pat.size(), textSz = text.size();
	bool matchFound;

	matches.clear();

	for ( int i = 0 ; i < modSz ; i++ ){
		bPwr[i] = 1;
		for ( int j = 0 ; j < patSz ; j++ )
			bPwr[i] = ( bPwr[i] * base ) % mod[i];
	}

	if ( textSz >= patSz ){
		for ( int i = 0 ; i < modSz ; i++ ){
			patHash[i] = 0;
			txtHash[i] = 0;
			for ( int j = 0 ; j < patSz ; j++ ){
				patHash[i] = ((pat[j] - 'a') + patHash[i] * base) % mod[i];
				txtHash[i] = ((text[j] - 'a') + txtHash[i] * base) % mod[i];
			}
		}

		matchFound = true;
		for ( int i = 0 ; i < modSz ; i++ ){
			if ( txtHash[i] != patHash[i] ){
				matchFound = false;
				break;
			}
		}

		if ( matchFound ) matches.push_back(0);

		for ( int j = patSz ; j < textSz ; j++ ){
			matchFound = true;
			for ( int i = 0 ; i < modSz ; i++ ){
				txtHash[i] = ((text[j] - 'a') + ( txtHash[i] * base - (text[j-patSz] - 'a') * bPwr[i] ) % mod[i] + mod[i]) % mod[i];
				if ( txtHash[i] != patHash[i] ) matchFound = false;
			}

			if ( matchFound ) matches.push_back(j - patSz + 1);
		}
	}
}

int main(){
	int test;
	string t, p;
	vector<int> mod, matches;

	mod.push_back(1297), mod.push_back(2179), mod.push_back(307);

	scanf("%d", &test);
	for ( int ks = 1 ; ks <= test ; ks++  ){
    	cin >> t >> p;
		RobinKarp(t, p, mod, matches);
        printf("Case %d: %d\n", ks, matches.size());
	}

	return 0;
}

