#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <limits.h>

int max(int a,int b);
int min (int a,int b);
bool relocation(int house[], int pickedHouse);
void listSuccessors(int house[],int depth,int depthMAX,int *mValue,int *action ,int player);
int evaluate(int house[],int *mValue,int *action);
int finalScoring(int house[]);
int minimaxDecision(int house[], int depthMAX);
void maxValue(int house[], int depth, int depthMAX, int *mValue, int *action);
void minValue(int house[], int depth, int depthMAX, int *mValue, int *action);



int main()
{
	int num,house[14],depthMAX;

	scanf("%d",&num);
	while(num--)
	{
		for(int i = 0;i<14;i++)
		{
			scanf("%d",&house[i]);
		}
		scanf("%d",&depthMAX);
		printf("%d\n",minimaxDecision(house,depthMAX));
	}


}


int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}

int min (int a,int b)
{
	if(a>b)
		return b;
	else
		return a;
}


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

/*
Parameters:

house[]: a state of 14 houses
depthMAX: the threshold of searching depth
depth: the current searching depth (during recursion call)


Return value:

mValue: the minimax value of the given state
action: the corresponding action to achieve the minimax value of the given state

NOTE:

(1) You need to call listSuccessors() to expand the minimax tree
(2) If there is no successor (which means it is a game-over node), call finalScoring() and evaluate() to get mValue
(3) If the expanded node is at the depth of depthMAX, call evaluate() to get mValue
(4) In maxValue(depth, ...), when taking the kth action to relocate the seeds,
if the player earn ONE MORE ACTION, instead calling minValue(depth+1, ...),
you should call maxValue(depth+2, ...) to skip the opponent.
(So is in minValue(depth, ...).)

*/


/*
player 0 = 1~6
player 1 = 7~12
*/
//•˝≥]tmpValue •Œ•L∏Ú§U§@ºh§ÅE
void listSuccessors(int house[],int depth,int depthMAX,int *mValue,int *action ,int player)
{
	int one_more_time=0;
	if(player)
	{
		*mValue = INT_MIN;
		for(int i=7;i<13;i++)
		{
			//do nothing if the set is empty
			if(house[i]==0)
				continue;

			int *tmp_house =new int[14];
			

			for(int j=0;j<14;j++)
			{
				tmp_house[j] = house[j];
			}
 
			int *tmpValue =new int;
			int *tmpaction = new int;
			*tmpaction = i;
			//¨Oß_¶A§@¶∏
			one_more_time=relocation(tmp_house,i);
			
			if(one_more_time)
			{
				
				maxValue(tmp_house, depth+2, depthMAX,tmpValue,tmpaction);
				//action §£•Œ©π§U∂«°A§£µM∑|≈‹¶®øÅEÅE‚™∫∞ ß@
				(*tmpValue>*mValue)? *mValue = *tmpValue,*action = i:0 ;
				//*mValue = max(*mValue,*tmpValue);
			}
			else
			{
				
				minValue(tmp_house, depth+1, depthMAX,tmpValue,tmpaction);
				(*tmpValue>*mValue)? *mValue = *tmpValue,*action = i:0 ;
				//*mValue = min(*mValue,*tmpValue);
			}
			//delete [] tmp_house;
		}
	}
	else
	{
		*mValue = INT_MAX;
		for(int i=0;i<7;i++)
		{
			if(house[i]==0)
				continue;

			int *tmp_house =new int[14];
			
 
			for(int j=0;j<14;j++)
			{
				tmp_house[j] = house[j];
			}

			int *tmpValue = new int;
			int *tmpaction = new int;
			*tmpaction = i;
			//¨Oß_¶A§@¶∏
			one_more_time=relocation(tmp_house,i);

			if(one_more_time){
				
				minValue(tmp_house, depth+2, depthMAX,tmpValue,tmpaction);
				(*tmpValue<*mValue)? *mValue = *tmpValue,*action = i:0 ;
				//*mValue = min(*tmpValue,*mValue);
			}
			else{
				
				maxValue(tmp_house, depth+1, depthMAX,tmpValue,tmpaction);
				(*tmpValue<*mValue)? *mValue = *tmpValue,*action = i:0 ;
				//*mValue = max(*tmpValue,*mValue);
			}
			//delete [] tmp_house;
		}
	}
}

int evaluate(int house[],int *mValue,int *action)
{
	
	*mValue = house[13]-house[6];
	return *action;
}

int finalScoring(int house[])
{
	//§]≠ncall evaluate
	//®S¶≥successor ¥N≠ncall
	int player_0_end=1,player_1_end=1;
	for(int i=0;i<7;i++)
	{
		if(house[i]!=0)
			player_0_end = 0;
	}
	for(int i = 7;i<13;i++)
	{
		if(house[i]!= 0)
			player_1_end =0;
	}
	if(player_0_end)
	{
		for(int i = 7;i<13;i++)
		{
			house[6] += house[i];
		}
	}
	if(player_1_end)
	{
		for(int i = 0;i<7;i++)
		{
			house[13] += house[i];
		}
	}
	if(player_1_end || player_0_end)
		return 1;
	return 0;
}

int minimaxDecision(int house[], int depthMAX)
{
	//
	int *mValue = new int  ;
	int *action= new int  ;
	
	maxValue(house,0,depthMAX,mValue,action);
	return *action;
	
}
void maxValue(int house[], int depth, int depthMAX, int *mValue, int *action)
{
	/*if(depth == 0)
		*mValue = -999;*/
	int is_depthMAX=0;
	
	
	//if expanded node is at the depth
	if(depth >= depthMAX)
	{
		is_depthMAX=1;
	}
	//≠YπC¿∏µ≤ßÙ°Aµ≤∫ÅE
	if(finalScoring(house))
	{
		evaluate(house,mValue,action);		
	}
	else if(is_depthMAX)
	{
		//call finalScoring() and evaluate() to get mValue
		//*mValue = -999; 
		//finalScoring(house,mValue,action);
		evaluate(house,mValue,action);

	}
	else
	{
		//list successor
		listSuccessors(house,depth,depthMAX,mValue,action,1 );
		
	}
	
}
void minValue(int house[], int depth, int depthMAX, int *mValue, int *action)
{
	//*mValue = 999;

	int is_depthMAX=0;
	
	//if expanded node is at the depth
	if(depth >= depthMAX)
	{
		is_depthMAX=1;
	}
	//≠YπC¿∏µ≤ßÙ°Aµ≤∫ÅE
	if(finalScoring(house))
	{
		evaluate(house,mValue,action);		
	}
	else if(is_depthMAX)
	{
		//call finalScoring() and evaluate() to get mValue
		//*mValue = 999;
		//finalScoring(house,mValue,action);
		evaluate(house,mValue,action);

	}
	else
	{
		//list successor
		listSuccessors(house,depth,depthMAX,mValue,action,0 );
	}
}