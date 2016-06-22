/*-----Red-Black creation ----*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct node
{	int key;
	struct node* left,*right,*prev;
	char color;
};

static int gName=0;
FILE* outputFile;
typedef struct node* nptr;

int verifyredblack(nptr);	//To verify if tree is correct redblack
nptr redblack(nptr,nptr);	//Balance acc. to red-black constraints
nptr rr(nptr,nptr);		//Rotates Right
nptr lr(nptr,nptr);		//Rotates Left
nptr create(nptr,int);		//Inserts newnodes & calls redblack() to balance them
nptr inorder(struct node*);	//Traverses tree -inorderly
void dotDump(nptr,FILE*);	//For each node calls preorderDotDump()
void preorderDotDump(nptr,FILE*);//Writes into dotty-file

//Function: Allocates memory to new node
//Parameter: Key value
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
	FILE *pipe;
	int key,number;
	printf("\n Enter no. of nodes");
	scanf("%d",&number);
	
		outputFile = fopen ("bst.dot", "w");

    		fclose (outputFile);
	
//	printf("\n Enter key value for root");
//	scanf("%d",&key);
	key=rand()%5000;
	nptr root=newnode(key);
	root=redblack(root,root);
	//writing to dotty-file
	outputFile = fopen ("bst.dot", "a");
	if (outputFile != NULL)     	
		//If file opens sucessfully	
		dotDump (root,  outputFile);
	fclose (outputFile);
	root=create(root,number);
	if(verifyredblack(root)>=0)
		printf("\n It is a redblack tree");
	else if(verifyredblack(root)<0)
		printf("\n It is not a redblack tree");
	
	pipe=popen("dot -Tps bst.dot -o bst.ps","w");
	pclose(pipe);	
	pipe=popen("evince bst.ps","r"); 
	pclose(pipe);

//	inorder(root);
}

//Function: Inserts newnodes -iteratively- & calls redblack() to balance them
//Parameters: Root pointer, total no. of nodes
nptr create (nptr root, int number)
{
	int key,i=0;
	y:i++;
	while( i<number)
	{
//		printf("\n Enter key value for %d node",i);
//		scanf("%d",&key);
		key=rand()%5000;
		struct node* new=root;
		x: if(key<new->key)
		   {	//If key is less than current node's value
			if(!new->left)
			   {	
				nptr temp=newnode(key);
				new->left=temp;
				temp->prev=new;
				root=redblack(root,temp);
				outputFile = fopen ("bst.dot", "a");
				if (outputFile != NULL) 
					//If file is opened sucessfully
					dotDump (root,  outputFile);
				fclose (outputFile);
				break;
			   }
			else
			{
				new=new->left;
				goto x;
		   	}
	
		   }
		else if(key>new->key)
		{	//If key is greater than current node's value		
			if(!new->right)
			   {
				nptr temp=newnode(key);
				new->right=temp;
				temp->prev=new;
				root=redblack(root,temp);
				outputFile = fopen ("bst.dot", "a");
				if (outputFile != NULL)      	
					//If file is opened sucessfully
					dotDump (root,  outputFile);
				fclose (outputFile);
				break;
			   }
			else
			   {
				new=new->right;
				goto x;
			   }
		}
		
	}if(i<number)
  	goto y;
	return root;
}

//Function: traverses tree inorderly
//Parameters: Root node to travel from
struct node* inorder(struct node* root)
{	
	if(root)
	{	//Recursive calling to traverse
		inorder(root->left);
		printf("%d\n",root->key);
		inorder(root->right);
	}
}

//Function: Balances according to red-black constraints
//Parameters: Tree root, New node inserted
nptr redblack(nptr root, nptr new)
{ 
	struct node* second=NULL;
	new->color='r';
	label:	if(new->key==root->key)
		{	//If node is root its colour should be black
			new->color='b';
			return new;
		}
	else if(new->prev->color!='b' && new->key!=root->key)
	{	//If parent's colour is red
	  	
		if(new->prev->prev->left && new->prev->prev->left->key==new->prev->key)
		{	//If parent is left child
			if(new->prev->prev->right)
				//If uncle of new-node exists recolouring and rotation
				second = new->prev->prev->right;
			if(second && second->color=='r')
			{	//Recolouring & rotating If uncle is red
				second->color='b';
				new->prev->color='b';
				new->prev->prev->color='r';
				new=new->prev->prev;
				goto label;
			}
			else if(new->prev->right && new->key==new->prev->right->key)
			{	//if new is a right child
				new=new->prev;
                                root=lr(new,root);
                                new->prev->color='b';
                                new->prev->prev->color='r';
                                root=rr(new->prev->prev,root);
                                goto label;
			}
			else if(new->prev->left && new->key==new->prev->left->key)
			{	//if new is a left child
				new=new->prev;
	                        root=rr(new,root);
        	                new->prev->color='b';
                	        new->prev->prev->color='r';
                        	root=rr(new->prev->prev,root);
	                        goto label;
			}
		}
		
		else if(new->prev->prev->right && new->prev->prev->right->key==new->prev->key)
		{	//If parent is a right child
			if(new->prev->prev->left)
				 //If uncle of new-node exists 
				second = new->prev->prev->left;
			if(second && second->color=='r')
			{	//Recolouring & rotating If uncle is red
				second->color='b';
				new->prev->color='b';
				new->prev->prev->color='r';
				new=new->prev->prev;
				goto label;
			}
			else if(new->prev->right && new->key==new->prev->right->key)
			{	//if new is a right child
                                new=new->prev;
                                root=lr(new,root);
                                new->prev->color='b';
                                new->prev->prev->color='r';
                                root=lr(new->prev->prev,root);
                                goto label;
			}
			
			else if(new->prev->left && new->key==new->prev->left->key)
			{	//if new is a left child
				new=new->prev;
                                root=rr(new,root);
                                new->prev->color='b';
                                new->prev->prev->color='r';
                                root=lr(new->prev->prev,root);
                                goto label;
			}
		}
	}
	return root;
}

//Function: Rotates Left By ex-changing subtrees
//Parameters: Node to be rotated, Tree root
nptr lr(nptr y,nptr root)
{	
        nptr temp=y->right;
        y->right=temp->left;
	if(temp->left!=NULL)
		temp->left->prev=y;
        temp->prev=y->prev;
	if(y->prev==NULL)
		//If node is root	
		root=temp;
	else if(y==y->prev->left)
		//If y is aleft child
		y->prev->left=temp;
	else if(y==y->prev->right)
		//If y is a right child
		y->prev->right=temp;
	temp->left=y;		
	y->prev=temp;
        return root;

}
//Function: Rotates right by changinf subtrees
//Parameters: Node to be rotated, Tree root
nptr rr(nptr x,nptr root)
{	
	nptr temp=x->left;
	x->left=temp->right;
	if(temp->right!=NULL)
		temp->right->prev=x;
	temp->prev=x->prev;
	if(x->prev==NULL)
		//If node is root
		root=temp;
	else if(x==x->prev->left)
		//If x is a left child
		x->prev->left=temp;
	else if(x==x->prev->right)
		//If x is a right child
		x->prev->right=temp;
	temp->right=x;
	x->prev=temp;
	return root;
}
//Function: Writes into dotty-file
//Parameters: Node to write from, File pointer to output file
void preorderDotDump (nptr root, FILE* outputFile)
{
	if (root != NULL) 
	{
		if(root->color=='b')
			fprintf (outputFile, "%d [label=%d,color=black];\n",root->key, root->key);
		else if(root->color=='r')
			 fprintf (outputFile, "%d [label=%d,color=red];\n",root->key, root->key);
		if (root->left != NULL) 
		         fprintf (outputFile, "%d -> %d ;\n", root->key, (root->left)->key);
        	if (root->right != NULL)
            		fprintf (outputFile, "%d -> %d;\n", root->key, root->right->key);
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
//Function: To verify if given tree is correctly redblack
//Parameters: Node to start checking from
int verifyredblack(nptr root)
{	int lh=0,rh=0,max=0,min=0;
	if(!(root->prev))
		//If node is root
		if (root->color=='r')
			//If root is not black
			return -1;
	if(root->color=='r')
	{	
		//If node's color is red
		if(root->left && root->left->color=='r')
			//If left child is red too
			return -1;
		else if(root->right && root->right->color=='r')
			//If right child is red too
			return -1;
	}
	if(!root->left && !root->right)
		//If node is leaf node
		return 1;	
	else if(root->left)
	{	//If node has a lleft child
		lh=verifyredblack(root->left);
		if(lh<0)
			return -1;
		else
			lh++;
	}
	else if(root->right)
	{	//If node has a right child
		rh=verifyredblack(root->right);
		if(rh<0)
			return -1;
		else rh++;
	}
	//if max height of a tree is more than 2 times min tree=> It is not a redblack tree
	max=lh>rh?lh:rh;
	min=lh<rh?lh:rh;
	if(min!=0 && max>(min*2))
		return -1;
	else 
		return max;
}
