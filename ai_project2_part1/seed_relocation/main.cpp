#include <stdlib.h>
#include <stdio.h>

/*
house[]: a current state of 14 houses
pickedHouse: the ID of the picked house

true if the final seed falls in the player's store
false otherwise

Note:

Remember not to put seeds into the opponent's store.
You can decide the player (human or computer) by the picked house ID.
*/
bool relocation(int house[], int pickedHouse)
{
	//player(0~5)
	//computer(7~12)
	//border:   (pickedHouse+1)/7 
	int seed = house[pickedHouse],position=pickedHouse,bank = ((pickedHouse+1)/7+1)*7-1;
	house[pickedHouse]=0;
	while(seed)
	{
		if((bank==6 && position ==12) || (bank==13 && position ==5)) //  next is another bank
		{
			//position = ((position+1)/7-1)*7;
			++++position;
			if(position>13) position =0;
			house[position]++;
			--seed;
			continue;
		}
		++position;
		if(position>13) position =0;
		house[position]++;
		--seed;
	}
	if(house[position]==1 && (position+1)%7!=0 && (position+1)/7==(pickedHouse+1)/7 && house[12-position]) // last_is_empty && not in bank && in my zone && opposite bowl has seed
	{
		house[bank] = house[bank] + house[12-position] + house[position];
		house[position] = 0;
		house[12-position]=0;
	}


	if(position == bank)
		return 1;
	return 0;
}


int main()
{
	int num,house[16],one_more_chance=0,pickedHouse;
	char y[10]="YES",n[10]="NO";
	scanf("%d",&num);
	for(int i=0;i<num;i++)
	{
		for(int j=0;j<14;j++)
		{
			scanf("%d",&house[j]);
		}
		scanf("%d",&pickedHouse);
		one_more_chance = relocation(house,pickedHouse);
		
		printf("[");
		for(int j=0;j<14;j++)
		{
			if(j==0)
				printf("%d",house[j]);
			else
				printf(" %d",house[j]);
		}
		printf("]\n");
		char* ans =(one_more_chance==1)? y:n;

		printf("%s\n",ans);
	}
	
}