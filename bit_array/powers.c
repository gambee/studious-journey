#include <stdio.h>
#include <stdlib.h>

struct node
{
	struct node *next, *left, *right;
	unsigned int value;
	int occurs;
};

struct node* shead;
struct node* head;
struct node* root;

int add(unsigned to_add)
{
	struct node* cur;
	cur = (struct node*) malloc(sizeof(struct node));
	cur->value = to_add;
	cur->occurs = 1;
	cur->left = NULL;
	cur->right = NULL;
	cur->next = head;
	head = cur;
	return 0;
}
	
int sadd(unsigned to_add, unsigned occurs)
{
	struct node* cur;
	cur = (struct node*) malloc(sizeof(struct node));
	cur->value = to_add;
	cur->occurs = 1;
	cur->left = NULL;
	cur->right = NULL;
	cur->next = shead;
	shead = cur;
	return 0;
}
	
void rec_sort_into_tree(struct node** root, struct node* to_sort)
{
	if(*root)
	{
		if((*root)->value > to_sort->value)
			rec_sort_into_tree(&((*root)->left), to_sort);
		else if((*root)->value < to_sort->value)
			rec_sort_into_tree(&((*root)->right), to_sort);
		else ++ (*root)->occurs;
	}
	else *root = to_sort;
}

void rec_sort_into_list(struct node* root)
{
	if(root)
	{
		rec_sort_into_list(root->right);
		sadd(root->value, root->occurs);
		rec_sort_into_list(root->left);
	}
}

void sort()
{
	struct node* cur = head;

	while(cur)
	{
		rec_sort_into_tree(&root, cur);
		cur = cur->next;
	}

	rec_sort_into_list(root);
}

void rec_sort_print(struct node* root)
{
	if(root)
	{
		rec_sort_print(root->left);
		printf("%10d:%4d\n", root->value, root->occurs);
		rec_sort_print(root->right);
	}
}

void print_tree()
{
	rec_sort_print(root);
}


int print_l(struct node* list)
{
	int i = 0;
	struct node* cur = list;
	while(cur)
	{
		printf("%8u:%16u\n", i++, cur->value);
		cur = cur->next;
	}
	return i;
}

int print_list()
{
	return print_l(head);
}

int print_slist()
{
	return print_l(shead);
}
int main(void)
{
	int i, j, to_add;
	shead = NULL;
	head = NULL;
	root = NULL;

	for(i = 0; i < 0x10; i++)
	{
		for(j = 0; j < 0x10; j++)
		{
			printf("i:%3d j:%3d result:%7d\n", i, j,
				(to_add = (!j)*16*(1 << i) + (!(!j))*(!(!i))*8*(1 << i) + (!(!j))*j*(1 << (i ? (i - 1) : 0))));
			add(to_add );
		}
	}
	return 0;
}
