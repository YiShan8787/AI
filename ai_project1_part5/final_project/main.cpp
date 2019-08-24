#include<stdio.h>
#include<queue>
#include<iostream>
#include<stdlib.h>

using namespace std;

struct Node
{
	int state[20],g,h,f,action;
	long long int order;
	Node *prevNode;
};

bool isGoal(int a[],int n)
{
	for(int i=0;i<n;i++)
	{
		if(a[i]!=i)
			return 0;
		
	}
	return 1;
}

struct cmp
{
	bool operator()(const Node* l,const Node* r)
	{
		//return l.f>r.f;
		if(l->f==r->f)
			return l->order>r->order;
		else
			return l->f>r->f;
		
	}
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

void show_step(Node end,int num)
{
	if(end.prevNode){
		show_step(*end.prevNode,num);
		printf("(%d) [",end.action);
			for(int i=0;i<num;i++)
			{
				if(i==num-1)
					printf("%d]\n",end.state[i]);
				else
					printf("%d ",end.state[i]);
			}
		delete end.prevNode;
	}
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
	//tmp_Node.g = action;
	tmp_Node.h = GapNumber(tmp_Node.state,TotalPancakes);
	//tmp_Node.h = 1;
	//tmp_Node.f = tmp_Node.g+tmp_Node.h;
	tmp_Node.action = action;

	return tmp_Node;
}


int main()
{
	int num,round =0;
	long long int order = 0;
	priority_queue<Node*,vector<Node*>,cmp>pq;
	Node *tmp,*head;
	head = new Node;
	scanf("%d",&num);
	for(int i=0;i<num;i++)
	{
		scanf("%d",&head->state[i]);
	}
	//defult 
	head->g = round;
	head->h = GapNumber(head->state,num);
	head->f = head->g+ head->h;
	head->order = order;
	head->prevNode = 0;
	order++;
	//後續的點
	Node *current = head;
	//check is goal
	while(!isGoal(current->state,num))
	{
		//make successor
		for(int i=2;i<=num;i++)
		{
			tmp = new Node;
			*tmp = makeSuccessor(*current,i,num);
			tmp->prevNode = current;
			if(tmp->prevNode)
				if(i==tmp->prevNode->action)
				{
					delete [] tmp;
					continue;
				}
			
			
			
			//寫出這是第幾步
			tmp->g = tmp->prevNode->g+1;
			//步數+gap
			tmp->f = tmp->g+tmp->h;
			tmp->order = order;
			
			//printf("%d %d\n",tmp->action,tmp->f);
			
			pq.push(tmp);
			order++;
		}
		//printf("successor done\n\n");
		//拿出最好的，其他都不要
		//更新previous action

		current = pq.top();

		pq.pop();
		
	}
	while(!pq.empty())
		{
			pq.pop();
		}
	show_step(*current,num);
	
	
}