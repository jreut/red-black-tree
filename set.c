#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum color {
	RED,
	BLACK
};

struct RBTree {
	int value;
	enum color color;
	struct RBTree* left;
	struct RBTree* right;
};

void
rbtree_new(struct RBTree **t, int v, enum color c)
{
	*t = malloc(sizeof(struct RBTree));
	if ((*t) == NULL) {
		printf("error: malloc");
		exit(EXIT_FAILURE);
	}
	(*t)->value = v;
	(*t)->color = c;
	(*t)->left = NULL;
	(*t)->right = NULL;
}

void
rbtree_free(struct RBTree *t)
{
	if (t == NULL) {
		return;
	} else {
		rbtree_free(t->left);
		rbtree_free(t->right);
		free(t);
	}
} 

void
print_rbtree(struct RBTree *t)
{

	if (t == NULL) {
		printf("Empty");
	} else {
		printf("RBTree (");
		print_rbtree(t->left);
		printf(") %d ", t->value);
		switch (t->color) {
			case RED:
				printf("RED");
				break;
			case BLACK:
				printf("BLACK");
				break;
			default:
				printf("?");
		}
		printf(" (");
		print_rbtree(t->right);
		printf(")");
	}
}

void
print_node(struct RBTree *t)
{
	if (t == NULL) {
		printf("Empty\n");
	} else {
		printf("RBTree %d ", t->value);
		switch (t->color) {
			case RED:
				printf("RED");
				break;
			case BLACK:
				printf("BLACK");
				break;
			default:
				printf("?\n");
		}
		printf("\n");
	}
}

bool
is_red(struct RBTree *t)
{
	return t != NULL && t->color == RED;
}

bool is_sorted(struct RBTree *t) {
	if (t == NULL)
		return true;
	if (t->left != NULL) {
		if (t->left->value < t->value) {
			return is_sorted(t->left);
		} else {
			return false;
		}
	}
	if (t->right != NULL) {
		if (t->right->value > t->value) {
			return is_sorted(t->right);
		} else {
			return false;
		}
	}
	return true; // left and right are empty
}


int is_balanced(struct RBTree *t) {
	if (t == NULL)
		return 0;
	if (is_red(t) && (is_red(t->left) || is_red(t->right)))
		return -1;
	int left = is_balanced(t->left);
	int right = is_balanced(t->right);
	if (left == -1 || right == -1)
		return -1;
	if (left == right)
		return is_red(t) ? left : left + 1;
	return -1;
}

bool
is_case_1(struct RBTree *t)
{
	bool p = t->color == BLACK
		&& t->left != NULL
		&& t->left->color == RED
		&& t->left->left != NULL
		&& t->left->left->color == RED;
	if (p)
		printf("case 1\n");
	return p;
}

bool
is_case_2(struct RBTree *t)
{
	bool p = t->color == BLACK
		&& t->right != NULL
		&& t->right->color == RED
		&& t->right->right != NULL
		&& t->right->right->color == RED;
	if (p)
		printf("case 2\n");
	return p;
}

bool
is_case_3(struct RBTree *t)
{
	bool p = t->color == BLACK
		&& t->left != NULL
		&& t->left->color == RED
		&& t->left->right != NULL
		&& t->left->right->color == RED;
	if (p)
		printf("case 3\n");
	return p;
}

bool
is_case_4(struct RBTree *t)
{
	bool p = t->color == BLACK
		&& t->right != NULL
		&& t->right->color == RED
		&& t->right->left != NULL
		&& t->right->left->color == RED;
	if (p)
		printf("case 4\n");
	return p;
}

void
do_it(
	struct RBTree *a,
	int xVal,
	struct RBTree *b,
	int yVal,
	struct RBTree *c,
	int zVal,
	struct RBTree *d,
	struct RBTree *newX,
	struct RBTree *newY,
	struct RBTree *newZ
     )
{
	newY->color = RED;
	newY->value = yVal;
	newY->left = newX;
	newY->right = newZ;

	newX->color = BLACK;
	newX->value = xVal;
	newX->left = a;
	newX->right = b;

	newZ->color = BLACK;
	newZ->value = zVal;
	newZ->left = c;
	newZ->right = d;
}

void
balance(struct RBTree *t)
{
	// printf("balancing: ");
	// print_node(t);
	if (t == NULL) {
		printf("balance(NULL)\n");
		return;
	}
	if (is_case_1(t)) {
		do_it(
			t->left->left->left,
			t->left->left->value,
			t->left->left->right,
			t->left->value,
			t->left->right,
			t->value,
			t->right,
			t->left->left,
			t,
			t->left
		     );
		return;
	}
	if (is_case_2(t)) {
		do_it(
			t->left,
			t->value,
			t->right->left,
			t->right->value,
			t->right->right->left,
			t->right->right->value,
			t->right->right->right,
			t->right,
			t,
			t->right->right
		     );
		return;
	}
	if (is_case_3(t)) {
		do_it(
			t->left->left,
			t->left->value,
			t->left->right->left,
			t->left->right->value,
			t->left->right->right,
			t->value,
			t->right,
			t->left,
			t,
			t->left->right
		     );
		return;
	}
	if (is_case_4(t)) {
		do_it(
			t->left,
			t->value,
			t->right->left->left,
			t->right->left->value,
			t->right->left->right,
			t->right->value,
			t->right->right,
			t->right->left,
			t,
			t->right
		     );
		return;
	}

	printf("catch-all: ");
	print_node(t);
}

void
ins(struct RBTree **t, int v)
{
	printf("ins(%d)\n", v);
	if ((*t) == NULL) {
		rbtree_new(t, v, RED);
		return;
	}

	if (v == (*t)->value) {
		return;
	} else if (v < (*t)->value) {
		ins(&((*t)->left), v);
		printf("balanced? %d\n", is_balanced(*t));
		balance(*t);
	} else {
		ins(&((*t)->right), v);
		printf("balanced? %d\n", is_balanced(*t));
		balance(*t);
	}
}

void
rbtree_insert(struct RBTree **t, int v)
{
	ins(t, v);
	(*t)->color = BLACK;
	printf("after insert(%d):\n", v);
	print_rbtree(*t);
	printf("\n");
}

int
main(int argc, char *argv[])
{
	int i;
	struct RBTree *t = NULL;
	for (i = 0; i < 10; i++)
		rbtree_insert(&t, i);
	for (i = 19; i >= 10; i--)
		rbtree_insert(&t, i);
	rbtree_insert(&t, 21);
	rbtree_insert(&t, 20);
	rbtree_insert(&t, 22);
	print_rbtree(t);
	printf("\nbalanced? %d\n", is_balanced(t));
	printf("sorted? %d", is_sorted(t));
	rbtree_free(t);
	return EXIT_SUCCESS;
}
