#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFLEN 1024
#define ELEMENT_TREE_LENGTH 3

#include "AVLTree.h"

typedef struct Range
{
	int *index;
	int size;
	int capacity;
} Range;

void printFile(char *fileName)
{
	if (fileName == NULL)
		return;
	FILE *file = fopen(fileName, "r");
	if (file == NULL)
		return;
	char *buf = (char *)malloc(BUFLEN + 1);
	while (fgets(buf, BUFLEN, file) != NULL)
	{
		printf("%s", buf);
	}
	printf("\n");
	free(buf);
	fclose(file);
}

void printWordsInRangeFromFile(Range *range, char *fileName)
{
	if (fileName == NULL || range == NULL)
		return;
	FILE *file = fopen(fileName, "r");
	if (file == NULL)
		return;
	char *buf = (char *)malloc(BUFLEN + 1);
	for (int i = 0; i < range->size; i++)
	{
		fseek(file, range->index[i], SEEK_SET);
		if (fgets(buf, BUFLEN, file) != NULL)
		{
			char *token = strtok(buf, " .,\n");
			printf("%d. %s:%d\n", i + 1, token, range->index[i]);
		}
	}
	printf("\n");
	free(buf);
	fclose(file);
}

void printTreeInOrderHelper(TTree *tree, TreeNode *node)
{
	if (node != NULL)
	{
		printTreeInOrderHelper(tree, node->lt);
		TreeNode *begin = node;
		TreeNode *end = node->end->next;
		while (begin != end)
		{
			printf("%d:%s  ", *((int *)begin->info), ((char *)begin->elem));
			begin = begin->next;
		}
		printTreeInOrderHelper(tree, node->rt);
	}
}

void printTreeInOrder(TTree *tree)
{
	if (tree == NULL)
		return;
	printTreeInOrderHelper(tree, tree->root);
}

void *createStrElement(void *str)
{
	// TODO: Cerinta 2
	/* Allocate a string element to store in the tree.
	 */
	int i;
	void *string = calloc(1, ELEMENT_TREE_LENGTH);
	for (i = 0; i < ELEMENT_TREE_LENGTH; i++)
	{
		*(char *)(string + i) = *(char *)(str + i);
	}

	return string;
}

void destroyStrElement(void *elem)
{
	// TODO: Cerinta 2
	/* Free a string element.
	 */
	free((char *)elem);
}

void *createIndexInfo(void *index)
{
	// TODO: Cerinta 2
	/* Allocate space to store a new index
	 */
	int *new_index = malloc(sizeof(int));
	*new_index = *(int *)index;
	return new_index;
}

void destroyIndexInfo(void *index)
{
	// TODO: Cerinta 2
	/* Free storage space for the index.
	 */
	free((int *)index);
}

int compareStrElem(void *str1, void *str2)
{
	// TODO: Cerinta 2
	/*  0  means strings are equal 
	 * -1  means str1 < str2
	 *  1  means str1 > str2
	 */
	int compare = strcmp((char *)str1, (char *)str2);
	if (compare < 0)
		return -1;
	if (compare > 0)
		return 1;
	if (compare == 0)
		return 0;
}

TTree *buildTreeFromFile(char *fileName)
{
	// TODO: Cerinta 2
	/* Parse the text file keeping track of indices!
	 * Words separators are the following: " :.,\r\n"
	 * At each step insert the <token, index> pair in the tree.
	 */
	TTree *tree = createTree(createStrElement, destroyStrElement,
							 createIndexInfo, destroyIndexInfo, compareStrElem);

	FILE *input = fopen(fileName, "rt");
	char text[BUFLEN];
	char buffer[BUFLEN + 1];
	int index_text = 0;
	int block = -2;
	while (fgets(buffer, BUFLEN, input)) //am citit textul din fisier
	{
		strcpy(text, buffer);
	}
	int i;
	for (i = 0; i < strlen(text) - 1; i++)
	{
		int j;
		while (text[i] == ' ' || text[i] == ':' ||
			   text[i] == '.' || text[i] == ',' ||
			   text[i] == '\r' || text[i] == '\n')
		{
			i++;
		}
		if (text[i - 2] == ',' &&
			text[i - 1] == ' ')
		{
			block = i - 1;
		}
		char *str = calloc(sizeof(char), BUFLEN);
		for (j = 0;; j++)
		{
			if (text[i + j] == ' ' || text[i + j] == ':' ||
				text[i + j] == '.' || text[i + j] == ',' ||
				text[i + j] == '\r' || text[i + j] == '\n')
				break;
			str[j] = text[i + j];
		}
		if (block == i - 1 || block == 1)
		{
			i = i - 1;
			insert(tree, str, &i);
		}
		else 
		{
			insert(tree, str, &i);
		}
		if (block != -2)
		{
			i += j + 1;
			block = 1;
		}
		else
		{
			i += j;
		}
	}
	fclose(input);
	return tree;
}
void put_index(Range *range, TreeNode *node, int *index, char *q)
{
	if (node != NULL)
	{
		put_index(range, node->lt, index, q);
		TreeNode *begin = node;
		TreeNode *end = node->end->next;
		int i;
		int check = 1;
		char *string = createStrElement(begin->elem);
		for (i = 0; i < strlen(q); i++)
		{
			if (q[i] != string[i])
				check = 0;
		}
		if (check)
		{
			while (begin != end)
			{
				range->index[(*index)++] = *(int *)begin->info;
				begin = begin->next;
			}
		}
		put_index(range, node->rt, index, q);
	}
	else
	{
		return;
	}
}

Range *singleKeyRangeQuery(TTree *tree, char *q)
{
	// TODO: Cerinta 3
	/* Get the words indices begining with the patern specified by q
	 * How can do you traverse the tree?
	 * There might be duplicates, can you make use of the tree duplicate lists?
	 */
	Range *range = (Range *)malloc(sizeof(Range));
	range->capacity = 100;
	range->index = (int *)malloc(sizeof(int) * range->capacity);
	range->size = 0;
	int index = 0;
	put_index(range, tree->root, &index, q);
	range->size = index;

	return range;
}

Range *multiKeyRangeQuery(TTree *tree, char *q, char *p)
{
	// TODO: Cerinta 4
	/* Get the words indices begining with the any patern 
	 * between q and p (inclusive).
	 */
	Range *range = (Range *)calloc(1, sizeof(Range));
	range->size = 0;
	range->capacity = 100;
	range->index = (int *)malloc(sizeof(int) * range->capacity);
	int i = 0;
	char *key = calloc(sizeof(char), 10);
	strcpy(key, q);
	for (i = 0; key[0] != p[0]; i++)
	{
		Range *tmp = singleKeyRangeQuery(tree, key);
		int j;
		for (j = 0; j < tmp->size; j++)
		{
			range->index[range->size++] = tmp->index[j];
		}
		key[0] = (char)(int)(key[0] + 1);
	}
	Range *tmp = singleKeyRangeQuery(tree, p);
	int j;
	for (j = 0; j < tmp->size; j++)
	{
		range->index[range->size++] = tmp->index[j];
	}
	return range;
}

int main(void)
{

	printf("The text file:\n");
	printFile("text.txt");

	TTree *tree = buildTreeFromFile("text.txt");
	printf("Tree In Order:\n");
	printTreeInOrder(tree);
	printf("\n\n");

	printf("Single search:\n");
	Range *range = singleKeyRangeQuery(tree, "v");
	printWordsInRangeFromFile(range, "text.txt");

	printf("Multi search:\n");
	Range *range2 = multiKeyRangeQuery(tree, "j", "pr");
	printWordsInRangeFromFile(range2, "text.txt");

	if (range != NULL)
		free(range->index);
	free(range);

	if (range2 != NULL)
	free(range2->index);
	free(range2);

	destroyTree(tree);
	return 0;
}
