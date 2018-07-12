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
		printf(")\n");
	}
}

int
main(int argc, char *argv[])
{
	struct RBTree *t;
	rbtree_new(&t, 42, RED);
	print_rbtree(t);
	rbtree_free(t);
	print_rbtree(t);
	return EXIT_SUCCESS;
}
