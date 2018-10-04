#ifndef BST_H
#define BST_H

struct BST_Node{
	struct BST_Node *left_child;
	struct BST_Node *right_child;
	int key;
	void *data;
};

struct BST_Node *bst_search( struct BST_Node *root, int key );
int bst_add_node( struct BST_Node **root, int key, void *data );
void bst_delete( struct BST_Node **root, int key );
void bst_print( struct BST_Node *root );
void bst_free( struct BST_Node *root );

#define BST_SUCCESS 0
#define BST_DUP_KEY 1
#define BST_NULL 2

#endif
