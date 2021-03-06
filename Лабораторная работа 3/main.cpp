#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <stack>
using namespace std;

typedef struct Node {
	int data;
	struct Node* next;
}Node;

Node* init(int num)
{
	Node* list; 
	list = (Node*)malloc(sizeof(Node));
	list->data = num;
	list->next = NULL;
	return list;
}

Node* add(Node* list, int num)
{
	Node* p, * temp;
	temp = (Node*)malloc(sizeof(Node));
	p = list->next;
	list->next = temp;
	temp->data = num;
	temp->next = p;
	return temp;
}

int** create_arr(int n)
{
	int s = 1;
	int **Arr;

	Arr = (int**)malloc(n * sizeof(int*));
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		Arr[i] = (int*)malloc(n * sizeof(int));
		Arr[i][i] = 0;

		for (int j = s; j < n; j++)
		{
			if (rand() % 100 > 10)
			{
				Arr[i][j] = 0;
			}
			else {
				Arr[i][j] = 1;
			}	
		}
		s++;
	}
	s = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = s; j < n; j++)
			Arr[j][i] = Arr[i][j];
		s++;
	}

	for (int i = 0; i < n; i++)
		printf("V%d ", i + 1);

	for (int i = 0; i < n; i++)
	{
		printf("\n");
		for (int j = 0; j < n; j++)
		{
			printf("%2d ", Arr[i][j]);
		}
	}
	return Arr;
}

void DFS(int** Arr, int n, bool* Arr2, int i)
{
	Arr2[i] = true;
	printf("%d ", i + 1);
	for (int j = 0; j < n; j++)
	{
		if (Arr[i][j] == 1 && Arr2[j] == false)
			DFS(Arr, n, Arr2, j);
	}
}

void Free(int** Arr, bool* Arr2, int n, Node** sp1)
{
	for (int i = 0; i < n; i++)
		free(Arr[i]);
	free(Arr);
	free(Arr2);
}

void fun_init(Node** sp1, int n)
{
	for (int i = 0; i < n; i++)
		sp1[i] = init(i);
}

void spisok(int n, int** Arr, Node* list, int i)
{
	for (int j = n; j > 0; j--)
	{
		if (Arr[i][j] == 1)
			add(list, j);
	}
}

void fun_spisok(Node** sp1, int n, int** Arr)
{
	for (int i = 0; i < n; i++)
		spisok(n, Arr, sp1[i], i);
}

void print_spisok(Node** sp1, int n)
{
	for (int i = 0; i < n; i++)
	{
		Node* adr = sp1[i];
		printf("\n");
		for (int j = 0; j < n; j++)
		{
			if (sp1[i] != NULL) 
			{ 
				printf("%*d", 3, sp1[i]->data + 1); 
				sp1[i] = sp1[i]->next; 
			}
		}
		sp1[i] = adr;
	}
}

void DFS_spisok(Node** sp1, bool* Arr2, int n, int i)
{
	int j;
	Arr2[i] = true;
	printf("%d ", i + 1);
	while (sp1[i]->next != NULL)
	{
		sp1[i] = sp1[i]->next;
		j = sp1[i]->data;
		if (Arr2[j] == false) 
			DFS_spisok(sp1, Arr2, n, j);
	}
}

void stk(int n, int** Arr, int i, int* nodes)
{
	stack<int> stk;
	int x;

	stk.push(i);
	printf("\nResult komponenta: ");
	while (!stk.empty())
	{
		int node = stk.top();
		stk.pop();
		if (nodes[node] == 2)
			continue;
		nodes[node] = 2;
		for (int j = n - 1; j >= 0; j--)
		{
			if (Arr[node][j] == 1 && nodes[j] != 2)
			{
				stk.push(j);
				nodes[j] = 1;
			}
		}
		printf("%d ", node + 1);
	}
}

void STK_K(int n, int** Arr)
{
	int* nodes = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		nodes[i] = 0;

	for (int i = 0; i < n; i++)
	{
		if (nodes[i] == 0) 
			stk(n, Arr, i, nodes);
	}
}

int main()
{
	setlocale(LC_ALL, "Ru");
	
	int n, **t;
	bool* Arr2;

	printf("Vvedite razmer arr: ");
	scanf("%d", &n);

	Node** sp1 = (Node**)malloc(n * sizeof(Node*));
	Arr2 = (bool*)malloc(n * sizeof(bool));

	for (int i = 0; i < n; i++)
		Arr2[i] = false;
	t = create_arr(n);

	printf("\nResult obhoda arr smachnosty: ");
	DFS(t, n, Arr2, 0);

	fun_init(sp1, n);
	fun_spisok(sp1, n, t);
	printf("\n");
	print_spisok(sp1, n);

	printf("\nResult obhoda cherez sprisok: ");
	for (int i = 0; i < n; i++)
		Arr2[i] = false;
	DFS_spisok(sp1, Arr2, n, 0);

	STK_K(n, t);

	Free(t, Arr2, n, sp1);
	_getch();
}
