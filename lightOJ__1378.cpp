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

#define S(x)        ((x)*(x))
#define ABS(x)		(((x)>0)?(x):-(x))
#define EPS			1e-8
#define Z(x)		(ABS(x)  < EPS)
double pi = 2 * acos(0);

struct V;
V operator+(V a,V b);
double operator*(V a,V b);
V operator*(V b,double a);
V operator*(double a,V b);

struct V{
	double x,y;

	V(){}
	V(double _x,double _y){x=_x;y=_y;}
	void set(double _x,double _y){x=_x;y=_y;}

	double	mag2(){	return S(x)+S(y);	}
	double	mag(){	return sqrt(mag2());	}

	void 	norm(){	double d = mag();x/=d;y/=d;}
	V 		unit(){	V ret = *this;	ret.norm(); return ret;}

	bool	scan(){		return scanf("%lf%lf",&x,&y)==2;	}
	void	show(){		printf("(%.2lf, %.2lf)",x,y);		}
	void	showln(){	printf("(%.4lf, %.4lf)\n",x,y);		}

	double	dot(V b){		return x*b.x + y*b.y;}
	double	cross(V b){		return x*b.y - y*b.x;}

	double	projL(V on){	on.norm();	return this->dot(on);}
	V		projV(V on){	on.norm();	return on * projL(on);}

	V 		perpR(){	return V(y, -x);	}
	V		perpL(){	return V(-y, x);	}

	V       rot(double ang) {double px = x*cos(ang)-y*sin(ang), py = x*sin(ang)+y*cos(ang); return V(px,py);}

	double angle(V b){	return acos( unit().dot( b.unit() ) );	}

	double angleX(){	if(Z(x) && Z(y)) return -1;	double ret = atan2(y, x);	if(ret < 0)ret += 2*pi;	return ret;	}
	bool operator==(V a)     {  return fabs(x-a.x)<EPS && fabs(y-a.y)<EPS; }
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

struct Circle{
	V ctr;
	double rad;
	
	Circle(){}
	Circle(V c, double r){ ctr = c, rad = r; }
	bool scan(){ return scanf("%lf%lf%lf", &ctr.x, &ctr.y, &rad) == 3; }
};

V normToLine;

void circleTouchingLines(Circle &one, Circle &two, V &p1, V &p2){
	V d = (one.ctr - two.ctr);
	double theta = acos((two.rad - one.rad)/d.mag());
	
	d.norm();
	normToLine.set(d.x * cos(theta) - d.y * sin(theta), d.x * sin(theta) + d.y * cos(theta));
	p1 = one.ctr + normToLine * one.rad;
	p2 = two.ctr + normToLine * two.rad;
}

double fallTime(V &p1, V &p2, Circle &three){
	p1 = p1 - normToLine * three.rad;
	p2 = p2 - normToLine * three.rad;
	V prevCtr = three.ctr;
	
	double t = (three.ctr.x - p1.x)/(p2.x - p1.x);
	three.ctr = p1 + (p2 - p1) * t;
	return prevCtr.y - (p1.y + (p2.y - p1.y)*t);
}

double rollTime(V rollDir, Circle &cir, Circle &ball){
	V prevCtr = ball.ctr;
	double theta = asin((ball.rad - cir.rad)/(ball.rad + cir.rad));
	if ( ball.ctr.x < cir.ctr.x ) theta = -theta;
	V tmp(-rollDir.x * cos(theta) + rollDir.y * sin(theta), -rollDir.x * sin(theta) - rollDir.y * cos(theta));
	V newCtr = cir.ctr + tmp * (ball.rad + cir.rad);
	
//	printf("%lf %lf %lf\n", cir.ctr.x, cir.ctr.y, cir.rad);
//	tmp.showln();
//	newCtr.showln();
	return (newCtr - prevCtr).mag()/(2*pi*ball.rad);
}

int main(){
	int test, ks;
	Circle one, two, three;
	V p1, p2, rollDir;
	double res;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			one.scan();
			two.scan();
			three.scan();
			if ( one.ctr.x > two.ctr.x ){
				Circle temp = one;
				one = two;
				two = temp;
			}
			
			res = 0;
			circleTouchingLines(one, two, p1, p2);
		//	p1.showln();
		//	p2.showln();
			
			res += fallTime(p1, p2, three);
			if ( fabs(p1.y - p2.y) > EPS ){
				rollDir = (p2 - p1);
				rollDir.norm();
				if ( p1.y > p2.y ) res += rollTime(rollDir, two, three);
				else res += rollTime(-rollDir, one, three);
			}
			
			printf("Case %d: %.10lf\n", ks, res);
		}
	}
	
	return 0;
}

