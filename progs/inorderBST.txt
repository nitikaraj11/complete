#include<stdio.h>
#include<stdlib.h>

struct Node   /*Structure for a Node*/
{
char data;
struct Node* left;
struct Node* right;
};

struct Node* BuildNode(char data)  /*function to create a node*/
{
struct Node* new = (struct Node*)malloc(sizeof(struct Node));
new->data = data;
new->left = NULL;
new->right = NULL;
return(new);
}

int SearchIndex(char a[],int start,int end,char val) /*function to check the position of an element in inorder travesal*/
{
int i;
for(i=start;i<=end;i++)
{
if(a[i]==val)
return i;
}
}

struct Node* TConstruct(char inorder[],char preorder[],int start,int end)/*fuction to Create the Tree*/
{
static int Pindex=0;
if(start>end)
return NULL;
struct Node *tNode=BuildNode(preorder[Pindex++]);
if(start==end)
return (tNode);
int Iindex=SearchIndex(inorder,start,end,tNode->data);
tNode->left=TConstruct(inorder,preorder,start,Iindex-1);
tNode->right=TConstruct(inorder,preorder,Iindex+1,end);
return tNode;
}

void PrintTree(struct Node* nodes)/*function to print the tree*/
{
if(nodes==NULL)
return;

PrintTree(nodes->left);

printf("%c\n",nodes->data);

PrintTree(nodes->right);
}
void PrintTreePOST(struct Node* nodes)
{
if(nodes==NULL)
return;
PrintTreePOST(nodes->left);
PrintTreePOST(nodes->right);
printf("%c\n",nodes->data);
}
void PrintTreePRE(struct Node* nodes)
{
if(nodes==NULL)
return;
printf("%c\n",nodes->data);
PrintTreePRE(nodes->left);
PrintTreePRE(nodes->right);
}

int main()/*main driver function*/
{
char preorder[30],inorder[30];
int n,i,j;
printf("ENTER NUMBER OF ELEMENTS:\n");
scanf("%d",&n);
printf("Enter Inoredered Elements:\n");
for(i=0;i<2*n;i++)
{
scanf("%c",&inorder[i]);
}
printf("enter preordered Elements:\n");
for(j=0;j<2*n;j++)
{
scanf("%c",&preorder[j]);
}
struct Node *root=TConstruct(inorder,preorder,0,2*n-2);

printf("-----------------The TREE---------------\n");
PrintTree(root);
/* this is to print the tree in other traversal modes..
printf("-----------------POSTORDER--------------\n");
PrintTreePOST(root);
printf("-----------------PREORDER---------------\n");
PrintTreePRE(root);*/
printf("\n\n");
}
