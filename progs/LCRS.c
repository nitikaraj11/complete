#include<stdio.h>
#include<stdlib.h>

//------------------NODE STRUCTURE-----------------
struct node
{
	int key;
	struct node *left;
	struct node *right;
}*root=NULL;
//--------------------------------------------------

int lefttrav(int b,struct node* tempo,int level);
int righttrav(int b,struct node* temp2,int level);

//--------------------------------------------------
//                        CREATION
//                        ````````
void create(int c, struct node *t)
{
	int k;
	int n,i;
	printf("Enter the no. of children of %d:\n",c);
	scanf("%d",&n);
	if(n>0)
	{
		for(i=1;i<=n;i++)
		{
			printf("enter the child of %d:\n",c);
			scanf("%d",&k);
			struct node *temp=(struct node *)malloc(sizeof(struct node));
			temp->key=k;
			if(t->left==NULL)
				t->left=temp;
			else
			{
				if(t->left->right==NULL)
					t->left->right=temp;
				else
				{
					t=t->left;
					while(t->right!=NULL)
						t=t->right;
					t->right=temp;
				}
			}
			create(temp->key,temp);
		}
	}
}
//----------------------------TRAVERSAL----------------------------
void traverse(struct node *f)
{
	if(f)
	{
		printf("%d\n",f->key);
		traverse(f->left);
		traverse(f->right);
	}
}

//-------------------------LEFT TRAVERSAL---------------------------------
int lefttrav(int b,struct node* tempo,int level)
{
	if(tempo)
	{
		level++;
		if(b==tempo->key)
		{
			return level;
		}
		else if(tempo->left!=NULL)
		{
			lefttrav(b,tempo->left,level);
			righttrav(b,tempo->right,level);
			return level;
		}
		else 
		{
		righttrav(b,tempo->right,level);
                        return level;
			}

	}
}
//------------------------RIGHT TRAVERSAL----------------------------------
int righttrav(int b,struct node* temp2,int level)
{
	if(temp2)
	{
		if(b==temp2->key)
		{
			return level;
		}
		else
		{
			level++;
			return (lefttrav(b,temp2->left,level));
		}
	}
}

//---------------------------RELATION FINDER--------------------------------
int relation(int b,struct node* r, int level)
{
	int x,y;
	if(r)
	{
		if(b==r->key)
		{
			level=0;
			return level;
		}
		else if(r->left==NULL)
		{
			printf("element not found and root does not have children..\n");
			return 0;
		}
		else
		{
			level=lefttrav(b,r->left,level);
			return level;
			/*x=relation(b,r->left,++level);
			  y=relation(b,r->right,level);*/
		}
	}
}
//------------------------------MAIN------------------------------------------
int main()
{
	int key,lev1,lev2,c,d,level=0,FLAG;
	printf("Enter the root:\n");
	scanf("%d",&key);
	struct node* root=(struct node*)malloc(sizeof(struct node));
	root->key=key;
	create(root->key,root);
	printf("\n\nTraversal\n");
	traverse(root);
	while(FLAG!=0)
	{
		printf("\nEnter 2 nodes between which you want to find relation:\n");
		scanf("%d%d",&c,&d);
		lev1=relation(c,root,level);
		lev2=relation(d,root,level);
		printf("LEVEL1: %d \t LEVEL2: %d\n ",lev1,lev2);
		if(lev1>lev2)
			printf("\n%d is at a level %d greater than %d\n\n",c,(lev1-lev2),d);
		else if(lev2>lev1)
			printf("\n%d is at a level %d greater than %d\n\n",d,(lev2-lev1),c);
		else
			printf("Both are at same level:%d\n",lev1);

		printf("check again?\n");
		scanf("%d",&FLAG);
	}
	return 0;
}
