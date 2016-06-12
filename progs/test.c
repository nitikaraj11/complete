#include<stdio.h>
void display(unsigned int a[],int start)
{       unsigned int arr[4];
        int k=0,i=0,p;
        {       while(i<4)
                {       arr[i]=a[i];
                        k=0;p=0;
                        while(arr[i]>0)
                        {       p=arr[i]%2;
                                if(p==1)
                                        printf("\t %u", (start+(i*32)+(31-k)));
                                k++;
                                arr[i]=arr[i]>>1;
                        }i++;
                }
        }
}

int main()
{	unsigned int a[]={5,2,4,8};
	display(a,0);
}
