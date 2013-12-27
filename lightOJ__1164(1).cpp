#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE (1<<16)

typedef long long ll;

int min(int a, int b){ return a > b ? b : a ; }
int max(int a, int b){ return a > b ? a : b ; }

typedef struct Node{
	int upd;
	ll _sum;
	struct Node *left, *right;
}Node;

Node* Init(int left, int right){
	Node *ptr = (Node*)malloc(sizeof(Node));
	memset(ptr, 0, sizeof(Node));
	return ptr;
}

int x, y;

void update(Node *ptr, int left, int right, int val){
	int mid = ( left + right ) >> 1;

	if ( ptr->upd ){
		ptr->_sum += (right - left + 1 ) * ptr->upd;
		
		if ( left != right ){
			if ( ptr->left == 0 ) ptr->left = Init(left, mid);
			if ( ptr->right == 0 ) ptr->right = Init(mid + 1, right);

			ptr->right->upd += ptr->upd;
			ptr->left->upd += ptr->upd;
		}
		
		ptr->upd = 0;
	}

	if ( left > y || right < x ) return;

	if ( left >= x && right <= y ){
		ptr->_sum += (right - left + 1) * val;

		if ( left != right ){
			if ( ptr->left == 0 ) ptr->left = Init(left, mid);
			if ( ptr->right == 0 ) ptr->right = Init(mid + 1, right);

			ptr->right->upd += val;
			ptr->left->upd += val;
		}

		/*printf("Sum from %d to %d : %d\n", left, right, ptr->_sum);*/
		return;
	}

	if ( ptr->left == 0 ) ptr->left = Init(left, mid);
	if ( ptr->right == 0 ) ptr->right = Init(mid + 1, right);

	update(ptr->left, left, mid, val);
	update(ptr->right, mid + 1, right, val);

	ptr->_sum = ptr->left->_sum + ptr->right->_sum;
	/*printf("Sum from %d to %d : %d\n", left, right, ptr->_sum);*/
}

ll query(Node *ptr, int left, int right){
	int mid = ( left + right ) >> 1;

	if ( ptr->upd ){
		ptr->_sum += (right - left + 1 ) * ptr->upd;
		
		if ( left != right ){
			if ( ptr->left == 0 ) ptr->left = Init(left, mid);
			if ( ptr->right == 0 ) ptr->right = Init(mid + 1, right);

			ptr->right->upd += ptr->upd;
			ptr->left->upd += ptr->upd;
		}
		
		ptr->upd = 0;
	}

	if ( left > y || right < x ) return 0;

	if ( left >= x && right <= y ){
		/*printf("Sum from %d to %d : %d\n", left, right, ptr->_sum);*/
		return ptr->_sum;
	}

	if ( ptr->left == 0 ) ptr->left = Init(left, mid);
	if ( ptr->right == 0 ) ptr->right = Init(mid + 1, right);

	ll res = query(ptr->left, left, mid) + query(ptr->right, mid + 1, right);
	/*printf("Sum from %d to %d : %d\n", left, right, res);*/
	return res;
}

void clear(Node *ptr){
	if ( ptr->left ) clear(ptr->left);
	if ( ptr->right ) clear(ptr->right);
	free(ptr);
}

int main(){
	int q, test, ks;
	char com[2];
	Node *root;
	int left = 0, right = 1000000000;

	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &right, &q);
			root = Init(left, right);
			
			printf("Case %d:\n", ks);
			while ( q-- ){
				scanf("%s%d%d", com, &x, &y);
				if ( com[0] == '0'){
					int val;
					scanf("%d", &val);
					update(root, left, right, val);
				}
				else{
					printf("%lld\n", query(root, left, right));
				}
			}

			clear(root);
		}
	}

	return 0;
}

