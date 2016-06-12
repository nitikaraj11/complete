#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct node
{	int key;
	struct node* left,*right,*prev;
	char color;
};
typedef struct node* nptr;
nptr redblack(nptr,nptr);
nptr rr(nptr,nptr);
nptr lr(nptr,nptr);
struct node* inorder(struct node*);
struct node* newnode(int key)
{	
	struct node* new1=(struct node*)malloc(sizeof(struct node));
	new1->left=NULL;
	new1->right=NULL;
	new1->prev=NULL;
	new1->key=key;
	new1->color='r';
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
	root=redblack(root,root);
y:i++;
  while( i<number)
  {
	  printf("\n Enter key value for %d node",i);
	  scanf("%d",&key);
	  struct node* new=root;
x: if(key<new->key)
   {	if(!new->left)
	   {	nptr temp=newnode(key);
		new->left=temp;
		   temp->prev=new;
		   root=redblack(root,temp);
		   break;
	   }
	   else
	   {	new=new->left;
		   goto x;
	   }
   }
   else if(key>new->key)
   {	if(!new->right)
	   {	nptr temp=newnode(key);
		new->right=temp;
		   temp->prev=new;
		   root=redblack(root,temp);
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

nptr redblack(nptr root, nptr new)
{ 
	struct node* second=NULL;
	new->color='r';
label:	if(new->key==root->key)
	{   new->color='b';
		return new;
	}
	else if(new->prev->color!='b' && new->key!=root->key)
	{	if(!new->prev->prev->left)
			goto y;
	  	if(new->prev->prev->left->key==new->prev->key)
		{	if(new->prev->prev->right)
				second = new->prev->prev->right;
			else
				goto x;
		}
		if(!new->prev->prev->right)
			goto x;
		else if(new->prev->prev->right->key==new->prev->key)
		{	if(new->prev->prev->left)
				second = new->prev->prev->left;
			else
				goto y;
		}
		if(second->color=='r')
		{	second->color='b';
			new->prev->color='b';
			new->prev->prev->color='r';
			new=new->prev->prev;
			goto label;
		}
		else if(second->color=='b')
		{	if(new->key==new->prev->left->key && new->prev->key==new->prev->prev->left->key)
x:			{	root=rr(new->prev->prev,root);
				new->prev->color='b';
				new->prev->right->color='r';			
			}
				else if(new->prev->key==new->prev->prev->left->color && new->key==new->prev->right->key)
			{	root=lr(new->prev,root);
				root=rr(new->prev,root);
				new->prev->color='b';
				new->prev->right->color='r';
			}
			else if(new->key==new->prev->right->key && new->prev->key==new->prev->prev->right->key)
y:			{	root=lr(new->prev->prev,root);
				new->prev->color='b';
				new->prev->left->color='r';
			}
			else if(new->prev->key==new->prev->prev->right->key && new->key==new->prev->left->key)
			{	root=rr(new->prev,root);
				root=lr(new->prev,root);
				new->prev->color='b';
				new->prev->right->color='r';			
			}
		}
	}
	return root;
}

nptr lr(nptr z,nptr root)
{	nptr y=z;	
	nptr temp=y->right;
	y->right=temp->left;
	temp->prev=y->prev;
	temp->left=y;
	y->prev=temp;
	return root;
}
nptr rr(nptr z,nptr root)
{	nptr x=z;
	nptr temp=x->left;
	x->left=temp->right;
	temp->prev=x->prev;
	temp->right=x;
	x->prev=temp;
	return root;
}

