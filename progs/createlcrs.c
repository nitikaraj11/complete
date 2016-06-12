#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
struct node
{	int key;
	struct node* down, *right;
	
};
typedef struct node* nptr;
int height, side;
int search(int,nptr);
nptr newnode(int key)
{	nptr new = (struct node*)malloc(sizeof(struct node));
	new->down=NULL;
	new->right=NULL;
	new->key=key;
	return new;
}
nptr insert(int key, nptr root)
{	nptr temp=root;
	if(!temp)
	{	temp=newnode(key);
		return temp;
	}
	while(1)
	{
		if(key<temp->key && temp->down)
			temp=temp->down;
		else if(key<temp->key && !temp->down)
		{	temp->down=newnode(key);
			break;
		}
		else if(key>temp->key && temp->right)
			temp=temp->right;
		else if(key>temp->key && !temp->right)
		{	temp->right=newnode(key);
			break;
		}
	}
	return root;
}
void traverse(nptr root)
{	nptr temp=root;
	if(temp)
	{	traverse(temp->down);
		printf("\n%d\t",temp->key);
		traverse(temp->right);
	}
}
int* calcposition(int val, nptr root)
{	nptr temp=root;
	int *a={0},height=0,side=0;
	while(temp)
	{	if(val==temp->key)
		{	*a=height;
			*(a+1)=side;
			return a;
		}
		else if(val<temp->key)
		{	temp=temp->down;
			height++;
		}
		else if(val>temp->key)
		{	temp=temp->right;
			side++;
		}
	}
}
int main()
{	
	int n,i,key,val1,val2;
	int* a,*b;
	printf("\n Enter total no. of nodes");
	scanf("%d",&n);
	nptr root=NULL;
	for(i-0; i<n;i++)
	{
		printf("\nEnter no. %d key value",i+1);
		scanf("%d",&key);
		root=insert(key,root);
	}
	traverse(root);
	printf("\n Enter 2 node value to find relationship between ");
	scanf("%d%d",&val1,&val2);
	if(!(search(val1,root)&&search(val2,root)))
		printf("\n Nodes are not present in tree");
	else
	{	a=calcposition(val1,root);
		b=calcposition(val2,root);
		printf("\n %d is %d level up and %d degree away from %d sideways",val1,*a-*b,*(a+1)-*(b+1),val2);
	}
	return 0;
}
int search(int key,nptr root)
{	nptr temp=root;
	while(temp)
	{	if(key==temp->key)
			return 1;
		if(key<temp->key)
			temp=temp->down;
		else if(key>temp->key)
			temp=temp->right;
	}
	return 0;
}
		
	
		
