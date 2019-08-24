#include<stdio.h>
#include<stdlib.h>

/*bool isGoal(int a[],int n)
{
	for(int i=0;i<n;i++)
	{
		if(a[i]!=i)
			return 0;
		
	}
	return 1;
}*/

int GapNumber(int a[],int n )
{
	int count = 0;
	for(int i=0;i<n-1;++i)
	{
		if(a[i] == a[i+1]-1 || a[i]== a[i+1]+1)
			continue;
		count++;
	}
	return count;
}


int main()
{
	int time ,num, pancake[20];

	scanf("%d",&time);
	/*for(int i=0;i<time;i++)
	{

	}*/
	while(time--)
	{
		scanf("%d",&num);
		for(int i=0;i<num;i++)
		{
			scanf("%d",&pancake[i]);
		}
		//
		
		//printf("%s\n", isGoal(pancake, num)? "YES" :"NO");
		printf("%d\n", GapNumber(pancake,num));
		//
	}
	system("pause");
}