#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
struct node 
{	int key;
	struct node* left,*right;
};
//typedef struct node* NODE;
static int gName=0;
struct node* inorder(struct node*);
struct node* newnode(int key)
{	
	struct node* new1=(struct node*)malloc(sizeof(struct node*));
	new1->left=NULL;
	new1->right=NULL;
	new1->key=key;
	return new1;
}
void preorderDotDump (struct node* root, FILE* outputFile)

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
void dotDump(struct node* root, FILE *outFile)

{

	gName++;

	fprintf (outFile, "digraph BST {\n",gName);

	

	preorderDotDump (root, outFile);

    	fprintf (outFile, "}\n");

}

FILE *outputFile;




void main()
{	
	FILE * pipe;
	int key,number,i,j;
	outputFile = fopen ("bst.dot", "w");

    		fclose (outputFile);
	printf("\n Enter no. of nodes");
	scanf("%d",&number);
	printf("\n Enter key value for root");
	scanf("%d",&key);
	struct node* root=newnode(key);
	outputFile = fopen ("bst.dot", "a");

			if (outputFile != NULL) 

			{

					        	

				dotDump (root,  outputFile);

			}

			fclose (outputFile);
	
	y:i++;
	while( i<number)
	{
		printf("\n Enter key value for %d node",i);
		scanf("%d",&key);
		struct node* new=root;
		x: if(key<new->key)
		{	if(!new->left)
			{	new->left=newnode(key);
				outputFile = fopen ("bst.dot", "a");

			if (outputFile != NULL) 

			{

					        	

				dotDump (root,  outputFile);

			}

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
			{	new->right=newnode(key);
				outputFile = fopen ("bst.dot", "a");

			if (outputFile != NULL) 

			{

					        	

				dotDump (root,  outputFile);

			}

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
	
					pipe=popen("dot -Tps bst.dot -o bst.ps","w");

					pclose(pipe);	

					pipe=popen("evince bst.ps","r"); 

					pclose(pipe);

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
	

