#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
int top=-1;
struct linknode
{	unsigned int a[4];
	struct linknode* next;
	int start;
}*custarr[10];

struct linknode* update(int,int);
void display(unsigned int a[],int);
void unions(struct linknode*, struct linknode*);
void intersection(struct linknode*, struct linknode*);
void difference(struct linknode*, struct linknode*);
struct linknode* newnode(int);
void displaylist(struct linknode*);

int main()
{	int products[5],c,ch,ch2,total,i,pos;
	char choice='y';
	while(choice=='y' || choice=='Y')
	{
		printf("\n 1.Buy as New Customer\n 2.Buy as Existing Customer\n 3.Find union of 2 customers\n 4.Find intersection of 2 customers\n 5.Find difference of 2 customers");
		scanf("%d",&c);
		switch(c)
		{	case 1: printf("\n Your ID no. is %d", ++top);
			ch=top;break;
			case 2: printf("\n Enter you ID no.");
				scanf("%d",&ch);
				if(ch>top)
				{	printf("\n Customer doesn't exist");
					goto y;
				}break;
			case 3: printf("Enter Customer ID nos.");
				scanf("%d%d",&ch,&ch2);
				if(ch>top || ch2>top)
				{	printf("\n Customers don't exist");
					break;
				}
				//			printf("\n All products are:\t");
				unions(custarr[ch],custarr[ch2]);
				break;
			case 4:printf("Enter Customer ID nos.");
			       scanf("%d%d",&ch,&ch2);
			       if(ch>top || ch2>top)
			       {       printf("\n Customers don't exist");
				       break;
			       }
			       intersection(custarr[ch],custarr[ch2]);
			       break;
			case 5:printf("Enter Customer ID nos.");
			       scanf("%d%d",&ch,&ch2);
			       if(ch>top || ch2>top)
				       printf("\n Customers don't exist");
			       difference(custarr[ch],custarr[ch2]);
			       break;
			default:printf("\n wrong choice entered");
		}
		if(c==1 || c==2)// If choice is to buy
		{
			printf("\n Enter total no. of products to be bought");
			scanf("%d",&total);
			for(i=0; i<total; i++)
			{	printf(" Enter product-no. %d",i+1);
				scanf("%d",&products[i]);
				if(!custarr[ch])	//If new customer		
				{	custarr[ch]= (struct linknode*)malloc (sizeof(struct linknode));
					custarr[ch]->next=NULL;
					custarr[ch]->start=(products[i]/128);
					custarr[ch]->start*=128;
					pos=products[i]%128;
					custarr[ch]->a[pos/32]=custarr[ch]->a[pos/32]|1<<(32-pos);
				}
				else
					custarr[ch]=update(products[i],ch);					
			}
		}
	y:	printf("\n Continue with more operations? (y/n)");
		scanf("%s",&choice);
	}
	return 0;
}

struct linknode* update(int a,int y)
{	int k=a/128,pos=a%128;
	k*=128;
	struct linknode *temp=custarr[y];
	for(;temp;temp=temp->next)
	{	if(k==temp->start)
		{		temp->a[pos/32]=temp->a[pos/32]|1<<(32-pos);
			return custarr[y];
		}
	}
	for(temp=custarr[y];temp->next;temp=temp->next);
	temp->next=newnode(a);
	temp=temp->next;
	return custarr[y];
}
void displaylist(struct linknode* a)
{	struct linknode* tempa=a;	
	for(;tempa;tempa=tempa->next)
        {
                printf("\n%d\t",tempa->start);
                display(tempa->a,tempa->start);
        }
}

void unions(struct linknode* a, struct linknode* b)//pass two linklist of customers as parameters
{
	int i,flag=0;
	unsigned int arr[4]={0,0,0,0};
	struct linknode *head,*tempa=a,*tempb=b;
	printf("\nFirst Customer has:");
	displaylist(tempa);
	printf("\n Second Customerr has:");
	displaylist(tempb);
	printf("\n All products are:\n");
	for(tempa=a;tempa;tempa=tempa->next)
	{       for(tempb=b;tempb;tempb=tempb->next)
		{       if(tempa->start==tempb->start)
			{	for(i=0; i<4; i++)
				{      arr[i]=tempa->a[i]|tempb->a[i];	//ORing and displaying common nodes
				} 
				display(arr,tempa->start);
				break;
			}
			else
			{      display(tempa->a,tempa->start);	//displaying rest of a
			}
		}
	}
	for(tempb=b;tempb;tempb=tempb->next)
	{	flag=0;
		for(tempa=a;tempa;tempa=tempa->next)
		{       if(tempb->start==tempa->start)
			{      flag=1;
				break;
			}
		}
		if(!flag)
			display(tempb->a,tempb->start);	//displaying rest of b

	}
}
void display(unsigned int a[],int start)
{	unsigned int arr[4]={0,0,0,0};
	int k=0,i=0,p;
	{	while(i<4)
		{	arr[i]=a[i];
			k=0;
			while(arr[i]>0)
			{	p=arr[i]%2;
				if(p==1)
					printf("\t %u", (start+(i*32)+(32-k)));			
				k++;
				arr[i]=arr[i]>>1;
			}i++;
		}
	}
}

void intersection(struct linknode* tempa, struct linknode* tempb)
{	int i=0;
	struct linknode* a=tempa, *b=tempb;
	unsigned int arr[4]={0,0,0,0};
	printf("\n First customer has:\n");
	displaylist(a);
	printf("\nSecond Customer has:\n");
	displaylist(b);	
	printf("\n Common Products are:\n");
	for(a=tempa;a;a=a->next)
	{	for(b=tempb;b;b=b->next)
		{	if(a->start==b->start)
			{	for(i=0;i<4;i++)
				{	arr[i]=a->a[i]&b->a[i];
				}
				display(arr,a->start);
				break;
			}
		}
	}
}
void difference(struct linknode* tempa, struct linknode* tempb)// A-B
{	int i=0,flag=0,arr[4]={0,0,0,0};
	struct linknode *a=tempa,*b=tempb;
	printf("\n First customer has:\n");     
        displaylist(a);
        printf("\nSecond Customer has:\n");     
        displaylist(b);
	printf("\n Products in first that are not in b are:\n");
	for(a=tempa;a;a=a->next)
	{       flag=0;
		for(b=tempb;b;b=b->next)
		{       if(a->start==b->start)
			{	for(i=0;i<4;i++)
				{       arr[i]=a->a[i]^b->a[i];	//Finding different products
					arr[i]=arr[i]&a->a[i];	//Finding products present in a
				}
				display(arr,a->start);
				flag=1;
			}
		}
		if(!flag)
		{	display(a->a,a->start);
		}
	}
}
struct linknode* newnode(int k)
{	int pos;
	struct linknode* new=(struct linknode *)malloc(sizeof(struct linknode));
	new->start=k/128;
	new->start*=128;
	new->next=NULL;
	pos=k%128;
	new->a[pos/32]=new->a[pos/32]|1<<(32-pos);
	return new;
}

