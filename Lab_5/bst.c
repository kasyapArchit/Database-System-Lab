#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

// Local functions
static struct BST_Node *moveLeftNode( struct BST_Node *root);
static int place_bst_node( struct BST_Node *parent, struct BST_Node *node );
static struct BST_Node *make_bst_node( int key, void *data );
// Root's pointer is passed because root can get modified for the first node
int bst_add_node( struct BST_Node **root, int key, void *data )
{
	struct BST_Node *newnode = NULL;
	struct BST_Node *parent = NULL;
	struct BST_Node *retnode = NULL;
	int status = 0;

	newnode = make_bst_node( key, data);
	if( *root == NULL ){
		*root = newnode;
		status = BST_SUCCESS;
	}
	else{
		status = place_bst_node( *root, newnode );
	}
	return status;
}

struct BST_Node *bst_search( struct BST_Node *root, int key )
{
	struct BST_Node *retval = NULL;
	if(root==NULL){
		return root;
	}
	if(root->key==key){
		retval = root;
	}
	else if(root->key>key){
		retval= bst_search(root->left_child,key);
	}
	else{
		retval= bst_search(root->right_child,key);
	}
	return retval;
}
void bst_print( struct BST_Node *root )
{
	if( root == NULL )
		return;
	else{
		printf("%d ", root->key);
		bst_print( root->left_child );
		bst_print( root->right_child );
	}
}

void bst_free( struct BST_Node *root )
{
	if( root == NULL )
		return;
	else{
		bst_free( root->left_child );
		bst_free( root->right_child );
		free(root);
	}
}

static int place_bst_node( struct BST_Node *parent, struct BST_Node *node ){
	int retstatus;

	if( parent == NULL ){
		return BST_NULL;
	}
	else if( node->key == parent->key ){
		return BST_DUP_KEY;
	}
	else if( node->key < parent->key ){
		if(parent->left_child==NULL){
			parent->left_child=node;
			retstatus=BST_SUCCESS;
			return retstatus;
		}
		return place_bst_node(parent->left_child,node);
	}
	else if( node->key > parent->key ){
		if(parent->right_child==NULL){
			parent->right_child=node;
			retstatus=BST_SUCCESS;
			return retstatus;
		}
		return place_bst_node(parent->right_child,node);
	}
	return BST_NULL;
}
struct BST_Node * minValueNode(struct BST_Node* node)
{
    struct BST_Node* current = node;
    while (current->left_child != NULL)
        current = current->left_child;
    return current;
}
void bst_delete( struct BST_Node **root, int key )
{
	if ((*root)->key == key) {
		// if root itself has the key then delete it, make the left node(biggest node smaller than root) as the root. If it
		// doesn't exist then make the right child as the root.
		struct BST_Node *node = moveLeftNode(*root);
		if (node != NULL) {
			node->right_child = (*root)->right_child;
			if(node != (*root)->left_child)
				node->left_child = (*root)->left_child;
			(*root) = node;
		} else {
			(*root) = (*root)->right_child;
		}
	}
	else {
		while((*root) != NULL) {
			// Since there is no reverse mapping we stay at root and look at if its child has the key
			if ((*root)->left_child != NULL && (*root)->left_child->key == key) {
				// here the we check if the left child has the key, if yes then call the node whose key is biggest smaller to its key
				struct BST_Node *node = moveLeftNode((*root)->left_child);
				if (node != NULL) {
					node->right_child = (*root)->left_child->right_child;
					if(node->left_child != (*root)->left_child->left_child)
						node->left_child = (*root)->left_child->left_child;
					(*root)->left_child = node;
				} else {
					(*root)->left_child = (*root)->left_child->right_child;
				}
				break;
			} else if ((*root)->right_child != NULL && (*root)->right_child->key == key) {
				// here the we check if the right child has the key, if yes then call the node whose key is biggest smaller to its key
				struct BST_Node *node = moveLeftNode((*root)->right_child);
				if (node != NULL) {
					node->right_child = (*root)->right_child->right_child;
					if(node->left_child != (*root)->right_child->left_child)
						node->left_child = (*root)->right_child->left_child;
					(*root)->right_child = node;
				} else {
					(*root)->right_child = (*root)->right_child->right_child;
				}
				break;
			} else {
				// here we continue our traversal in search for the key
				if ((*root)->key < key)
					(*root) = (*root)->right_child;
				else
					*root = (*root)->left_child;
			}
		}
	}
}
static struct BST_Node *moveLeftNode( struct BST_Node *root)
{
	if (root == NULL || root->left_child == NULL)
		return NULL;

	root = root->left_child;

	struct BST_Node *prevNode = NULL;
	while(root->right_child != NULL) {
		prevNode = root;
		root = root->right_child;
	}

	// remove the right most node's parent
	if (prevNode != NULL)
		prevNode->right_child = NULL;

	return root;
}
static struct BST_Node *make_bst_node( int key, void *data )
{
	struct BST_Node *newnode;
	newnode = (struct BST_Node *) malloc(sizeof(struct BST_Node));
	newnode->key = key;
	newnode->data = data;
	newnode->left_child = NULL;
	newnode->right_child = NULL;

	return newnode;
}
