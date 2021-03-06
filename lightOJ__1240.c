#include <stdio.h>
#include <math.h>

#define EPS 1e-12

typedef struct Vector{
	double x, y, z;
}Vector;

void Add(Vector *c, Vector *a, Vector *b){
	c->x = a->x + b->x, c->y = a->y + b->y, c->z = a->z + b->z;
}

void Sub(Vector *c, Vector *a, Vector *b){
	c->x = a->x - b->x, c->y = a->y - b->y, c->z = a->z - b->z;
}

void MultScalar( Vector *c, Vector *a, double t ){
	c->x = a->x * t, c->y = a->y * t, c->z = a->z * t;
}

double Mag( Vector *a ){
	double temp;

	return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

double Distance(Vector *a, Vector *b){
	Vector temp;

	Sub(&temp, a, b);
	return Mag(&temp);
}

Vector A, B, One, P;
double Function(double t){
	Vector temp1;

	MultScalar(&temp1, &One, t);
	Add(&temp1, &temp1, &A);

	return Distance(&temp1, &P);
}

double MinDistance(){
	const double golden = (sqrt(5)-1)/2;
	double t0 = 0, t1 = 1, t2, t3, d;
	double f0 = Function(t0), f1 = Function(t1), f2, f3;

	do{
		d = golden * ( t1 - t0 );
		t2 = t0 + d;
		t3 = t1 - d;
		f2 = Function(t2);
		f3 = Function(t3);

		if ( f3 < f2 ) t1 = t2;
		else t0 = t3;
	}while ( fabs(t2 - t3) > EPS );

	return (f2 + f3)/2;
}

int main(){
	int test, kase;

	while ( scanf("%d", &test) == 1 ){
		for ( kase = 1 ; kase <= test ; kase++ ){
			scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf", &A.x, &A.y, &A.z, &B.x, &B.y, &B.z, &P.x, &P.y, &P.z);
			Sub(&One, &B, &A);

			printf("Case %d: %.10lf\n", kase, MinDistance());
		}
	}

	return 0;
}

