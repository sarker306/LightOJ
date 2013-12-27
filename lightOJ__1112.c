#include <stdio.h>

#define SIZE 100005

long binaryIndexTree[SIZE];
long amount[SIZE];
long n;

void add ( long index, long val ){
    while ( index <= n ){
        binaryIndexTree[index] += val;
        index += index & -index;
    }
}

long total ( long index ){
    long sum = 0;
    
    while ( index ){
        sum += binaryIndexTree[index];
        index -= index & -index;
    }
    
    return sum;
}

long sumInterval ( long from, long to ){
    return total(to) - total(from - 1);
}

int main(){
    unsigned test, kase, query;
    long i, p, v, q;
    
    while ( scanf ("%u", &test ) != EOF ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld%u", &n, &query);
            for ( i = 1 ; i <= n ; i++ ){
                scanf("%ld", &amount[i]);
                add( i, amount[i] );
            }
            
            printf("Case %d:\n", kase);
            while ( query-- ){
                scanf("%ld", &p);
                switch ( p ){
                    case 1 : scanf("%ld", &p);
                             p++;
                             printf("%ld\n", amount[p]);
                             /*printf("%ld\n", sumInterval(p-1, p));*/
                             add( p, -amount[p]);
                             amount[p] = 0;
                             break; 
                    case 2 : scanf("%ld%ld", &p, &q);
                             p++;
                             add( p, q );
                             amount[p] += q;
                             break;
                    case 3 : scanf("%ld%ld", &p, &q); p++, q++;
                             printf("%ld\n", sumInterval(p, q));
                             break;
                }
            }
            
            for ( i = 1 ; i <= n ; i++ ) amount[i] = binaryIndexTree[i] = 0;
        }
    }
    
    return 0;
}
