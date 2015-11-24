// Ofure Ukpebor
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct listnode
{
	int key;
	struct listnode * next;
} ListNode;

int findListLength(ListNode *list) //returns length of list
{
	int counter = 0;
	for (; list != NULL; list = list->next)
	{
		++counter;
	}
	return counter;
}

ListNode *findRandomPivotNode(ListNode *head_node) //finds pivot node in list
{
	int list_length = findListLength(head_node);
	int pivot_position = rand() % list_length; 

	for (int count = 0; count < pivot_position; count++)
	{
		head_node = head_node->next;
	}
	return head_node;
}

ListNode * findLastNode(ListNode * current_node)
{
	for (; current_node->next != NULL; current_node = current_node->next);
	return current_node;
}

ListNode * join(ListNode* left_list, ListNode * pivot, ListNode * right_list)
{
	pivot->next = right_list;

	if (left_list == NULL)	return pivot;

	ListNode * left_tail = findLastNode(left_list);
	left_tail->next = pivot;

	return left_list;
}

ListNode * sort(ListNode * list)
{
	if (list == NULL || list->next == NULL) return list;

    ListNode *pivot = findRandomPivotNode(list);

	ListNode *left_sub_list = NULL, *right_sub_list = NULL;

	for (ListNode * current_node = list; current_node != NULL;)
	{
		ListNode * next_node = current_node->next;

		if (current_node != pivot)
		{
			if (current_node->key <= pivot->key)
			{
				current_node->next = left_sub_list;
				left_sub_list = current_node;
			}
			else
			{
				current_node->next = right_sub_list;
				right_sub_list = current_node;
			}
		}
		current_node = next_node;
	}

	return join(sort(left_sub_list), pivot, sort(right_sub_list));
}

int main(void)
{
	long i;
	struct listnode *node, *space;
	//create a linked list of 500000 items
	space = (struct listnode *)malloc(500000 * sizeof(struct listnode));
	for (i = 0; i < 500000; i++)
	{
		(space + i)->key = 2 * ((17 * i) % 500000);
		(space + i)->next = space + (i + 1);
	}
	(space + 499999)->next = NULL;
	node = space;
	//printList(node);
	printf("\n prepared list, now starting sort\n");
	node = sort(node);
	//printList(node);
	printf("\n checking sorted list\n");
	for (i = 0; i < 500000; i++)
	{
		if (node == NULL)
		{
			printf("List ended early\n"); exit(0);
		}
		if (node->key != 2 * i)
		{
			printf("Node contains wrong value\n"); exit(0);
		}
		node = node->next;
	}
	printf("Sort successful\n");
	exit(0);
}
