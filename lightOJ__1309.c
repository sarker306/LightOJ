#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define ID 0
#define NUM 1
#define DELIM 2
#define END 3

char *prog;
char token[20], tokenType;

typedef struct Polynomial{
	int degree;
	long long arr[100];
}Polynomial;

void printPolynomial ( Polynomial *poly ){
	int i;
	
	for ( i = 0 ; i <= poly->degree ; i++ ) printf("%lld ", poly->arr[i]);
	puts("");
}

int isdelim(char ch){
	if (strchr("+-*=()", ch)) return 1;
	return 0;
}

void putback(){
	prog -= strlen(token);
}

void getToken(){
	int i = 0;
	
	while ( isspace(*prog++) );
	prog--;
	
	if ( *prog == 0 ){
		tokenType = END;
		token[i++] = 0;
	}
	else if ( isdelim(*prog) ){
		tokenType = DELIM;
		token[i++] = *prog++;
	}
	else if ( isalpha(*prog) ){
		tokenType = ID;
		token[i++] = *prog++;
	}
	else if ( isdigit(*prog) ){
		tokenType = NUM;
		while ( isdigit(*prog) ) token[i++] = *prog++;
	}
	
	token[i] = 0;
}

void Number(Polynomial *res){
	memset(res, 0, sizeof(res));
	res->degree = 0;
	sscanf(token, "%lld", &res->arr[0]);
}

void Expression(Polynomial*);

void Factor(Polynomial *res){
	getToken();

	if ( tokenType == DELIM ){
		Expression(res);
		getToken();
	}
	else if ( tokenType == ID ){
		memset(res, 0, sizeof(res));
		res->degree = 1;
		res->arr[1] = 1;
	}
	else if ( tokenType == NUM ) Number(res);
}

void Term1(Polynomial *res){
	Polynomial temp, temp2;
	int i, j;
	memset(&temp, 0, sizeof(temp));
	memset(&temp2, 0, sizeof(temp2));

	getToken();
	switch( *token ){
		case '*' : 	Factor(&temp);
					for ( i = 0 ; i <= res->degree ; i++ )
						for ( j = 0 ; j <= temp.degree ; j++ )
							temp2.arr[i+j] += res->arr[i] * temp.arr[j];
					res->degree += temp.degree;
					for ( i = 0 ; i <= res->degree ; i++ ) res->arr[i] = temp2.arr[i];
					Term1(res);
					break;
		default :   putback();
	}
}

void Term(Polynomial *res){
	Factor(res);
	Term1(res);
}

void Expression1(Polynomial *res){
	int i, max;
	Polynomial temp;
	memset(&temp, 0, sizeof(temp));
	temp.degree = 0, temp.arr[0] = 0;

	getToken();
	
	switch ( *token ){
		case '+' : 	Term(&temp);
					res->degree = max = temp.degree > res->degree ? temp.degree : res->degree;
					for ( i = 0 ; i <= max ; i++ ) res->arr[i] += temp.arr[i];
					Expression1(res);
					break;
		case '-' : 	Term(&temp);
					res->degree = max = temp.degree > res->degree ? temp.degree : res->degree;
					for ( i = 0 ; i <= max ; i++ ) res->arr[i] -= temp.arr[i];
					Expression1(res);
					break;
		default  :  putback();
					break;
	}
}

void Expression(Polynomial *res){
	Term(res);
	Expression1(res);
}

long long gcd ( long long x, long long y ){
	long long temp;
	
	while ( y ) {
		temp = x;
		x = y;
		y = temp % y;
	}
	
	return x;
}

void Equation(){
	long long temp, a, b;
	Polynomial res, res1;
	char flag;
	
	memset(&res1, 0, sizeof(res1));
	memset(&res, 0, sizeof(res));
	Expression(&res);
	getToken();
	Expression(&res1);

	/* Assuming res1.degree or res.degree both <= 1 */
	
	if ( res.arr[1] == res1.arr[1] || (res.degree == 0 && res1.degree == 0)){
		printf(res.arr[0] == res1.arr[0] ? "infinitely many solutions" : "no solution");
	}
	else{
		a = res1.arr[0] - res.arr[0];

		if ( res.degree == 0 ) b = -res1.arr[1];
		else if ( res1.degree == 0 ) b = res.arr[1];
		else b = res.arr[1] - res1.arr[1];
		
		if ( a * 1.0 / b < 0 ) flag = 1;
		else flag = 0;
		
		if ( a < 0 ) a = -a;
		if ( b < 0 ) b = -b;
		temp = gcd(a, b);
		a /= temp, b /= temp;

		if ( flag ) putchar('-');
		if ( b == 1 ) printf("%lld", a);
		else printf("%lld/%lld", a, b);
	}
}

int main(){
	char input[105];
	int test, kase;

	gets(input);
	sscanf(input,"%d", &test);
	
	for ( kase = 1 ; kase <= test ; kase++ ) {
		gets(input);
		printf("Case %d: ", kase);
		prog = input;
		Equation();
		puts("");
	}
	
	return 0;
}

