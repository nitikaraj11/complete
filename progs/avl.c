#include<stdio.h>
#include<malloc.h>

    struct node 

    {	int key,length;

	struct node* right;
	struct node* left;

    };

   void preorder(struct node*);      //to display tree   

   struct node* rr(struct node*);     //to rotate right

   struct node* lr(struct node*);     //to rotate left

   struct node* insert(struct node*,int);     //to insert new node

   struct node* rotate(struct node*,int);    //to check equality and rotate

    int check(struct node*);       //to calculate diff b/w left and right children

    int total(struct node*);     //to calculate total length



   struct node* newnode(int key)

    {   struct node* new1=(struct node*)malloc(sizeof(struct node));
        
	new1->key=key;

	new1->left=new1->right=NULL;

	new1->length=1;

	return new1;

    }

    int total(struct node* new2)

    {	if(!new2)

		return 0;

	else

		return new2->length;

    }

    int check(struct node *a)

    {   int b;

	if(!a)

		return 0;

	else

	{	b=total(a->left)-total(a->right);

		return b;

	}

    }

    struct node* insert(struct node* new1, int key)

    {	
	int a,b;
	if(!new1)
	{	
	new1->key=key;
	return new1;
	}

	if(key<new1->key)

		new1->left=insert(new1->left,key);

	else

		new1->right=insert(new1->right,key);



	a=total(new1->left)+1;

	b=total(new1->right)+1;

	if(a>b)

		new1->length=a;

	else if(a<b)

		new1->length=b;



	struct node* rotated=(struct node*)malloc(sizeof(struct node));

	rotated=rotate(new1,key);

	return rotated;

    }

    struct node* rotate(struct node *new3, int key)

    {   
        int a;
        a=check(new3);

	if(a>1 && key<new3->left->key)

		return rr(new3);

	else if(a>1 && key>new3->left->key)

	{	new3->left=lr(new3->left);

		return rr(new3);

	}

	else if(a<-1 && key>new3->right->key)

		return lr(new3);

	else if(a<-1 && key<new3->right->key)

	{	new3->right=rr(new3->length);

		return lr(new3);

	}

	else

		return new3;

    }

    struct node *rr(struct node *old)

    {	struct node* t2=(struct node*)malloc(sizeof(struct node));

        struct node* t1=(struct node*)malloc(sizeof(struct node));

	int a,b;
	t1=old->left;

	t2=t1->right;

	t1->right=old;

	old->left=t2;

	a=total(old->left);

	b=total(old->right);

	if(a>b)

		old->length=a;

	else

		old->length=b;

	a=total(t1->left);

	b=total(t1->right);

	if(a>b)

		t1->length=a;

	else

		t1->length=b;

	return t1;

    }

    struct node* lr(struct node* old)

    {	
	struct node* t2=(struct node*)malloc(sizeof(struct node));

        struct node* t1=(struct node*)malloc(sizeof(struct node));


		int a,b;
	t1=old->right;

	t2=t1->left;

	t1->left=old;

	old->right=t2;

	a=total(old->left);

	b=total(old->right);

	if(a>b)

		old->length=a;

	else

		old->length=b;

	a=total(t1->left);

	b=total(t1->right);

	if(a>b)

		t1->length=a;

	else

		t1->length=b;

	return t1;

    }

	void preorder(struct node* abc)
{
	printf("%d\t",abc->key);
	preorder(abc->left);
	preorder(abc->right);
}



    int main()

    {	
    	struct node* root=(struct node*)malloc(sizeof(struct node)); 
        root=NULL;

	int n,key,i;

	printf("\n Enter no. of nodes");

	scanf("%d",&n);

	printf("\n Enter %d  no. of keys to be inserted\n",n);

	for(i=0; i<n; i++)
	{	
	scanf("%d",&key);

	root=insert(root,key);

	}

	preorder(root);

	return 0;

    }
