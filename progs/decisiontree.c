//--------------------------------Program for making & testing of a DECISION TREE--------------------------------------------------------//
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
struct table
{
	int salary;
	int martial;
	int  eligible,home,defaulted;
	int done;
}customer[20];

struct node
{
	struct node* left,*right;
	char *classname;
	int eligible;
}*root;

typedef struct node* nptr;
char attributes[][10]={"salary","martial","home","defaulted"};
int count=0;

void sort ( float [], int);	
void createtree(int,int);
void calculate(int,int);
void traverse(nptr);
float cgini(int  a[][2],int);	//Function for calculating gini value
void check(struct table,nptr);	//Function for testing a decision tree

//Function: Allocates memory to a newnode
nptr newnode()
{
	nptr new=(nptr)malloc(sizeof(struct node));
	new->left=NULL;
	new->right=NULL;
	new->eligible=0;
	new->classname=(char*)malloc(sizeof(char));
	return new;
}

//Function: Creates Data-Input table
//Parameters: Total number of records
void createtable(int total,int k)
{	
	int i;
	for(i=0;i<total;i++)
	{
//		printf("\nFor Customer %d :\n",i+1);
//		printf("\nEnter salary :");
		scanf("%d",&customer[i].salary);
//		printf("\nIs married? (0/1)");
		scanf("%d",&customer[i].martial);
//		printf("\nIs defaulted? (0/1)");
		scanf("%d",&customer[i].defaulted);
//		printf("\nHas home? (0/1)");
		scanf("%d",&customer[i].home);
		if(k==1)
		{
//			printf("\n Is eligible for loan? (0/1)");
			scanf("%d",&customer[i].eligible);
		}
		customer[i].done=0;
	}

	printf("\n Given data is:\n\tCust. ID\tMartial Status\tHome Owner\tSalary\t\tLoan Defaulted\tEligible For loan\n");
	for(i=0;i<total;i++)
	{
		printf("\n\t| %d\t\t| %d\t\t |%d\t\t |%d\t\t |%d|",(i+1),customer[i].martial,customer[i].home,customer[i].salary,customer[i].defaulted);
	if(k==1)
	printf("\t\t |%d|\n",customer[i].eligible);
	}
}

int main()
{
	int total,i;
	printf("\n Enter total no. of Customers");
	scanf("%d",&total);
	createtable(total,1);
	calculate(total,4);
	createtree(total,4);
	traverse(root);
	printf("\n Enter total new customers");
        scanf("%d",&total);
        createtable(total,2);
	for(i=0;i<total;i++)
		check(customer[i],root);
	return 0;
}

//Function: For testing DEcision Tree via new records
//Parameter: A new record, Decision tree node
void check(struct table customer,nptr new)
{
	if(!new->left && !new->right)
	{
		printf("\n\n%s\t%d",new->classname,new->eligible);
		return;
	}
	else
	{
	if(strcmp(new->classname,"salary")==0)
	{
		if(customer.salary<80000)
			check(customer,new->left);
		else if(customer.salary>=80000)
			check(customer,new->right);
	}
	if(strcmp(new->classname,"martial")==0)
	{
		if(customer.martial==1)
			check(customer,new->left);
		else if(customer.martial==0)
			check(customer,new->right);
	}
	else if(strcmp(new->classname,"defaulted")==0)
	{
		if(customer.defaulted==0)
			check(customer,new->left);
		else if(customer.defaulted==1)
			check(customer,new->right);
	}
	else if(strcmp(new->classname,"home")==0)
	{
		if(customer.home==1)
			check(customer,new->left);
		else if(customer.home==0)
			check(customer,new->right);
	}
	}
}

//Function: Calls Cgini for each record and attribute
//Parameters: Total no. of rceords, Total no. of attributes		
void calculate(int total,int attotal)
{
	int i,j,attributeno;
	float gini[4];
	int a[2][2]={0,0,0,0};
	for(j=0;j<total;j++)
	{	if(!customer[j].done)
		{
			if(customer[j].salary>80000)
			{
				if(customer[j].eligible==0)
					a[0][0]++;		
				else if(customer[j].eligible==1)
					a[1][0]++;
			}
			else if(customer[j].salary<=80000)
			{
				if(customer[j].eligible==0)
					a[0][1]++;
				else if(customer[j].eligible==1)
					a[1][1]++;
			}
		}
	}
	gini[0]=cgini(a,2);
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			a[i][j]=0;
	
	for(j=0;j<total;j++)
	{	if(!customer[j].done)
		{
			if(customer[j].martial==0)
			{
				if(customer[j].eligible==0)
					a[0][0]++;
				else if(customer[j].eligible==1)
					a[1][0]++;
			}
			else if(customer[j].martial==1)
			{
				if(customer[j].eligible==0)
					a[0][1]++;
				else if(customer[j].eligible==1)
					a[1][1]++;
			}
		}
	}
	gini[1]=cgini(a,2);
	for(i=0;i<2;i++)
                for(j=0;j<2;j++)
                        a[i][j]=0;
	for(j=0;j<total;j++)
	{	if(!customer[j].done)
		{
			if(customer[j].home==0)
			{
				if(customer[j].eligible==0)
					a[0][0]++;
				else if(customer[j].eligible==1)
					a[1][0]++;
			}
			else if(customer[j].home==1)
			{
				if(customer[j].eligible==0)
					a[0][1]++;
				else if(customer[j].eligible==1)
					a[1][1]++;
			}
		}
	}
	gini[2]=cgini(a,2);
	for(i=0;i<2;i++)
                for(j=0;j<2;j++)
                        a[i][j]=0;
	for(j=0;j<total;j++)
	{	if(!customer[j].done)
		{
			if(customer[j].defaulted==1)
			{
				if(customer[j].eligible==0)
					a[0][0]++;
				else if(customer[j].eligible==1)
					a[1][0]++;
			}
			else if(customer[j].defaulted==0)
			{
				if(customer[j].eligible==0)
					a[0][1]++;
				else if(customer[j].eligible==1)
					a[1][1]++;
			}
		}
	}
	gini[3]=cgini(a,2);
	sort(gini,4);
}
void sort(float a[],int n)
{
	int i, j, temp;
	char *tempc;
	tempc=(char*)malloc(sizeof(char));
	for (i = 0; i <n-1 ; i++)
	{
		for (j = i; j <n-i-1; j++)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=a[j];
				strcpy(tempc,attributes[j]);
				strcpy(attributes[j],attributes[j+1]);
				strcpy(attributes[j+1],tempc);
			}
		}
	}
}

//Function: Calcuates gini value for given array
//Parameter: a 2-D array holding no. of records for each attribute
float cgini(int a[][2], int k)
{
	float total,a0=0,a1=0,gini,tot0,tot1;
	tot0=a[0][0]+a[1][0];
	tot1=a[0][1]+a[1][1];
	if(tot0)
		a0=pow(a[0][0]/tot0,2)+pow(a[1][0]/tot0,2);
	if(tot1)
		a1=pow(a[0][1]/tot1,2)+pow(a[1][1]/tot1,2);
	gini=(a0*(tot0/total))+(a1*(tot1/total));
	return(1-gini);
}

//Function:Creates Decision tree
//Parameters:Total records,Total attributes
void createtree(int total,int attotal)
{
	if(!root)
	{
		//If tree doesn't exist
		root=newnode();
		strcpy(root->classname,attributes[count]);
		count++;
		root->left=newnode();
		root->left->eligible=1;			
		strcpy(root->left->classname,"eligible");
	}
	nptr temp=root;
	if(temp->right)
		while(temp->right)
		{
			temp=temp->right;
		}
	if(count==attotal)
	{	
		//If all attributes have been classified
		temp->right=newnode();
		temp=temp->right;
		strcpy(temp->classname,"Not eligible");
		temp->eligible=0;
		return;	
	}
	if(temp)
	{	
		nptr new=newnode();
		strcpy(new->classname,attributes[count]);		
		count++;
		temp->right=new;
		temp=temp->right; 
		temp->left=newnode();
		temp->left->eligible=1;
		strcpy(temp->left->classname,"eligible");
	}
	if(count<=attotal)
		createtree(total,attotal);
}
//Function: traverses tree in an inoreder manner
//Parameter: tree node
void traverse(nptr root)
{	nptr temp=root;
	if(temp)
	{	printf("\n%s\t%d",temp->classname,temp->eligible);

		if(temp->left)
		traverse(temp->left);
		if(temp->right)
		traverse(temp->right);
	}
}
