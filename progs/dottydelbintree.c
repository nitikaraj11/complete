#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
struct node 
{	int key;
	struct node* left,*right;
};
int val;
FILE* openfile;
static int gname=0;
struct node* inorder(struct node*);//Traverses tree in inorder
struct node* search(struct node*,int);//search for element to be deleted
struct node* replace(struct node*,int);//to delete & replace required node
struct node* minright(struct node*);//to find minimum of right subtree of node to be deleted
struct node* newnode(int key)//to create a new node
{	
	struct node* new1=(struct node*)malloc(sizeof(struct node*));
	new1->left=NULL;
	new1->right=NULL;
	new1->key=key;
	return new1;
}
void dotdump(NODE root, FILE *outFile)
{       gName++;
	fprintf (outFile, "digraph BST {\n",gName);
        preorderDotDump (root, outFile);
        fprintf (outFile, "}\n");
}
void preorderDotDump (NODE root, FILE* outputFile)
{        if (root != NULL)
  	 {      fprintf (outputFile, "%d [label=%d,color=black];\n",root->info, root->info);
                if (root->llink != NULL)
                       fprintf (outputFile, "%d -> %d ;\n", root->info, (root->llink)->info);
                if (root->rlink != NULL)
                        fprintf (outputFile, "%d -> %d;\n", root->info, root->rlink->info);
        //      if (root->pptr != NULL)
         //             fprintf (outputFile, "%d -> %d [style = dashed];\n", root->info, (root->pptr)->info);
                preorderDotDump (root->rlink, outputFile);
                preorderDotDump (root->llink, outputFile);
        }
}
void main()
{	
	File* pipe;
	openfile=fopen("nodes.dot","w");
	fclose(openfile);
	int key,number,i=0,j,top=0,delvalue;
	printf("\n Enter no. of nodes");
	scanf("%d",&number);
	printf("\n Enter key value for root");
	scanf("%d",&key);
	struct node* root=newnode(key);
	y:i++;
	while( i<number)
	{
		printf("\n Enter key value for %d node",i);
		scanf("%d",&key);
		struct node* new=root;
		x: if(key<new->key)
		{	if(!new->left)
			{	new->left=newnode(key);
				openfile=fopen("nodes.dot","a");
				if(openfile)
					dotdump(root,openfile);
				fclose(openfile);
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
				openfile=fopen("nodes.dot","a");
				if(openfile)
					dotdump(root,openfile);
				fclose(openfile);
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
	printf("\n Enter key to be deleted");
	scanf("%d",&delvalue);
	struct node* delnode=search(root,delvalue);
	if(!delnode)
	{	printf("\n Element not present");
		exit(0);
	}
	root=replace(root,delvalue);
//	inorder(root);
	openfile=fopen("nodes.dot","a");
	if(openfile)
		dotdump(root,openfile);
	fclose(openfile);

}
struct node* minright(struct node* delnode)
{	while(delnode->left)
	{	delnode=delnode->left;
	}
	return delnode;
}



struct node* inorder(struct node* root)
	{	
		if(root)
		{	inorder(root->left);
			printf("%d",root->key);
			inorder(root->right);
		}
	}	
	
struct node* search( struct node* root,int key)
{	int flag=0;
	struct node* temp=root;
	while(temp)
	{
		if(key=temp->key)
		{	flag=1;	
			return temp;
		}
		else if(key<temp->key)
			temp=temp->left;
		else if(key>temp->key)
			temp=temp->right;	
	}
	if (flag==0)
		return NULL;
}

struct node* replace(struct node* root,int delvalue)
{	struct node* temp;
	if(delvalue<root->key)
		replace(root->left,delvalue);
	if(delvalue>root->key)
		replace(root->right,delvalue);
	else
	{
		if(!root->left)
		{	
			temp=root->right;
			free(root);
			return temp;
		}
		if(!root->right)
		{	temp=root->left;
			free(root);
			return temp;
		}
		else
		{	temp=minright(root);
			root->key=temp->key;
			root->right=replace(root->right,temp->key);
		}
	}
	return root;
}		
