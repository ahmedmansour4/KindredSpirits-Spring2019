// Name: Ahmed Mansour
// COP3502, Spring 2019
// NID: ah505081

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

// This struct creates a singly linked list.
typedef struct linkedNode
{
	int data;
	struct linkedNode *next;
}	linkedNode;

// Checks if first binary tree is a reflection of the second binary tree.
int isReflection(node *a, node *b)
{
	if(a == NULL && b == NULL)
	{
		return 1;
	}
	else if(a == NULL || b == NULL)
		return 0;
	
	// If structures of first and second tree are mirrored and data 
	// in each node is the same, then they are reflections.
	if(isReflection(a->right, b->left) && isReflection(a->left, b->right) && a->data == b->data)
		return 1;
	
	return 0;
}

// This function creates a new binary tree that is a mirror of the passed in tree. 
node *makeReflection(node *root)
{
	node *temp = malloc(sizeof(node));
	
	if(root == NULL)
	{
		free(temp);
		return NULL;
	}
		
	temp->data = root->data;
	// Set new binary tree right node to left node of passed tree.
	temp->right = makeReflection(root->left);
	// Set new binary tree left node to right node of passed tree.
	temp->left = makeReflection(root->right);
	
	return temp;
}

// Helper function that inserts a node into the head of a linked list.
linkedNode *insertNode(int data, linkedNode *head)
{
	linkedNode *temp = malloc(sizeof(linkedNode));
	temp->data = data;
	temp->next = head;
	head = temp;
	return temp;
}

// Helper function that returns a linked list that is the reversed post order of the tree.
linkedNode *getPostorder(node *root, linkedNode *head)
{
	if(root == NULL)
		return head;
	
	// Recursive call on left subtree.
	head = getPostorder(root->left, head);
	// Recursive call on right subtree.
	head = getPostorder(root->right, head);
	// insert the current node's data into a linked list.
	head = insertNode(root->data, head);
	
	return head;
}
// Helper function that returns a linked list that is the reversed preorder of the tree.
linkedNode *getPreorder(node *root, linkedNode *head)
{
	if(root == NULL)
		return head;
	
	// insert the current node's data into a linked list.
	head = insertNode(root->data, head);
	// Recursive call on left subtree.
	head = getPreorder(root->left, head);
	// Recursive call on right subtree.
	head = getPreorder(root->right, head);
	
	return head;
}


// Helper function that compares each node of two linked lists to see if they match.
int compareLinkedLists(linkedNode *headA, linkedNode *headB)
{
	linkedNode *tempA = malloc(sizeof(linkedNode));
	linkedNode *tempB = malloc(sizeof(linkedNode));
	
	// If both linked lists are NULL then they are equal.
	if(headA == NULL && headB == NULL)
	{
		free(tempA);
		free(tempB);
		return 1;
	}
	// If one linked list head exists and the other doesn't, then they are not equal.
	if(headA == NULL || headB == NULL)
	{
		free(tempA);
		free(tempB);
		return 0;
	}
		
	tempA = headA;
	tempB = headB;
	
	while(tempA != NULL || tempB != NULL)
	{
		if(tempA->data != tempB->data)
		{
			free(tempA);
			free(tempB);
			return 0;
		}
			
		tempA = tempA->next;
		tempB = tempB->next;
	}
	free(tempA);
	free(tempB);
	return 1;
}

// Function that checks if the preorder of one binary tree is the post order of the other binary tree.
int kindredSpirits(node *a, node *b)
{
	linkedNode *headA = malloc(sizeof(linkedNode));
	linkedNode *headB = malloc(sizeof(linkedNode));
	linkedNode *headC = malloc(sizeof(linkedNode));
	linkedNode *headD = malloc(sizeof(linkedNode));
	
	if(a == NULL && b == NULL)
		return 1;
	if(a == NULL || b == NULL)
		return 0;
	
	int compareAB, compareCD;
	// Both permutations of post order and preorder for the two binary trees are checked.
	headA = getPreorder(a, headA);
	headB = getPostorder(b, headB);
	headC = getPostorder(a, headC);
	headD = getPreorder(b, headD);
	compareAB = compareLinkedLists(headA, headB);
	compareCD = compareLinkedLists(headC, headD);
	
	// If either permutations returned 1, then the two trees are kindred spirits.
	return compareAB || compareCD;
}

double difficultyRating(void)
{
	return 4.0;
}

double hoursSpent(void)
{
	return 18.0;
}
