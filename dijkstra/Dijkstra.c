#define _CRT_SECURE_NO_WARNINGS
#define TRUE   1
#define FALSE   0
#define HEAP_LEN   100

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

typedef struct _element {
	char name;
	int value;
}element;

typedef element * HData;
typedef int PriorityComp(int d1, int d2);

typedef struct _heap
{
	PriorityComp * comp;
	int numOfData;
	HData heapArr[HEAP_LEN];
} Heap;


void HeapInit(Heap * ph, PriorityComp pc)
{
	ph->numOfData = 0;
	ph->comp = pc;
}

int HIsEmpty(Heap * ph)
{
	if (ph->numOfData <= 0)
		return TRUE;
	else
		return FALSE;
}

int GetParentIDX(int idx)
{
	return idx / 2;
}

int GetLChildIDX(int idx)
{
	return idx * 2;
}

int GetRChildIDX(int idx)
{
	return GetLChildIDX(idx) + 1;
}

int GetHiPriChildIDX(Heap * ph, int idx)
{
	if (GetLChildIDX(idx) > ph->numOfData)
		return 0;

	else if (GetLChildIDX(idx) == ph->numOfData)
		return GetLChildIDX(idx);

	else
	{
		if (ph->comp(ph->heapArr[GetLChildIDX(idx)]->value,
			ph->heapArr[GetRChildIDX(idx)]->value) < 0)
			return GetRChildIDX(idx);
		else if (ph->comp(ph->heapArr[GetLChildIDX(idx)]->value,
			ph->heapArr[GetRChildIDX(idx)]->value) == 0)
		{
			if (ph->heapArr[GetLChildIDX(idx)]->name >
				ph->heapArr[GetRChildIDX(idx)]->name)
			{
				return GetRChildIDX(idx);
			}
			else
				return GetLChildIDX(idx);
		}
		else
			return GetLChildIDX(idx);
	}
}

void HInsert(Heap * ph, HData data)
{
	int idx = ph->numOfData + 1;

	while (idx != 1)
	{
		//	if(pr < (ph->heapArr[GetParentIDX(idx)].pr))
		if (ph->comp(data->value, ph->heapArr[GetParentIDX(idx)]->value) > 0)
		{
			ph->heapArr[idx] = ph->heapArr[idx-1];
			idx = idx-1;
		}
		else if (ph->comp(data->value, ph->heapArr[idx-1]->value) == 0)
		{

			if ((int)(data->name) - (int)(ph->heapArr[idx-1]->name)>0) // 만약 아빠 이름이 애새키 이름보다 크면 애새키가 위로 올라가야하므로 밑으로 내린다.
			{
				break;
			}
			else
			{
				ph->heapArr[idx] = ph->heapArr[idx-1];
				idx = idx-1;
			}
		}
		else
		{
			break;
		}
	}

	ph->heapArr[idx] = data;
	ph->numOfData += 1;
}
void swap(element * n, element *y)
{
	element  temp ;
	temp = *n;
	*n = *y;
	*y = temp;
}

HData HDelete(Heap * ph)
{
	HData retData = ph->heapArr[1];
	HData lastElem = ph->heapArr[ph->numOfData];

	int parentIdx = 1;
	int childIdx = parentIdx+1;

	//while (childIdx = GetHiPriChildIDX(ph, parentIdx))
	while(childIdx<=ph->numOfData)
	{
	//	if (childIdx > ph->numOfData)
	//		break;
		if (ph->comp(lastElem->value, ph->heapArr[childIdx]->value) > 0)
			break;
		else if (ph->comp(lastElem->value, ph->heapArr[childIdx]->value) == 0)
		{
			if ((int)(lastElem->name) < (int)(ph->heapArr[childIdx]->name)) // 만약 아빠 이름이 애새키 이름보다 크면 애새키가 위로 올라가야하므로 밑으로 내린다.
			{
				break;
			}
			//else
			//{
			//	ph->heapArr[parentIdx] = ph->heapArr[childIdx]; //노드를 위로 보내는 것
			//	parentIdx = childIdx;
				
			//}
			
		}
		ph->heapArr[parentIdx] = ph->heapArr[childIdx]; //노드를 위로 보내는 것
		parentIdx = childIdx;
		childIdx += 1;
	}

	ph->heapArr[parentIdx] = lastElem;
	ph->numOfData -= 1;
	return retData;
}

typedef Heap PQueue;
typedef HData PQData;

void PQueueInit(PQueue * ppq, PriorityComp pc)
{
	HeapInit(ppq, pc);
}

int PQIsEmpty(PQueue * ppq)
{
	return HIsEmpty(ppq);
}

void PEnqueue(PQueue * ppq, PQData data)
{
	HInsert(ppq, data);
}

PQData PDequeue(PQueue * ppq)
{
	return HDelete(ppq);
}


int DataPriorityComp(int ch1, int ch2)
{
	return ch2 - ch1;
}

void relax(element  * u, element  * v, int weight[][100])
{
	if (weight[(int)u->name - 65][(int)v->name - 65] == 0)
		return;
	if (v->value <= (u->value + weight[(int)u->name - 65][(int)v->name - 65]))
		return;
	if ((v->value > u->value + weight[(int)u->name - 65][(int)v->name - 65]));
	{
		
		v->value = u->value + weight[(int)u->name - 65][(int)v->name - 65];
		//printf("%c -> %c : new weight is %d\n", u->name, v->name, v->value);
	}
}

void initialize(element vertex[], char source, int numvertex)
{
	for (int i = 0; i < numvertex; i++)
	{
		if (vertex[i].name == source)
		{
			vertex[i].value = 0;
		}
		else
		{
			vertex[i].value = 10000;
		}
	}


}

void dijkstra(element vertex[], int weight[][100], char source, int numvertex)
{
	PQueue pq;
	PQueueInit(&pq, DataPriorityComp);
	element * ve[100];
	int n = 0;
	int cnt = 0;
	initialize(vertex, source, numvertex);
	
	for (int i = 0; i < numvertex; i++)
	{
		PEnqueue(&pq, &vertex[i]);
	}
	while (!PQIsEmpty(&pq))
	{
		cnt = pq.numOfData;
		for (int i = 0; i < cnt; i++)
		{
			ve[i] = PDequeue(&pq);
		}
		for (int i = 0; i < cnt; i++)
		{
			PEnqueue(&pq, ve[i]);
		}
		//element * v = PDequeue(&pq);
		//PEnqueue(&pq, v);
		
		element  * u = PDequeue(&pq);
		for (int j = 0; j < numvertex; j++)
		{
			relax(u, &vertex[j], weight);
		}
		
		
	}
	for (int i = 0; i < numvertex; i++)
	{
		printf("%d\n", vertex[i].value);
	}
}


int main()
{
	char vertexs[100] = { -100, };
	element vertex[100];
	gets(vertexs);
	int num=0;
	int i = 0;
	int numvertex = 0;
	while (i < 100) {
		if ((vertexs[i] >= 'A' && vertexs[i] <= 'Z'))
		{
			vertex[numvertex].name = vertexs[i];
			numvertex += 1;
		}
		i++;
	}
	int weight[100][100] = { 0, };


	int numedge = 0;
	scanf("%d", &numedge);
	getchar();
	for (int i = 0; i < numedge; i++ )
	{
		char edge1, edge2;
		char temp;
		int edgeweight;
		
			scanf("%c", &edge1);
			getchar();

			scanf("%c", &edge2);
			getchar();

			scanf("%d", &edgeweight);
			getchar();
		
		weight[(int)edge1 - 65][(int)edge2 - 65] = edgeweight;
	}


	dijkstra(vertex, weight, 'A', numvertex);
}


