#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
struct node 
{	int key;
	struct node* left,*right;
};
struct node* inorder(struct node*);
struct node* newnode(int key)
{	
	struct node* new1=(struct node*)malloc(sizeof(struct node*));
	new1->left=NULL;
	new1->right=NULL;
	new1->key=key;
	return new1;
}
void main()
{	
	int key,number,i,j;
	printf("\n Enter no. of nodes");
	scanf("%d",&number);
	printf("\n Enter key value for root");
	scanf("%d",&key);
	struct node* root=newnode(key);
//	struct node* temp=root;
	
	y:i++;
	while( i<number)
	{
		printf("\n Enter key value for %d node",i);
		scanf("%d",&key);
		struct node* new=root;
		x: if(key<new->key)
		{	if(!new->left)
			{	new->left=newnode(key);
				break;
			}
			else
			{	new=new->left;
				goto x;
			}
		}
		else if(key>new->key)
		{	if(!new->right)
			{	new->right=newnode(key);
				break;
			}
			else
			{	new=new->right;
				goto x;
			}
		}
	 }if(i<number)
		goto y;
	inorder(root);
}
struct node* inorder(struct node* root)
{	
	if(root)
	{	inorder(root->left);
		printf("%d",root->key);
		inorder(root->right);
	}
}	
	
