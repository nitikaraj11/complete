#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
static int gName=0;
struct node
{	int key;
	struct node* left,*right,*prev;
	char color;
};
FILE* outputFile;

typedef struct node* nptr;
int verifyredblack(nptr,nptr);
nptr redblack(nptr,nptr);	//Red-Black Balancing
nptr rr(nptr,nptr);		//Right Rotation
nptr lr(nptr,nptr);		//Left Rotation
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
{	FILE *pipe;
	int key,number,i,j;
	printf("\n Enter no. of nodes");
	scanf("%d",&number);
	
		outputFile = fopen ("bst.dot", "w");

    		fclose (outputFile);

	printf("\n Enter key value for root");
	scanf("%d",&key);
	struct node* root=newnode(key);
	root=redblack(root,root);
	
		outputFile = fopen ("bst.dot", "a");

    		fclose (outputFile);
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
			
		outputFile = fopen ("bst.dot", "a");

    		fclose (outputFile);
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
		
		outputFile = fopen ("bst.dot", "a");

    		fclose (outputFile);
		   break;
	   }
	   else
	   {	new=new->right;
		   goto x;
	   }
   }
  }if(i<number)
  goto y;
	if(verifyredblack(root,root)<0)
		printf("\n Tree is not redblack balanced");
	else
		printf("\n Tree is redblack balance");
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
x:			{	if(new->prev->prev->prev)
					new->prev->prev->prev->left=rr(new->prev->prev,root);
				else	
					root=rr(new->prev->prev,root);
				new->prev->color='b';
				new->prev->right->color='r';			
			}
				else if(new->prev->key==new->prev->prev->left->key && new->key==new->prev->right->key)
			{	new->prev->prev->left=lr(new->prev,root);
				 if(new->prev->prev->prev)
                                        new->prev->prev->prev->left=rr(new->prev->prev,root);
                                else
					root=rr(new->prev,root);
				new->prev->color='b';
				new->prev->right->color='r';
			}
			else if(new->key==new->prev->right->key && new->prev->key==new->prev->prev->right->key)
y:			{	 if(new->prev->prev->prev)
                                        new->prev->prev->prev->right=lr(new->prev->prev,root);
                                else
					root=lr(new->prev->prev,root);
				new->prev->color='b';
				new->prev->left->color='r';
			}
			else if(new->prev->key==new->prev->prev->right->key && new->key==new->prev->left->key)
			{	new->prev->prev->right=rr(new->prev,root);
				 if(new->prev->prev->prev)
                                        new->prev->prev->prev->right=lr(new->prev->prev,root);
                                else
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
	temp->left=y;
	temp->prev=z->prev;	
	y->prev=temp;
	return temp;
}
nptr rr(nptr z,nptr root)
{	nptr x=z;
	nptr temp=x->left;
	x->left=temp->right;
	temp->right=x;
	temp->prev=z->prev;
	x->prev=temp;
	return temp;
}
int verifyredblack( nptr new,nptr root)
{	int leftmax,leftmin,rightmax,rightmin,max,min;
	if(!new)
		return 0;
	if(root->color!='b')
		return -1;
	if(new->color=='r')
		if(new->left->color=='r' || new->right->color=='r')
			return -1;
	if(!(new->color=='r' || new->color=='b'))
		return -1;
	if(verifyredblack(new->left,root)<0)
		return -1;
	if(verifyredblack(new->right,root)<0)
		return -1;
	max=(leftmax>rightmax?leftmax:rightmax)+1;
	min=(leftmin<rightmin?leftmin:rightmin)+1;
	if(max<-2*min)
		return 1;
	else 
		return -1;
}
	
			
void preorderDotDump (nptr root, FILE* outputFile)

{

	if (root != NULL) 

	{

		fprintf (outputFile, "%d [label=%d,color=black];\n",root->key, root->key);

		if (root->left != NULL) 

		         fprintf (outputFile, "%d -> %d ;\n", root->key, (root->left)->key);

		

        	if (root->right != NULL)

            		fprintf (outputFile, "%d -> %d;\n", root->key, root->right->key);

	//	if (root->pptr != NULL)

         //   		fprintf (outputFile, "%d -> %d [style = dashed];\n", root->key, (root->pptr)->key);

        	preorderDotDump (root->right, outputFile);

        	preorderDotDump (root->left, outputFile);

    	}

}



void dotDump(nptr root, FILE *outFile)

{

	gName++;

	fprintf (outFile, "digraph BST {\n",gName);

	

	preorderDotDump (root, outFile);

    	fprintf (outFile, "}\n");

}
