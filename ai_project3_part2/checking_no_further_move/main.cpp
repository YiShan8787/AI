#include <stdio.h>

bool check(int pan[])
{
	int player0_win=1,player1_win=1;
	for(int i=0;i<6;i++)
	{
		if(pan[i]!=0){
			player0_win = 0;
			break;
		}
	}
	for(int i=7;i<13;i++)
	{
		if(pan[i]!=0){
			player1_win = 0;
			break;
		}
	}
	if(player1_win || player0_win)
		return 1;
	else
		return 0;
}

int main()
{
	int time,pan[14];
	scanf("%d",&time);
	while(time--)
	{
		for(int i=0;i<14;i++)
		{
			scanf("%d",&pan[i]);
		}
		if(check(pan))
			printf("YES\n");
		else
			printf("NO\n");
		
	}
}