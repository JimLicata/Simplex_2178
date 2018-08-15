
#include "Node.h"

bool visited;
int xPos;
int yPos;
int heuristic;
int index;
int step;
int weight;
Node* prev;
Node::Node()
{
	visited = false;
	xPos = 0;
	yPos = 0;
	heuristic = 5;
	index = 0;
	step = 0;
	weight = 1;
	prev = nullptr;
}

Node::Node(int x,int y,bool v, int h,int i, int w)
{
	xPos = x;
	yPos = y;
	visited = v;
	heuristic = h;
	fScore = 0;
	index = i;
	step = 0;
	weight = w;
	prev = nullptr;
}

Node::~Node()
{

}
