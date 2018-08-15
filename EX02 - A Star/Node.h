#pragma once
class Node
{
public:
	Node();
	Node(int x , int y, bool visit, int h,int index, int w);
	
	int xPos;
	int yPos;
	bool visited;
	int index;
	int heuristic;
	int step;
	int fScore;
	int weight;
	Node* prev;
	~Node();
};

