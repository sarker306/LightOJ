#include <stdio.h>
#include <math.h>

#define EPS 1e-10

typedef struct Vector{
	double x, y;
}Vector;

void Add(Vector *c, Vector *a, Vector *b){
	c->x = a->x + b->x, c->y = a->y + b->y;
}

void Sub(Vector *c, Vector *a, Vector *b){
	c->x = a->x - b->x, c->y = a->y - b->y;
}

void MultScalar( Vector *c, Vector *a, double t ){
	c->x = a->x * t, c->y = a->y * t;
}

double Mag( Vector *a ){
	double temp;
	
	if ( fabs(a->x) < EPS ) return fabs(a->y);
	else if ( fabs(a->y) < EPS ) return fabs(a->x);
	else if ( a->x > a->y ){
		temp = a->y / a->x;
		return fabs(a->x) * sqrt( 1 + temp * temp );
	}
	else {
		temp = a->x / a->y;
		return fabs(a->y) * sqrt( 1 + temp * temp );
	}
}

double Distance(Vector *a, Vector *b){
	Vector temp;
	
	Sub(&temp, a, b);
	return Mag(&temp);
}

Vector A, B, C, D, One, Two;
double Function(double t){
	Vector temp1, temp2;

	MultScalar(&temp1, &One, t);
	Add(&temp1, &temp1, &A);
	MultScalar(&temp2, &Two, t);
	Add(&temp2, &temp2, &C);
	
	return Distance(&temp1, &temp2);
}

double MinDistance(){
	const double golden = (sqrt(5)-1)/2;
	double t0 = 0, t1 = 1, t2, t3, d;
	double f0 = Function(t0), f1 = Function(t1), f2, f3;
	
	do{
		d = golden * ( t1 - t0 );
		t2 = t0 + d;
		t3 = t1 - d;
		f2 = -Function(t2);
		f3 = -Function(t3);
		
		if ( f3 > f2 ) t1 = t2;
		else t0 = t3;
	}while ( fabs(f2 - f3) > EPS );
	
	return -(f2 + f3)/2;
}

int main(){
	int test, kase;
	
	while ( scanf("%d", &test) == 1 ){
		for ( kase = 1 ; kase <= test ; kase++ ){
			scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y, &D.x, &D.y);
			Sub(&One, &B, &A);
			Sub(&Two, &D, &C);
			
			printf("Case %d: %.10lf\n", kase, MinDistance());
		}
	}
	
	return 0;
}

