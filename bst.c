/* bst.c
 * Judson Cooper
 * MP5
 *
 * Purpose: This file contains the functions for creation and management
 * 	of a binary search tree. 
 *
 * Assumptions: The binary search tree will be built with a linked
 *		implementation using pointers. They will be stored based on a key
 *		with type bst_key_t.
 * 
 * Bugs: None known.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "bst.h"

// private function prototypes
int bst_debug_validate_rec(bst_node_t *N, int min, int max, int *count);
void ugly_print(bst_node_t *N, int level);
int bst_int_path_len_rec(bst_node_t *N, int level);

/* find the tree element with the matching key, if key not found return NULL.
 * 
 * treeHdr is the header block of the tree to be searched, searchKey is the
 * key for the memory block to be searched for.
 * 
 * returns pointer to data block stored in the node of the tree holding searchKey.
 */
data_t bst_access (bst_t *treeHdr, bst_key_t searchKey) {
	treeHdr->num_recent_key_comparisons = 0;
	bst_node_t *rover = treeHdr->root;
	
	// root of tree is null, nothing to search
	if (rover == NULL) {
		return NULL;
	}

	// traverse binary tree in search of node with matching key
	while (rover != NULL) {
		treeHdr->num_recent_key_comparisons++;
		if (searchKey == rover->key) {
			return rover->data_ptr;
		}
		else if (searchKey > rover->key) {
			treeHdr->num_recent_key_comparisons++;
			rover = rover->right;
		}
		else if (searchKey < rover->key) {
			treeHdr->num_recent_key_comparisons++;
			rover = rover->left;
		}
		else {
			puts("ERROR: issue comparing key for searching tree");
		}
	}

	// the key was unable to be found
	return NULL;
}

/* creates the header block for the tree. 
 *
 * tree_policy sets the policy for the tree and is saved in the header block.
 *
 * a pointer to the header block is returned.
 */
bst_t *bst_construct (int tree_policy) {
	bst_t *newTree = (bst_t*) malloc (sizeof(bst_t));
	
	// initialize info on the new tree
	newTree->root = NULL;
	newTree->tree_policy = tree_policy;
	newTree->tree_size = 0;
	newTree->num_recent_key_comparisons = 0;

	return newTree;
}

/* frees all items stored in the tree including the memory block with the
 * data, the bst_node_t struct, and the header block.
 *
 * treeHdr is the header block of the tree to be destroyed.
 */
void bst_destruct (bst_t *treeHdr) {
	// remove the root until the whole tree is gone
	while (treeHdr->root != NULL) {
		free(bst_remove(treeHdr, treeHdr->root->key));
	}
	free(treeHdr);
}

/* inserts new memory block into the tree 
 * 
 * treeHdr is header block of tree, newKey is the key corresponding to
 * the new memory block, newData is the new memory block to be added.
 * 
 * returns 0 if key already in the BST (and the data memory block is replaced).
 * returns 1 if the key not already in the BST and instead added.
 */
int bst_insert (bst_t *treeHdr, bst_key_t newKey, data_t newData) {
	treeHdr->num_recent_key_comparisons = 0;
	bst_node_t *rover = treeHdr->root;
	bst_node_t *previous = NULL;

	// nothing in tree yet, make new entry root
	if (rover == NULL) {
		bst_node_t *newNode = (bst_node_t*) malloc(sizeof(bst_node_t));
		newNode->data_ptr = newData;
		newNode->key = newKey;
		newNode->left = NULL;
		newNode->right = NULL;
		
		treeHdr->root = newNode;
		treeHdr->tree_size++;
		return 1;
	}

	// search for proper position for new node
	while (rover != NULL) {
		treeHdr->num_recent_key_comparisons++;
		if (newKey == rover->key) {
			// found identical key, update the data
			free(rover->data_ptr);
			rover->data_ptr = newData;
			return 0;
		}
		else if (newKey > rover->key) {
			treeHdr->num_recent_key_comparisons++;
			previous = rover;
			rover = rover->right;
		}
		else if (newKey < rover->key) {
			treeHdr->num_recent_key_comparisons++;
			previous = rover;
			rover = rover->left;
		}
		else {
			puts("ERROR: issue comparing key for searching tree");
		}
	}

	// didn't find exact match, so create new node for data
	bst_node_t *newNode = (bst_node_t*) malloc(sizeof(bst_node_t));
	newNode->data_ptr = newData;
	newNode->key = newKey;
	newNode->left = NULL;
	newNode->right = NULL;

	// insert under previous node pointer at appropriate position
	if (newKey > previous->key) {
		previous->right = newNode;
	}
	else {
		previous->left = newNode;
	}

	treeHdr->tree_size++;
	return 1;

}

/* removes the item in the tree with the matching key. If key not found,
 * returns NULL.
 *
 * treeHdr is the header block to the tree to be searched, removeKey is
 * the key value of the node to be removed.
 *
 * returns pointer to the data memory block of the removed node.
 */
data_t bst_remove (bst_t *treeHdr, bst_key_t removeKey) {
	treeHdr->num_recent_key_comparisons = 0;
	bst_node_t *rover = treeHdr->root;
	bst_node_t *previous = NULL;
	data_t removedData = NULL;

	// nothing in tree yet, nothing to possibly remove
	if (rover == NULL) {
		return NULL;
	}
	
	// search for the node to be removed and store in rover
	while (rover != NULL) {
		treeHdr->num_recent_key_comparisons++;
		if (removeKey == rover->key) {
			// found identical key, exit loop
			break;
		}
		else if (removeKey > rover->key) {
			treeHdr->num_recent_key_comparisons++;
			previous = rover;
			rover = rover->right;
		}
		else if (removeKey < rover->key) {
			treeHdr->num_recent_key_comparisons++;
			previous = rover;
			rover = rover->left;
		}
		else {
			puts("ERROR: issue comparing key for searching tree");
		}
	}

	// matching key was not found
	if (rover == NULL) {
		return NULL;
	}

	// this will be the same no matter the case for rover and its children
	removedData = rover->data_ptr;
	
	// node has no children
	if ((rover->left == NULL) && (rover->right == NULL)) {
		if (rover != treeHdr->root) {
			// make sure this isn't the top node first
			if (rover->key > previous->key) {
				// rover is the right child
				previous->right = NULL;
			}
			else {
				// rover is the left child
				previous->left = NULL;
			}
		}
		else {
			treeHdr->root = NULL;
		}
		free (rover); 
		rover = NULL;
	}

	// node only has right child
	else if (rover->left == NULL) {
		if (rover == treeHdr->root) {
			// put child in root if rover is root
			treeHdr->root = rover->right;
		}
		else {
			if (rover->key > previous->key) {
				// rover is the right child
				previous->right = rover->right;
			}
			else {
				// rover is the left child
				previous->left = rover->right;
			}
		}
		free (rover); 
		rover = NULL;
	}

	// node has only left child
	else if (rover->right == NULL) {
		if (rover == treeHdr->root) {
			// put child in root if rover is root
			treeHdr->root = rover->left;
		}
		else {
			if (rover->key > previous->key) {
				// rover is right child
				previous->right = rover->left;
			}
			else {
				// rover is left child
				previous->left = rover->left;
			}
		}
		free (rover); 
		rover = NULL;
	}

	// node has two children
	else {
		// find in order successor to replace the node we want to delete
		bst_node_t *inOrderSuccessor = rover->right;
		while (inOrderSuccessor->left != NULL) {
			inOrderSuccessor = inOrderSuccessor->left;
		}
		// remove inOrderSuccessor after saving its info
		bst_key_t successorKey = inOrderSuccessor->key;
		
		// save these
		int keyComps = treeHdr->num_recent_key_comparisons; 
		int realSize = treeHdr->tree_size;

		data_t successorData = bst_remove(treeHdr, inOrderSuccessor->key);
		
		// dont count above bst_remove comps, or moving of inOrderSuccessor in size
		treeHdr->num_recent_key_comparisons = keyComps; 
		treeHdr->tree_size = realSize;
		
		// update rover with info of inOrderSuccessor
		rover->data_ptr = successorData;
		rover->key = successorKey;
	}
	
	treeHdr->tree_size--;
	return removedData;
}

/* returns the number of keys in the bst.
 * 
 * treeHdr is the header block of the tree whose size is to be returned.
 *
 * returns the size of the tree.
 */
int bst_size(bst_t *treeHdr) {
	return treeHdr->tree_size;
}

/* return num_recent_key_comparisons.
 *
 * treeHdr is the header block of the tree in question.
 */
int bst_stats (bst_t *treeHdr) {
	return treeHdr->num_recent_key_comparisons;
}

/* returns internal path length of the tree
 *
 * treeHdr is header block of the tree in question.
 */
int bst_int_path_len(bst_t *treeHdr) {
	if (treeHdr->root == NULL) {
		return 0;
	}
	return bst_int_path_len_rec(treeHdr->root, 0);
}

/* function to print the a binary tree.
 * 
 * treeHdr is a pointer to the header block of the tree to be printed.
 *
 * no return value, the tree is simply printed to the terminal
 */
void bst_debug_print_tree(bst_t *treeHdr) {
	ugly_print(treeHdr->root, 0);
}

/* function to partially validate a BST.
 * 
 * T is the header block of the tree to be validated.
 */
void bst_debug_validate(bst_t *T) { 
	int size = 0; 
	assert(bst_debug_validate_rec(T->root, INT_MIN, INT_MAX, &size) == TRUE); 
	assert(size == T->tree_size); 
} 

/* supporting function for bst_debug_validate.
 *
 * N is a node of the tree, min and max are the min and max possible key
 * values, and count is the number of nodes in the tree.
 */
int bst_debug_validate_rec(bst_node_t *N, int min, int max, int *count) { 
	if (N == NULL) return TRUE; 
	if (N->key <= min || N->key >= max) return FALSE; 
	assert(N->data_ptr != NULL); 
	*count += 1; 
	return bst_debug_validate_rec(N->left, min, N->key, count) && 
	bst_debug_validate_rec(N->right, N->key, max, count); 
} 

/* prints a binary tree using the ugly print format, after called
 * by bst_debug_print_tree.
 *
 * N is the top node of the tree to be printed, level is the level
 * of N.
 *
 * no return, the tree is simply printed.
 *
 */
void ugly_print(bst_node_t *N, int level) { 
	if (N == NULL) return ; 
	ugly_print(N->right, level+1) ; 
	for (int i=0; i<level; i++) printf(" "); /* 5 spaces */ 
	printf("%5d\n", N->key); /* field width is 5 */ 
	ugly_print(N->left, level+1); 
} 

/* supporting function for bst_int_path_len.
 *
 * N is the node for which the internal path length is to be found.
 * level is the level of the current node in the tree.
 *
 * returns the internal path length of the given node.
 */
int bst_int_path_len_rec(bst_node_t *N, int level) {
	if (N == NULL) {
		// no path length if it doesn't exist
		return 0;
	}
/*	else if ((N->right == NULL) && (N->left == NULL)) {
		// no path length if there's no children
		return lenSum;
	}
*/
	int leftSum = bst_int_path_len_rec(N->left, level + 1);
	int rightSum = bst_int_path_len_rec(N->right, level + 1);

	return (leftSum + rightSum + level);
}




