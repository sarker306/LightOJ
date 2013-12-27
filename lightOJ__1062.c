#include<stdio.h>
#include<math.h>

double x, y, c, p, diff;

int main(){
    double m, d, prevd;
    char flag;
    int test, kase;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%lf%lf%lf", &x, &y, &c);
            if(x>y) { p=x; x=y; y=p;}
            if(fabs(x-y)>1e-8) for(d=0; ;){
                prevd=d;
                p=sqrt(y*y-x*x+d*d);
                d=(p*c)/(p-c);
                if(fabs(d-prevd)<1e-8) break;
            }
            else d=2*c;
            
            d=sqrt(x*x-d*d);
            printf("Case %d: %.10lf\n", kase, d);
        }
    }
    
    return 0;
}
