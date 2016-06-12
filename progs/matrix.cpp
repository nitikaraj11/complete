#include<iostream>
using namespace std;
int main()
{	
	int i=0,j=0, m,n,k,f,a[10][10],count=1;
	cout<<"\n Enter m X n";
	cin>>m>>n;
	cout<<"\n Enter elements";
	for(i=0; i<m;i++)
	{	for(j=0; j<n; j++)
		{	cin>>a[i][j];
		}
	}
	for(i=0; i<m;i++)
	{	for(j=0; j<n; j++)
		{	cout<<a[i][j];
		}
		cout<<"\n";
	}
	count=m*n;
	while(count>0)
	{	m--;
		n--;
		i=0;
		j=0;
		for(;j<=m-1;j++)
		{	cout<<a[i][j];
			count--;
		}
		for(;i<=n-1;i++)
		{	cout<<a[i][j];
			count--;
		}
		j=0;
		for(;j<=m-1;j++)
		{	k=m-j;
			cout<<a[i][k];
			count--;
		}
		k--;
		i=0;
		for(;i<=n-1;i++)
		{	f=n-i;
			cout<<a[f][k];
			count--;
		}		
	}

	return 0;
}
