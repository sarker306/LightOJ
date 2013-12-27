#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ID 1
#define DELIM 2

void Expression(char *);
void Expression1(char *);
void Term(char *);
void Term1(char *);
void Factor(char *);
void Sub(char *);
void Var(char *);

int mask;
char varPos[10] = { 0,1,2,3,4,5,6,7,8,9 };
char *prog;

int main(){
	char input1[105], input2[105], res1, res2;
	int test, kase, MAX = 1024;
	
	while ( scanf("%d", &test) == 1 ){
		getchar();
		for ( kase = 1 ; kase <= test ; kase++ ){
			gets(input1);
			gets(input2);
			
			printf("Case %d: ", kase);
			for ( mask = 0 ; mask < MAX ; mask++ ){
				prog = input1;
				Expression(&res1);
				prog = input2;
				Expression(&res2);
				if ( res1 != res2 ) break;
			}
			
			printf("%sEquivalent\n", mask == MAX ? "" : "Not ");
		}
	}
	
	return 0;
}

char token, tokenType;

void putBack(){ prog--; }

void getToken(){
	token = *prog++;
	
	if ( isalpha(token) ) tokenType = ID;
	else tokenType = DELIM;
}

void Expression(char *res){
	Term(res);
	Expression1(res);
}

void Expression1(char *res){
	char temp;
	
	getToken();
	if ( token == '|' ){
		Term(&temp);
		*res |= temp;
		Expression1(res);
	}
	else putBack();
}

void Term(char *res){
	Factor(res);
	Term1(res);
}

void Term1(char *res){
	char temp;
	
	getToken();
	if ( token == '&' ){
		Factor(&temp);
		*res &= temp;
		Term1(res);
	}
	else putBack();
}

void Factor(char *res){
	getToken();
	if ( token == '!' ){
		Factor(res);
		*res = !*res;
	}
	else{
		putBack();
		Sub(res);
	}
}

void Sub(char *res){
	getToken();
	if ( tokenType == ID ){
		*res = (mask & (1<<(token - 'a')))>>(token - 'a');
	}
	else{
		Expression(res);
		getToken();
	}
}


