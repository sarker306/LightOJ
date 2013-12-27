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

#define CO(V)	V.x,V.y

#define S(x)		((x)*(x))

#define ABS(x)		(((x)>0)?(x):-(x))

#define EPS			1e-8
#define Z(x)		(ABS(x)  < EPS)

#define det(a,b,c,d)	((a)*(d)-(b)*(c))

double pi = 2.*acos(0.);
double sqrt2 = sqrt(2.);
double sqrt3 = sqrt(3.);

double c30 = cos(pi/6);
double s30 = sin(pi/6);
double t30 = tan(pi/6);

double c15 = cos(pi/12);
double s15 = sin(pi/12);
double t15 = tan(pi/12);

double mysqrt(double x){if(x < 0)	return 0;return sqrt(x);}
double myasin(double x){if(x < -1)	return -pi/2;if(x > 1)	return pi/2;return asin(x);}
double myacos(double x){if(x < -1)	return -pi;if(x > 1)	return 0;return acos(x);}

struct V;

V operator+(V a,V b);
double operator*(V a,V b);
V operator*(V b,double a);
V operator*(double a,V b);

struct V{
	double x,y;

	V(){}
	V(double _x,double _y){x=_x;y=_y;}

	double	mag2(){	return S(x)+S(y);	}
	double	mag(){	return sqrt(mag2());	}

	void 	norm(){	double d = mag();x/=d;y/=d;}
	V 		unit(){	V ret = *this;	ret.norm(); return ret;}

	bool	scan(){		return scanf("%lf%lf",&x,&y)==2;	}
	void	show(){		printf("%.10lf %.10lf",x,y);		}
	void	showln(){	printf("[%.4lf, %.4lf]\n",x,y);		}

	double	dot(V b){		return x*b.x + y*b.y;}
	double	cross(V b){		return x*b.y - y*b.x;}

	double	projL(V on){	on.norm();	return this->dot(on);}
	V		projV(V on){	on.norm();	return on * projL(on);}

	V 		perpR(){	return V(y, -x);	}
	V		perpL(){	return V(-y, x);	}

	double angle(V b){	return acos( unit().dot( b.unit() ) );	}

	double angleX(){	if(Z(x) && Z(y)) return -1;	double ret = atan2(y, x);	if(ret < 0)ret += 2*pi;	return ret;	}
};

V operator+(V a,V b){		return V(a.x+b.x, a.y+b.y);	}
V operator-(V a){			return V (-a.x, -a.y);		}
V operator-(V a,V b){		return V(a.x-b.x, a.y-b.y);	}
double operator*(V a,V b){	return a.cross(b);			}
V operator*(double a,V b){	return V(a*b.x, a*b.y);		}
V operator*(V b,double a){	return V(a*b.x, a*b.y);		}
V operator/(V b,double a){	return V(b.x/a, b.y/a);		}

V I(1,0);
V J(0,1);
V INEG(-1,0);
V JNEG(0,-1);
V Origin(0,0);

int main(){
	int test;
	
	while (cin >> test){
		for ( int kase = 1 ; kase <= test ; kase++ ){
			V a, b, c, d;
			double bb, cc, dd;
			a.scan();
			b.scan();
			cin >> bb >> cc >> dd;
			
			V diff = b - a;
			double aa = diff.mag();
			double bbb = bb * aa / ( aa - cc );
			double ddd = dd * aa / ( aa - cc );
			
			printf("Case %d:\n", kase);
			double theta = acos((aa*aa + ddd*ddd - bbb*bbb)/(2*aa*ddd));

			//cout<<theta<<endl;
			diff.norm();
			double Angle = theta + I.angle(diff);
			d = a + V(dd * cos(Angle), dd * sin(Angle));
			c = d + cc * diff;
			
			c.show(); cout<<' '; d.show();
			cout<<endl;
		}
	}
	
	return 0;
}

