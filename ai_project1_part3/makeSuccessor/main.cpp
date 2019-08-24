#include<stdio.h>
/*
state : store all id of pancakes
g : the real flip number of this state
h : gap number
f : =h+g
action : the action applied on the previous state to reach the state
*/
struct Node
{
	int state[20],g,h,f,action;
	Node *prevNode;
};


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

/*
Node current : the state of the pancake.
int action : the action you want to flip.
int TotalPancakes : all pancakes.
return : the successor Node.
*/

Node makeSuccessor(Node current,int action,int TotalPancakes)
{
	int tmp[20];
	Node tmp_Node=current;
	for(int i = 0;i<action;i++)
	{
		tmp_Node.state[i]=current.state[action-i-1];
	}
	tmp_Node.g = action;
	tmp_Node.h = GapNumber(tmp_Node.state,TotalPancakes);
	//tmp_Node.h = 1;
	//tmp_Node.f = tmp_Node.g+tmp_Node.h;
	tmp_Node.action = action;

	return tmp_Node;
}


int main()
{
	int number, totalPancake,current_g,previous_action,*temp;
	Node current,next;
	scanf("%d",&number);
	while(number--)
	{
		scanf("%d",&totalPancake);
		for(int i=0;i<totalPancake;i++)
		{
			scanf("%d",&current.state[i]);
		}
		
		scanf("%d",&current_g);
		scanf("%d",&previous_action);
		for(int i=2;i<=totalPancake;i++)
		{
			if(i==previous_action)
				continue;
			next = makeSuccessor(current,i,totalPancake);
			//寫出這是第幾步
			next.g = current_g+1;
			//步數+gap
			next.f = next.g+next.h; 
			printf("[");
			for(int i=0;i<totalPancake;i++)
			{
				if(i==totalPancake-1)
					printf("%d]",next.state[i]);
				else
					printf("%d ",next.state[i]);
			}
			printf(", %d, %d, %d, %d\n",next.g,next.h,next.f,next.action);
		}
	}
}