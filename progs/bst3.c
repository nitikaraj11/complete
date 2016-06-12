#include<stdio.h>

#include<stdlib.h>





struct node

{

	int info;

	struct node *llink,*rlink,*pptr;

};





typedef struct node * NODE;

static int gName=0;

int val;

NODE getnode()

{

	NODE x;

	

	x=(NODE)malloc(sizeof(struct node));



	if(x==NULL)

	{

		printf("out 0f memory\n");

		exit(0);

	}

	

	return x;

}





NODE insert(int item,NODE root)

{

	NODE temp,cur,prev;



	temp=getnode();



	temp->info=item;

	temp->llink=NULL;

	temp->rlink=NULL;

	temp->pptr=NULL;



	if(root==NULL)

		return temp;



	prev=NULL;

	cur=root;		



	while(cur!=NULL)

	{

		prev=cur;

		//No duplicate elements allowed

		if(item==cur->info)

		{

			val++;				

			return root;

					

		}



		if(item < cur->info)

			cur=cur->llink;



		else

			cur=cur->rlink;



	}



	if(item < prev->info)

		prev->llink=temp;

		

	

	else

		prev->rlink=temp;

		

		temp->pptr=prev;	

	return root;

}

		



NODE delete(int item,NODE root)

{

}







void preorderDotDump (NODE root, FILE* outputFile)

{

	if (root != NULL) 

	{

		fprintf (outputFile, "%d [label=%d,color=black];\n",root->info, root->info);

		if (root->llink != NULL) 

		         fprintf (outputFile, "%d -> %d ;\n", root->info, (root->llink)->info);

		

        	if (root->rlink != NULL)

            		fprintf (outputFile, "%d -> %d;\n", root->info, root->rlink->info);

	//	if (root->pptr != NULL)

         //   		fprintf (outputFile, "%d -> %d [style = dashed];\n", root->info, (root->pptr)->info);

        	preorderDotDump (root->rlink, outputFile);

        	preorderDotDump (root->llink, outputFile);

    	}

}



void dotDump(NODE root, FILE *outFile)

{

	gName++;

	fprintf (outFile, "digraph BST {\n",gName);

	

	preorderDotDump (root, outFile);

    	fprintf (outFile, "}\n");

}

FILE *outputFile;









int main(int argc, char** argv)

{

		FILE *pipe;

		NODE root,temp;

		int ch,i,item;

		int x;

		root='\0';

		if (argc != 2)

		{

			printf(" need one argument  \n");

			exit(0);

		}



		outputFile = fopen ("bst.dot", "w");

    		fclose (outputFile);

		val = atoi(argv[1]);

		for(i=0;i<val;i++)

		{

			item=random()%1000;

			printf("%d\t",item);

			root=insert(item,root); 

						

			outputFile = fopen ("bst.dot", "a");

			if (outputFile != NULL) 

			{

					        	

				dotDump (root,  outputFile);

			}

			fclose (outputFile);

		}						

					







		while(1)

		{

			printf("\n1.Delete\n2.Display dotty \n");

			printf("Enter your choice\n");

			scanf("%d",&ch);

			switch(ch)

			{

				

					

							

				case 1:printf("Enter element to be deleted\n");

					scanf("%d",&item);

					root=delete(item,root);

					printf("\nElement deleted\n");					

					outputFile = fopen ("bst.dot", "a");

					dotDump (root,  outputFile);

					fclose (outputFile);

					break;

				

				case 2:

					pipe=popen("dot -Tps bst.dot -o bst.ps","w");

					pclose(pipe);	

					pipe=popen("evince bst.ps","r"); 

					pclose(pipe);

	

					break;

	

				default:printf("wrong choice\n");

					exit(0);



			}

			

			

		}

		return 0;

}


