#include <stdio.h>
#include <stdlib.h>

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
		printf("RBTree %d %d (", t->value, t->color);
		print_rbtree(t->left);
		printf(") (");
		print_rbtree(t->right);
		printf(")");
	}
}

void
balance(struct RBTree *t)
{
	if (t == NULL) {
		printf("balance(NULL)\n");
		return;
	}
	if (t->color != BLACK) {
		printf("balance({ .color = RED })\n");
		return;
	}
	if (t->left != NULL
		&& t->left->color == RED
		&& t->left->left != NULL
		&& t->left->left->color == RED
		) {
		struct RBTree *a = t->left->left->left;
		struct RBTree *b = t->left->left->right;
		struct RBTree *c = t->left->right;
		struct RBTree *d = t->right;
		int x = t->left->left->value;
		int y = t->left->value;
		int z = t->value;
	}
	if (t->right != NULL) {
	}
}

void
ins(struct RBTree **t, int v)
{
	if ((*t) == NULL) {
		rbtree_new(t, v, RED);
		return;
	}

	if (v == (*t)->value) {
		return;
	} else if (v < (*t)->value) {
		ins(&((*t)->left), v);
	} else {
		ins(&((*t)->right), v);
	}
}


int
main(int argc, char *argv[])
{
	struct RBTree *t = NULL;
	ins(&t, 42);
	ins(&t, 43);
	ins(&t, 0);
	print_rbtree(t);
	rbtree_free(t);
	return EXIT_SUCCESS;
}
