#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
int top=-1;
void insert(int,int);
void update(int,int);
struct linknode
{	double a[2];
	struct linknode* next;
	int start;
};

struct stacknode
{
	struct linknode* head,*temp=head;//*last=NULL
}custarr[10];

int main()
{	int products[5],ch,ch2,total,i;
	printf("\n 1.Buy as New Customer\n 2.Buy as Existing Customer\n 3.Find union of 2 customers\n 4.Find intersection of 2 customers\n 5.Find difference of 2 customers");
	scanf("%d",&ch);
	switch(ch)
	{	case 1: printf("\n Your ID no. is %d", ++top);
		//	custarr[top]->custno=top;
			ch=top;break;
		case 2: printf("\n Enter you ID no.");
			scanf("%d",&ch);
			if(ch>top)
			{	printf("\n Customer doesn't exist");
				exit(0);
			}break;
		case 3: printf("Enter Customer ID nos.");
			scanf("%d%d",&ch,&ch2);
			if(ch>top || ch2>top)
				printf("\n Customers don't exist");
			unions(custarr[ch].head,custarr[ch2].head);
			break;
		case 4:printf("Enter Customer ID nos.");
                        scanf("%d%d",&ch,&ch2);
                        if(ch>top || ch2>top)
                                printf("\n Customers don't exist");
                        intersection(custarr[ch].head,custarr[ch2].head);
                        break;
		case 5:printf("Enter Customer ID nos.");
                        scanf("%d%d",&ch,&ch2);
                        if(ch>top || ch2>top)
                                printf("\n Customers don't exist");
                        difference(custarr[ch].head,custarr[ch2].head);
                        break;
		default:printf("\n wrong choice entered");
	}
	printf("\n Enter total no. of products to be bought");
	scanf("%d",&total);
	for(i=0; i<total; i++)
	{	printf(" Enter product-no. %d",i+1);
		scanf("%d",&products[i]);
		if(!custarr[ch].head)		
		{	struct linknode* new= (struct linknode*)malloc (sizeof(struct linknode*));
			custarr[ch].head=custarr[ch]->temp=new;
			custarr[ch].head->start=(products[i]/128);
			custarr[ch].head->start*=2;
			insert(products[i],ch);
		}
		else
			update(product[i],ch);					
	}
	return 0;
}

void update(int a,int y)
{	int k=a/128,flag=0;
	k*=128;
	custarr[y].temp=custarr[y].head;
	for(;custarr[y].temp;custarr[y].temp=custarr[y].temp->next)
	{	if(k>=custarr[y].temp->start && k<custarr[y].temp->start+127)
		{		insert(a,y);
				flag=1;
				break;
		}
	}
	if(!flag)
	{	struct linknode* new= (struct linknode*)malloc (sizeof(struct linknode*));
		temp->next=new;
		temp=temp->next;
		custarr[y].temp->start=(a/128);
                custarr[y].temp->start*=2;
		insert(a,y);
	}
		
}
void insert(int a,int y)
{	int pos,j;
//	custarr[top]->temp->start=(a/128);
//      custarr[top]->temp->start*=2;
	pos=a%128;
	j=pos/64;
	custarr[y].temp->a[j]=custarr[y].temp->a[j]|1<<pos;
}
		
void unions(struct linknode* a, struct linknode* b)//pass two linklist of customers as parameters
{
        int i;
        struct linknode* c,*head=c;
        struct linknode* tempa,*tempb;
        for(tempa=a; tempa; tempa=tempa->next)
        {
                for(tempb=b; tempb; tempb=tempb->next)
                {       if(tempa->start=tempb->start)
                        {       struct linknode* new=(struct node*)malloc(sizeof(struct node));
                                head->next=new;
                                head->start=tempa->start;
                                for(i=0; i<3; i++)
                                {       head->a[i]=tempa->a[i]|tempb->a[i];
                                }
                                head->next=NULL;
                        }
                        else
                        {       head->next=tempa;
                                head=head->next;
                        }
                }
        }
        for(tempa=a; tempa; tempa=tempa->next)
        {
                for(tempb=b; tempb; tempb=tempb->next)
                {       if(tempb->start!=tempa->start)
                        {       head->next=tempb;
                                head=head->next;
                        }
                }
        }
        display(c);
}
void display( struct linknode* c)
{     






















				
