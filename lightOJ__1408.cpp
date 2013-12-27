#include <cstdio>
#include <cmath>

using namespace std;

int k1, k2, kase;
double p;
const double EPS = 1e-6;
double b;
double myPow(int p){
	if ( p == 0 ) return 1;

	double tmp = myPow(p>>1);
	tmp *= tmp;
	if ( p & 1 ) tmp *= b;
	
	return tmp;
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( kase = 1 ; kase <= test ; kase++ ){
			scanf("%lf%d%d", &p, &k1, &k2);
			
			double res;
			double tmp, tmp1;

			b = 1 - p;
			tmp = myPow(k1);
			b = p;
			tmp1 = myPow(k2);
			
			if ( fabs(p) < EPS ) res = k1;
			else if ( fabs(1-p) < EPS ) res = k2;
			else res = (( 1 - tmp ) * ( 1 - tmp1 )) / ((1-p)*tmp1 + p*tmp - tmp*tmp1);
			
			printf("Case %d: %.10lf\n", kase, res);
		}
	}
	
	return 0;
}

