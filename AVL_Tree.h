// URSU OLIMPIA DENISA 314CD

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <stdlib.h>

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))
#define HEIGHT(x) ((x) ? ((x)->height) : (0))

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just assume
  some type Item was previously defined.
 */
// -----------------------------------------------------------------------------

typedef struct node
{
	void *elem;
	void *info;
	struct node *pt;
	struct node *lt;
	struct node *rt;
	struct node *next;
	struct node *prev;
	struct node *end;
	long height;
} TreeNode;

typedef struct TTree
{
	TreeNode *root;
	void *(*createElement)(void *);
	void (*destroyElement)(void *);
	void *(*createInfo)(void *);
	void (*destroyInfo)(void *);
	int (*compare)(void *, void *);
	long size;
} TTree;

TTree *createTree(void *(*createElement)(void *), void (*destroyElement)(void *),
				  void *(*createInfo)(void *), void (*destroyInfo)(void *),
				  int compare(void *, void *))
{
	// TODO: Cerinta 1
	/* 1. This tree does NOT have any sentinels!!!
	 * "root" is just a pointer to the actual root node.
	 * 
	 * 2. You must set all function pointers in the structure!!!
	 */
	TTree *newTree = (TTree *)malloc(sizeof(TTree));
	newTree->root = NULL;
	newTree->size = 0;
	newTree->createElement = createElement;
	newTree->destroyElement = destroyElement;
	newTree->createInfo = createInfo;
	newTree->destroyInfo = destroyInfo;
	newTree->compare = compare;
	return newTree;
}

TreeNode *createTreeNode(TTree *tree, void *value, void *info)
{
	// TODO: Cerinta 1
	/* Implementing and using this function
	 * will greatly improve your chances of 
	 * getting this to work.
	 */
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	newNode->elem = tree->createElement(value);
	newNode->info = tree->createInfo(info);
	newNode->next = newNode->prev = NULL;
	newNode->end = newNode;
	newNode->pt = newNode->rt = newNode->lt = NULL;
	newNode->height = 1;

	return newNode;
}

void destroyTreeNode(TTree *tree, TreeNode *node)
{
	// TODO: Cerinta 1
	/* Implementing and using this function
	 * will greatly improve your chances of 
	 * getting this to work.
	 */
	tree->destroyElement(node->elem);
	tree->destroyInfo(node->info);
	free(node);
}

int isEmpty(TTree *tree)
{
	return tree->root == NULL;
}

TreeNode *search(TTree *tree, TreeNode *x, void *elem)
{
	// TODO: Cerinta 1
	while (x != NULL)
	{
		int diff = tree->compare(elem, x->elem);
		if (diff == 0)
			return x;
		else if (diff < 0)
			x = x->lt;
		else
			x = x->rt;
	}
	return NULL;
}

TreeNode *minimum(TTree *tree, TreeNode *x)
{
	// TODO: Cerinta 1
	while (x->lt != NULL)
		x = x->lt;
	return x;
}

TreeNode *maximum(TTree *tree, TreeNode *x)
{
	// TODO: Cerinta 1
	while (x->rt != NULL)
	{
		x = x->rt;
	}
	return x;
}

TreeNode *successor(TTree *tree, TreeNode *x)
{ //de modificat
	// TODO: Cerinta 1
	if (x->rt != NULL)
		return minimum(tree, x->rt);

	while (x->pt != NULL)
	{
		if (tree->compare(x->elem, x->pt->elem) < 0)
			return x->pt;
		x = x->pt;
	}
	return NULL;
}

TreeNode *predecessor(TTree *tree, TreeNode *x)
{ //de modificat
	// TODO: Cerinta 1
	if (x->lt != NULL)
		return maximum(tree, x->lt);

	while (x->pt != NULL)
	{
		if (tree->compare(x->elem, x->pt->elem) > 0)
			return x->pt;
		x = x->pt;
	}
	return NULL;
}

void avlRotateLeft(TTree *tree, TreeNode *x)
{
	// TODO: Cerinta 1
	/* You may want to use the macros at the top of this file.
	 */
	TreeNode *root = x;
	TreeNode *y = x->rt;
	TreeNode *y_l = y->lt;

	y->lt = root;
	root->rt = y_l;
	y->pt = x->pt;

	if (x == tree->root)
		tree->root = y;
	else if (x->pt->lt == x)
		x->pt->lt = y;
	else
		x->pt->rt = y;

	x->pt = y;
	int lh = 0, rh = 0;
	if (root->lt != NULL)
		lh = root->lt->height;
	if (root->rt != NULL)
		rh = root->rt->height;
	root->height = MAX(lh, rh) + 1;
	if (y->lt != NULL)
		lh = y->lt->height;
	if (y->rt != NULL)
		rh = y->rt->height;
	y->height = MAX(lh, rh) + 1;
}

void avlRotateRight(TTree *tree, TreeNode *y)
{
	// TODO: Cerinta 1
	/* You may want to use the macros at the top of this file.
	 */
	TreeNode *root = y;
	TreeNode *x = y->lt;
	TreeNode *x_r = x->rt;

	x->rt = root;
	root->lt = x_r;
	x->pt = y->pt;

	if (y == tree->root)
		tree->root = x;
	else if (y->pt->lt == y)
		y->pt->lt = x;
	else
		y->pt->rt = x;

	y->pt = x;
	int lh = 0, rh = 0;
	if (root->lt != NULL)
		lh = root->lt->height;
	if (root->rt != NULL)
		rh = root->rt->height;
	root->height = MAX(lh, rh) + 1;
	if (x->lt != NULL)
		lh = x->lt->height;
	if (x->rt != NULL)
		rh = x->rt->height;
	x->height = MAX(lh, rh) + 1;
}

int avlGetBalance(TTree *tree, TreeNode *x)
{
	//TODO: // TODO: Cerinta 1

	/* Get AVL balance factor for node x.
	 * You may want to use the macros at the top of this file.
	 */
	if (isEmpty(tree))
		return 0;
	if (x == NULL)
		return 0;
	int lh = 0;
	int rh = 0; // left height, right height
	if (x->lt != NULL)
		lh = x->lt->height;
	if (x->rt != NULL)
		rh = x->rt->height;
	return lh - rh;
}

void avlFixUp(TTree *tree, TreeNode *y)
{
	//TODO: Cerinta 1
	/* Fix any unblance from this node to the top of tree*/
	while (y != NULL)
	{
		int balance = avlGetBalance(tree, y);

		if (balance < -1)
		{
			if (avlGetBalance(tree, y->rt) > 0)
				avlRotateRight(tree, y->rt); // caz dreapta
			avlRotateLeft(tree, y);			 // caz dreapta stanga
		}
		else if (balance > 1)
		{
			if (avlGetBalance(tree, y->lt) < 0)
				avlRotateLeft(tree, y->lt); // caz stanga
			avlRotateRight(tree, y);		// caz stanga dreapta
		}
		int lh = 0, rh = 0;
		if (y->rt != NULL)
			rh = y->rt->height;
		if (y->lt != NULL)
			lh = y->lt->height;
		y->height = MAX(rh, lh) + 1;
		y = y->pt;
	}
}

void insert(TTree *tree, void *elem, void *info)
{
	//TODO: Cerinta 1
	/*
	 * 1. Begin by implementing the normal BST insersion (no duplicates).
	 * 2. Fix any unbalance caused by this insertion as the last operation.
	 * 3. Now if this element is a duplicate all you have to do is to
	 *    inserted in the approapiate list. Inseting the duplicate at the
	 *    end of a list is easier and consistent!
	 */
	TreeNode *new_node = createTreeNode(tree, elem, info);
	TreeNode *node = tree->root;
	if (tree == NULL)
		return;
	tree->size += 1;
	TreeNode *newNode = createTreeNode(tree, elem, info);
	if (isEmpty(tree))
	{
		tree->root = newNode;
		return;
	}
	else
	{
		TreeNode *tmp = tree->root;
		TreeNode *prev = tmp;
		while (tmp != NULL)
		{
			prev = tmp;
			if (tree->compare(tmp->elem, elem) > 0)
				tmp = tmp->lt;
			else
				tmp = tmp->rt;
		}
		if (search(tree, tree->root, elem) == NULL)
		{
			if (tree->compare(prev->elem, elem) > 0)
			{
				prev->lt = newNode;
			}
			else
			{
				prev->rt = newNode;
			}
			newNode->pt = prev;

			int lh = 0, rh = 0;
			if (prev->lt != NULL)
				lh = prev->lt->height;
			if (prev->rt != NULL)
				rh = prev->rt->height;
			prev->height = MAX(lh, rh) + 1;

			prev->prev = predecessor(tree, prev); //sagetile mov
			if (predecessor(tree, prev) != NULL)
				predecessor(tree, prev)->end->next = prev;
			prev->end->next = successor(tree, prev);
			if (successor(tree, prev) != NULL)
				successor(tree, prev)->prev = prev->end;
			return;
		}
		else if (search(tree, tree->root, elem) != NULL)
		{
			prev = search(tree, tree->root, elem);
			TreeNode *test = prev;

			newNode->next = prev->end->next;
			prev->end->next = newNode;
			newNode->prev = prev->end;
			if (newNode->next != NULL)
				newNode->next->prev = newNode;
			prev->end = newNode;
		}
	}
	avlFixUp(tree, new_node);
}
void deleteHelper(TTree *tree, TreeNode *node)
{
	tree->destroyElement(node->elem);
	tree->destroyInfo(node->info);
	avlFixUp(tree, node->pt);
	free(node);
	tree->size--;
}

void delete (TTree *tree, void *elem)
{
	//TODO: Cerinta 1
	/*
	 * 1. Begin by implementing the normal BST deletion (no duplicates).
	 * 2. Fix any unbalance caused by this insertion as the last operation.
	 * 3. Now what happends if the elem you are trining to delete has duplicates?
	 *    Is it easier to delete the duplicate? Which one?
	 *    What happends to the tree-list when you delete an elem with no duplicates?
	 *    
	 */
	if (isEmpty(tree)) // daca arborele e gol
		return;
	TreeNode *t_node = search(tree, tree->root, elem);
	TreeNode *l_node = t_node->end;
	if (t_node == NULL)
		return;
	if (l_node->prev != NULL)
		l_node->prev->next = l_node->next;
	if (l_node->next != NULL)
		l_node->next->prev = l_node->prev;

	if (t_node != l_node)
	{
		t_node->end = l_node->prev;
		destroyTreeNode(tree, l_node);
		tree->size--;
		return;
	}
	else
	{
		//caz cand e un singur nod in arbore
		if (tree->root->rt == NULL &&
			tree->root->lt == NULL && tree->compare(tree->root->elem, elem) == 0)
		{
			deleteHelper(tree, tree->root);
			tree->size = 0;
			tree->root = NULL;
			return;
		}
		TreeNode *tmp = search(tree, tree->root, elem);
		TreeNode *child = NULL;
		TreeNode *change_node;
		if (tmp->lt == NULL || tmp->rt == NULL) // daca elimin un nod cu 0 copii sau 1 copil
		{
			if (tmp->lt == NULL && tmp->rt != NULL) //daca are un copil pe dreapta
			{
				child = tmp->rt;
			}
			else if (tmp->lt != NULL && tmp->rt == NULL) // daca are un copil de stanga
			{
				child = tmp->lt;
			}
			else
			{ // daca nu are niciun copil
				if (tree->compare(tmp->pt->lt->elem, elem) == 0)
					tmp->pt->lt = NULL;
				else
					tmp->pt->rt = NULL;
				deleteHelper(tree, tmp);
				return;
			}
			//daca are macar un copil o sa intre pe aici unde se actualizeaza parintii
			if (tmp->pt != NULL)
			{
				//in functie de pozitia copilului (stg/drp) se inloc. nodul dorit sa se stearga cu, copilul
				if (tmp->lt != NULL)
				{
					tmp->pt->lt = child;
				}
				else
				{
					tmp->pt->rt = child;
				}
			}
			child->pt = tmp->pt; //parintele nodului pe care il sterg o sa fie parintele copilului lui
			deleteHelper(tree, tmp);
			return;
		}
		else
		{
			// nodul are 2 copii
			change_node = minimum(tree, tmp->rt); //urmatorul nod care va inlocui nodul sters este minimul din subgraful asociat nodului
			child = change_node->rt;
			if (change_node != tmp->rt) //daca nu e fix nodul din dreapta se schimba parintele copilului
			{
				if (child != NULL)
					child->pt = change_node->pt;
				change_node->pt->lt = child;
			}

			change_node->lt = tmp->lt;
			tmp->lt->pt = change_node;
			//nodul care devine noul tmp primeste copiii lui tmp
			if (tmp->rt != change_node)
				change_node->rt = tmp->rt;

			if (change_node->rt != NULL)
				change_node->rt->pt = change_node;

			change_node->pt = tmp->pt; //parintele lui tmp devine parintele nodului nou
			if (tree->root == tmp)	 //daca tmp era chiar root, atunci nodul nou o sa fie root
				tree->root = change_node;
		}

		deleteHelper(tree, tmp);
	}
}

void destroyTree(TTree *tree)
{

	//TODO: Cerinta 1
	/* What is the easiest way to get rid of all elements for this SPECIAL tree?
	 */
	TreeNode *start = minimum(tree, tree->root);
	while (start != NULL)
	{
		TreeNode *tmp = start;
		start = start->next;
		destroyTreeNode(tree, tmp);
	}

	free(tree);
}

#endif /* AVLTREE_H_ */
