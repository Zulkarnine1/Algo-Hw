//our c++ implementation of 8 puzzle
#include <bits/stdc++.h> //remember to adapt this path
using namespace std;
#define N 3

// state space tree nodes
struct Node
{

	Node* prt;


	int mat[N][N];


	int x, y;

	int cost;


	int level;
};

// Function to print N x N matrix
int printMatrix(int mat[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}


Node* newNode(int mat[N][N], int x, int y, int newX,
			int newY, int level, Node* prt)
{
	Node* node = new Node;


	node->prt = prt;

	memcpy(node->mat, mat, sizeof node->mat);


	swap(node->mat[x][y], node->mat[newX][newY]);

	node->cost = INT_MAX;

	node->level = level;


	node->x = newX;
	node->y = newY;

	return node;
}

// botton, left, top, right
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };


int calculateCost(int initial[N][N], int final[N][N])
{
	int count = 0;
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
		if (initial[i][j] && initial[i][j] != final[i][j])
		count++;
	return count;
}


int isSafe(int x, int y)
{
	return (x >= 0 && x < N && y >= 0 && y < N);
}

void printPath(Node* root)
{
	if (root == NULL)
		return;
	printPath(root->prt);
	printMatrix(root->mat);

	printf("\n");
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
	}
};

void solve(int initial[N][N], int x, int y,
		int final[N][N])
{

	priority_queue<Node*, std::vector<Node*>, comp> pq;

	// create a root node and calculate its cost
	Node* root = newNode(initial, x, y, x, y, 0, NULL);
	root->cost = calculateCost(initial, final);

	// Add root to list of live nodes;
	pq.push(root);

	while (!pq.empty())
	{
		// Find a live node with least estimated cost
		Node* min = pq.top();


		pq.pop();


		if (min->cost == 0)
		{

			printPath(min);
			return;
		}


		for (int i = 0; i < 4; i++)
		{
			if (isSafe(min->x + row[i], min->y + col[i]))
			{

				Node* child = newNode(min->mat, min->x,
							min->y, min->x + row[i],
							min->y + col[i],
							min->level + 1, min);
				child->cost = calculateCost(child->mat, final);

				// Add child to list of live nodes
				pq.push(child);
			}
		}
	}
}


int main()
{
	int initial[N][N] =
	{
		{1, 2, 3},
		{5, 6, 0},
		{7, 8, 4}
	};


	int final[N][N] =
	{
		{1, 2, 3},
		{5, 8, 6},
		{0, 7, 4}
	};


	int x = 1, y = 2;

	solve(initial, x, y, final);

	return 0;
}
