#include <iostream>     // std::cout
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <queue>
#include<stdio.h>
#include<string.h>
using namespace std;

struct Node
{
	int state[20],g,h,f,action,order;
	Node *prevNode;
};

struct cmp
{
	bool operator()(const Node& l,const Node& r)
	{
		if(l.f==r.f)
			return l.order>r.order;
		else
			return l.f>r.f;
	}
};



/*
void swap(Node &p1, Node &p2){
    Node temp = p1;
    p1 = p2;
    p2 = temp;
}

void MaxHeapify(Node * successor, int root, int length){

    int left = 2*root,      // ���oleft child
    int right = 2*root + 1,     // ���oright child
    int largest;                // largest�ΨӰO���]�troot�Pchild, �T�̤���Key�̤j��node

    if (left <= length && successor[left].f > successor[root].f)
        largest = left;
    else
        largest = root;

    if (right <= length && successor[right].f > successor[largest].f)
        largest = right;

    if (largest != root) {                         // �p�G�ثeroot��Key���O�T�̤����̤j
        swap(successor[largest], successor[root]);         // �N�մ�root�P�T�̤�Key�̤j��node����m
        MaxHeapify(successor, largest, length);        // �վ�s��subtree��Max Heap
    }
}

void BuildMaxHeap(Node * successor, int totalnode){

    for (int i = (int)totalnode/2; i >= 1 ; i--) {
        MaxHeapify(successor, i, (int)totalnode - 1);     // length�n��@, �]��heap�q1�}�l�s����
    }
}
*/


int main()
{

	priority_queue<Node,vector<Node>,cmp>pq;
	//Node priority_queue[20];
	Node tmp;
	char command[20];
	int order=0;
	while(1)
	{
		scanf("%s",command);
		if(!strcmp(command,"INSERT"))
		{
			//store the node into queue (including the state of node)
			for(int i=0;i<16;i++)
			{
				//scanf("%d",&priority_queue[num_in_queue].state[i]);
				scanf("%d",&tmp.state[i]);
			}
			//scanf("%d",&priority_queue[num_in_queue].g);
			//scanf("%d",&priority_queue[num_in_queue].h);
			scanf("%d",&tmp.g);
			scanf("%d",&tmp.h);
			tmp.f = tmp.g+tmp.h;
			tmp.order = order;
			order++;
			pq.push(tmp);
		}

		if(!strcmp(command,"GETTOP"))
		{
			//print the top node in queue
			tmp = pq.top();
			printf("[");
			for(int i=0;i<16;i++)
			{
				if(i==15)
					printf("%d]",tmp.state[i]);
				else
					printf("%d ",tmp.state[i]);
			}
			printf(", %d, %d, %d\n",tmp.g,tmp.h,tmp.f);
			pq.pop();
		}

		if(!strcmp(command,"GETALL"))
		{
			while(!pq.empty())
			{
				//print all the top node in queue recursively
				tmp = pq.top();
				printf("[");
				for(int i=0;i<16;i++)
				{
					if(i==15)
						printf("%d]",tmp.state[i]);
					else
						printf("%d ",tmp.state[i]);
				}
				printf(", %d, %d, %d\n",tmp.g,tmp.h,tmp.f);
				pq.pop();
			}
			break;
		}
	}
	
}