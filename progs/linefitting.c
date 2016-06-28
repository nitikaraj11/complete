//----------------------------------------------Line-Fitting using Simple Linear Regression---------------------

#include<stdio.h>
#include<stdlib.h>

int points[50][2];

//Function: generates/inputs points
//Return integer vector
int*  generatepoints()
{
	int* a=(int*)malloc((sizeof(int)));
//	*a=rand()%100;
//	*(a+1)=rand()%100;

	scanf("%d",&*a);

	scanf("%d",&*(a+1));
	return a;
}

//Function: Calculates mean For an array
//Parameters: Index of array, total inputs
float mean(int k,int total)
{
	float mean=0;
	int i;
	for(i=0;i<total;i++)
	{
		mean+=points[i][k];
	}
	mean/=total;
	return mean;
}

//Function: Calculates slope & intercept for given points
//Parameters: Total no.of inputs
float* slope(int total)
{
	float xmean,ymean,slope=0,intercept=0,*a=(float*)malloc(sizeof(float));
	int i,temp=total;
	xmean=mean(0,total);
	ymean=mean(1,total);
	for(i=0;i<total;i++)
	{
		if(points[i][0]!=xmean)
			slope+=((points[i][0]-xmean)*(points[i][1]-ymean))/((points[i][0]-xmean)*(points[i][0]-xmean));
		else
			temp--;
	}
	slope/=temp;
	intercept=ymean-(slope*xmean);
	*a=intercept;
	*(a+1)=slope;
	return a;
}

//Function: Calculates Residual square error
//Parameters: Tota inputs, slope & intercept of line
float error(int total,int slope,int intercept)
{
	int i,y,temp;
	float error=0;
	for(i=0;i<total;i++)
	{
		y=(slope*points[i][0])+intercept;	
		error+=(points[i][1]-y)*(points[i][1]-y);
	}
//	error/=total;
	return error;
}

int main()
{
	int* a;
	int total,i;
	float x,y,*b;
	FILE *file;
	FILE *pipe=popen("gnuplot -persist","w");
	file=fopen("points","w");
	printf("\n Enter no. of points");
	scanf("%d",&total);
	for(i=0; i<total;i++)
	{
		a=generatepoints();
		points[i][0]=*a;
		points[i][1]=*(a+1);
		fprintf(file,"%d %d\n",points[i][0],points[i][1]);
//		points[i][]=generatepoints();
	}
	fclose(file);
	printf("\n Taken points are:\n");
	for(i=0;i<total;i++)
	{
		printf("\n%d\t%d",points[i][0],points[i][1]);
	}
	b=slope(total);
	printf("\n Final intercept of required line is: %f", *b);
	printf("\n Final slope of Required line is: %f\n",*(b+1));
	printf("\n Residual Squared error is : %f", error(total,*(b+1),*b));
	file=fopen("data","w");
	for(i=0;i<total;i++)
	{
		fprintf(file,"%d %.2f\n", points[i][0],((*(b+1)*points[i][0])+*b));
	}
	fclose(file);
	fprintf(pipe,"set title \"LINEAR REGRESSION\"\n");
//      fprintf(pipe,"plot 'points'\n");
        fprintf(pipe,"set style data lines\n");
//      fprintf(pipe,"replot 'data' using 1:1\n");
        fprintf(pipe,"plot 'data' with lines, 'points' with points\n");

	return 0;
}	
