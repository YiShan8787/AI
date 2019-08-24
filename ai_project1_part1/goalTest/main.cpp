#include<stdio.h>
#include<stdlib.h>

bool isGoal(int a[],int n)
{
	for(int i=0;i<n;i++)
	{
		if(a[i]!=i)
			return 0;
		
	}
	return 1;
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
		
		printf("%s\n", isGoal(pancake, num)? "YES" :"NO");
		//
	}
	//system("pause");
}