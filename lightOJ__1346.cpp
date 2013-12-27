#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

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
	void	show(){		printf("[%.2lf, %.2lf]",x,y);		}
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

bool operator==(V a, V b){  return fabs(a.x - b.x) < EPS && fabs(a.y - b.y) < EPS ; }
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

V Intersection( V a, V b, V c, V d ){
	b = b - a, d = d - c;
	double t, s;
	// a + t * b = c + s * d
	// t * b - s * d = c - a
	// t * bx - s * dx = cx - ax
	// t * by - s * dy = cy - ay
	
	V bb = b.unit(), dd = d.unit();
	if ( bb == dd ) return V(-1, -1);
	
	t = (c.x - a.x)*d.y - (c.y-a.y)*d.x;
	s = b.x * (c.y - a.y) - b.y * (c.x - a.x);
	t /= (b.x * d.y - b.y * d.x);
	s /= -(b.x * d.y - b.y * d.x);

	return V(t, s);
}

int Turn( V a, V b, V c ){
	b = b - a, c = c - a;
	double tmp = b * c;
	
	if ( fabs(tmp) < EPS ) return 0;
	if ( tmp < 0 ) return 1;
	else return -1;
}

int main(){
	int test;
	
	while ( cin >> test ){
		for ( int kase = 1 ; kase <= test ; kase++ ){
			int n;
			V init, next;
			double area = 0;
			
			cin >> n >> init.x;
			init.y = 0;
			
			next.scan();
			n--;
			
			V prev = next;
			while ( n-- ){
				V now;
				now.scan();
				
				if ( Turn(init, next, now) == -1 ){
					V intrsct = Intersection(init, next, prev, now);
					
					if ( intrsct.y > 1 || intrsct.y < 0 ) {
					}
					else {
						V tmp = prev + intrsct.y *( now - prev );
						area += (now - tmp).mag();

						next = now;
					}
				}
				///
				prev = now;
			}
			
			printf("Case %d: %.10lf\n", kase, area);
		}
	}

	return 0;
}

