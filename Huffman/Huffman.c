#define _CRT_SECURE_NO_WARNINGS
#define TRUE   1
#define FALSE   0
#define HEAP_LEN   100

#include "stdio.h"
#include "stdlib.h"


typedef struct Node {
	int value;
	int c;
	struct Node * leftnode;
	struct Node * rightnode;
}node;

typedef node * HData;

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
	if (ph->numOfData == 0)
		return TRUE;
	else
		return FALSE;
}

int GetParentIDX(int idx) //parent index얻기
{
	return idx / 2;
}

int GetLChildIDX(int idx) //왼쪽 자식 노드 index얻기
{
	return idx * 2;
}

int GetRChildIDX(int idx) //오른쪽 자식 노드 index 얻기
{
	return GetLChildIDX(idx) + 1;
}

int GetHiPriChildIDX(Heap * ph, int idx) // 자식 노드 들 중에 priority가 높은 자식의 index를 돌려받기
{
	if (GetLChildIDX(idx) > ph->numOfData) // 전체 heap의 element 갯수와 비교하는 것
		return 0;

	else if (GetLChildIDX(idx) == ph->numOfData)
		return GetLChildIDX(idx);

	else
	{

		if (ph->comp(ph->heapArr[GetLChildIDX(idx)]->value, ph->heapArr[GetRChildIDX(idx)]->value) < 0)
			return GetRChildIDX(idx);
		else
			return GetLChildIDX(idx);
	}
}

void HInsert(Heap * ph, HData data)
{
	int idx = ph->numOfData + 1;
	while (idx != 1)
	{
		if (ph->comp(data->value, ph->heapArr[GetParentIDX(idx)]->value) > 0) // 이 자식을 넣을 위치의 index를 구하는 것
		{
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)]; // leaf노드에서 시작해서 위로 올라가는 거
			idx = GetParentIDX(idx);
		}
		else
		{
			break;
		}
	}

	ph->heapArr[idx] = data;
	ph->numOfData += 1;
}

HData HDelete(Heap * ph) // heap에서 자료 추출
{
	HData retData = ph->heapArr[1];
	HData lastElem = ph->heapArr[ph->numOfData];

	int parentIdx = 1;
	int childIdx;

	while (childIdx = GetHiPriChildIDX(ph, parentIdx))
	{
		if (ph->comp(lastElem->value, ph->heapArr[childIdx]->value) >= 0)
			break;

		ph->heapArr[parentIdx] = ph->heapArr[childIdx];
		parentIdx = childIdx;
	}

	ph->heapArr[parentIdx] = lastElem;
	ph->numOfData -= 1;
	//printf("빠져나오는 값은 : %d\n", retData->value);
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
node* makenewnode(int value, int c)
{

	node * nextnode = (node*)malloc(sizeof(node));
	nextnode->leftnode = NULL;
	nextnode->rightnode = NULL;
	nextnode->c = c;
	nextnode->value = value;
	return nextnode;
}
node * Huffman(int arr[], int num)
{
	PQueue pq;
	PQueueInit(&pq, DataPriorityComp);
	for (int j = 0; j < num; j++)
	{
		node * nextnode = makenewnode(arr[j], j);
		
		HInsert(&pq, nextnode);
	}
	for (int i = 0; i < num - 1; i++)
	{
		node * newnode = (node*)malloc(sizeof(node));
		newnode->leftnode = PDequeue(&pq);
		newnode->rightnode = PDequeue(&pq);
		//printf("나오는 값이 : %d\n", newnode->leftnode->value);
		//printf("나오는 값이 : %d\n", newnode->rightnode->value);
		newnode->value = newnode->leftnode->value + newnode->rightnode->value;
		PEnqueue(&pq, newnode);

	}

	return PDequeue(&pq);

}
int isLeaf(node* root)

{

	return !(root->leftnode) && !(root->rightnode);
}
void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);

	printf("\n");
}

void printCodes(node * root, int arr[], int top, int j)

{
	// Assign 0 to left edge and recur 
	if (root->leftnode) {

		arr[top] = 0;
		printCodes(root->leftnode, arr, top + 1, j);

	}

	// Assign 1 to right edge and recur
	if (root->rightnode)  {

		arr[top] = 1;
		printCodes(root->rightnode, arr, top + 1, j);
	}
	 
	
	if (isLeaf(root) && j == root->c) {
		printArr(arr, top);
	}
}

void print_tree(node* r, int n, char* code) // 결과 허프만 알고리즘  트리 출력
{
	if (r) {
		n++;    // 트리의 깊이를 표시

		code[n] = '0';    // 트리의 좌측
		print_tree(r->leftnode, n, code);

		code[n] = '1';    // 트리의 우측
		print_tree(r->rightnode, n, code);

		code[n] = '\0';   // 찌꺼기 제거
		if (r->leftnode == NULL || r->rightnode == NULL)   // 자식이 있는 노드는 출력하지 않음
			printf("%s\n", code);
	}
}
int main()
{
	int num;
	scanf("%d", &num);
	int arr[1000];

	for (int i = 0; i < num; i++)
	{
		scanf("%d", &arr[i]);
	}

	node * root = Huffman(arr, num);
	node * fake = root;
	for (int i = 0; i < num; i++)
	{
		char arr1[1000], top = 0;
		printCodes(root, arr1, top, i);
	}

	return 0;

}