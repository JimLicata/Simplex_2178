
#include "AppClass.h"

void Application::InitVariables(void)
{

	//Creating our lists and nodes
	openList = new std::vector<Node*>();
	closedList = new std::vector<Node*>();
	adjacentNodes = new std::vector<Node*>();
	path = new std::vector<Node*>();
	startNode = new Node();
	endNode = new Node();
	currNode = new Node();

	//Initialize models

	//pipe
	m_pPipe = new Model();
	m_pPipe->Load("Mario\\WarpPipe.obj");
	m_pPipeRB = new MyRigidBody(m_pPipe->GetVertexList());

	//steve
	m_pSteve = new Model();
	m_pSteve->Load("Minecraft\\Steve.obj");
	m_pSteveRB = new MyRigidBody(m_pSteve->GetVertexList());

	//init the mesh
	m_uMeshCount1 = 36;
	m_uWallCount1 = 11;
	for (uint i = 0; i < m_uMeshCount1; i++)
	{
		MyMesh* pMesh = new MyMesh();
		m_pMeshList1.push_back(pMesh);
		m_pMeshList1[i]->GenerateCube(1.0f, C_BLUE_CORNFLOWER);
	}

	for (uint i = 0; i < m_uWallCount1; i++)
	{
		MyMesh* pMesh = new MyMesh();
		m_pWallList1.push_back(pMesh);
		m_pWallList1[i]->GenerateCube(1.0f, C_INDIGO);
	}


	//Set model matrix to the pipe
	matrix4 mPipe = glm::translate(IDENTITY_M4, vector3(3.0f, 1.5f, 3.0f)) * glm::scale(IDENTITY_M4, vector3(0.3f)) * glm::rotate(IDENTITY_M4, glm::radians(180.0f), vector3(1.0f, 0.0f, 0.0f)); // scales, rotates, and translates the pipe to fit in the end position
	m_pPipe->SetModelMatrix(mPipe);
	m_pPipeRB->SetModelMatrix(mPipe);


	//Set model matrix to Steve
	matrix4 mSteve = glm::translate(IDENTITY_M4, vector3(0.0f, 0.5f, 0.0f));
	m_pSteve->SetModelMatrix(mSteve);
	m_pSteveRB->SetModelMatrix(mSteve);

	
	int width = 0;
	// ones are the path and zeroes are the walls
	if (first) // maze 1
	{
		int mazeData[6][6] =
		{
			{1, 1, 1, 1, 0, 0},
			{1, 0, 0, 1, 1, 0},
			{1, 1, 1, 0, 1, 1},
			{1, 0, 0, 1, 0, 1},
			{1, 1, 0, 1, 1, 1},
			{1, 1, 1, 0, 1, 1}
		};
		width = 6;

		//Creating adjacency matrix
		for (size_t i = 0; i < 6; i++)
		{
			for (size_t j = 0; j < 6; j++)
			{
				if (mazeData[i][j] == 1)
				{

					Node* n = new Node(i, j, false, 1, nodeCounter, mazeData[i][j]);
					nodeCounter++;
					nodes.push_back(n);
				}

			}
		}
		//Initializing Adjmatrix 
		adjMatrix = new int*[nodes.size()];
		for (size_t i = 0; i < nodes.size(); i++)
		{
			adjMatrix[i] = new int[nodes.size()];
			for (size_t j = 0; j < nodes.size(); j++)
			{

				adjMatrix[i][j] = 0;

			}
		}
	}

	else // maze 2
	{
		int mazeData[9][9] =
		{
			{1, 1, 1, 1, 1, 1, 1, 1, 1},
			{0, 0, 0, 1, 1, 0, 1, 0, 1},
			{1, 1, 0, 0, 1, 0, 1, 0, 1},
			{0, 1, 1, 0, 1, 0, 1, 0, 1},
			{1, 0, 1, 0, 0, 1, 1, 0, 0},
			{1, 0, 1, 0, 0, 1, 0, 1, 1},
			{1, 0, 1, 0, 1, 1, 0, 1, 0},
			{1, 1, 0, 1, 0, 1, 1, 1, 0},
			{0, 1, 1, 1, 1, 1, 0, 1, 0}
		};
		width = 9;

		//Creating adjacency matrix
		for (size_t i = 0; i < 6; i++)
		{
			for (size_t j = 0; j < 6; j++)
			{
				if (mazeData[i][j] == 1)
				{

					Node* n = new Node(i, j, false, 1, nodeCounter, mazeData[i][j]);
					nodeCounter++;
					nodes.push_back(n);
				}

			}
		}
		//Initializing Adjmatrix 
		adjMatrix = new int*[nodes.size()];
		for (size_t i = 0; i < nodes.size(); i++)
		{
			adjMatrix[i] = new int[nodes.size()];
			for (size_t j = 0; j < nodes.size(); j++)
			{

				adjMatrix[i][j] = 0;

			}
		}
	}
	startPosX = 0;
	startPosY = 0;
	endPosX = 3;
	endPosY = 3;
						
	SetNode();
	SetEdges();
	
}

void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	matrix4 mSteve = glm::translate(m_v3Steve) * ToMatrix4(m_qSteve) * ToMatrix4(m_qArcBall);
	m_pSteve->SetModelMatrix(mSteve);
	m_pSteveRB->SetModelMatrix(mSteve);

	static bool bColliding = m_pPipeRB->IsColliding(m_pSteveRB);
	if (bColliding)
	{
		std::cout << "Colliding" << std::endl;
	}
	AStar();

}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	//calculate the current position
	vector3 v3CurrentPos;

	// add path to the stopsList for LERP
	for (uint i = 0; i < path->size(); i++)
	{
		vector3 tmp = vector3((*path)[i]->yPos * 1.0f, 0.5f, (*path)[i]->xPos * 1.0f); // convert the x and y positions to a vector that can be used for the stopsList
		m_stopsList.push_back(tmp);
	}

	//LERP
	v3CurrentPos = vector3(0.0f, 0.0f, 0.0f);
	vector3 v3Start, v3End;
	static uint route = 0;
	v3Start = m_stopsList[route];
	v3End = m_stopsList[(route + 1) % m_stopsList.size()];

	float fTimeBetweenStops = 1.0f;
	float fPercentage = MapValue(fTimer, 0.0f, fTimeBetweenStops, 0.0f, 1.0f);

	v3CurrentPos = glm::lerp(v3Start, v3End, fPercentage);

	if (fPercentage >= 1.0f)
	{
		route++;
		fTimer = m_pSystem->GetDeltaTime(uClock);
		route %= m_stopsList.size();
	}
	
	matrix4 m4Steve = glm::translate(v3CurrentPos);
	m_pSteve->SetModelMatrix(m4Steve);
	m_pSteveRB->SetModelMatrix(m4Steve);

	m_pPipe->AddToRenderList();
	m_pSteve->AddToRenderList();

	

	if (first) // if the first maze is called
	{
		// creates maze 1
		matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f, 0.0f, 0.0f)); // start
		matrix4 m4Model = m4Translate;
		m_pMeshList1[0]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMeshList1[1]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMeshList1[2]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMeshList1[3]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMeshList1[4]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f, 1.0f, 0.0f));
		m4Model = m4Translate;
		m_pWallList1[0]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMeshList1[5]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f, 1.0f, 0.0f));
		m4Model = m4Translate;
		m_pWallList1[1]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f, 0.0f, 1.0f));
		m4Model = m4Translate;
		m_pMeshList1[6]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f, 0.0f, 1.0f));
		m4Model = m4Translate;
		m_pMeshList1[7]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f, 1.0f, 1.0f));
		m4Model = m4Translate;
		m_pWallList1[2]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f, 0.0f, 1.0f));
		m4Model = m4Translate;
		m_pMeshList1[8]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f, 1.0f, 1.0f));
		m4Model = m4Translate;
		m_pWallList1[3]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f, 0.0f, 1.0f));
		m4Model = m4Translate;
		m_pMeshList1[9]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f, 0.0f, 1.0f));
		m4Model = m4Translate;
		m_pMeshList1[10]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f, 0.0f, 1.0f));
		m4Model = m4Translate;
		m_pMeshList1[11]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f, 1.0f, 1.0f));
		m4Model = m4Translate;
		m_pWallList1[4]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f, 0.0f, 2.0f));
		m4Model = m4Translate;
		m_pMeshList1[12]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f, 0.0f, 2.0f));
		m4Model = m4Translate;
		m_pMeshList1[13]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f, 0.0f, 2.0f));
		m4Model = m4Translate;
		m_pMeshList1[14]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f, 0.0f, 2.0f));
		m4Model = m4Translate;
		m_pMeshList1[15]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f, 1.0f, 2.0f));
		m4Model = m4Translate;
		m_pWallList1[5]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f, 0.0f, 2.0f));
		m4Model = m4Translate;
		m_pMeshList1[16]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f, 0.0f, 2.0f));
		m4Model = m4Translate;
		m_pMeshList1[17]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f, 0.0f, 3.0f));
		m4Model = m4Translate;
		m_pMeshList1[18]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f, 0.0f, 3.0f));
		m4Model = m4Translate;
		m_pMeshList1[19]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f, 1.0f, 3.0f));
		m4Model = m4Translate;
		m_pWallList1[6]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f, 0.0f, 3.0f));
		m4Model = m4Translate;
		m_pMeshList1[20]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f, 1.0f, 3.0f));
		m4Model = m4Translate;
		m_pWallList1[7]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f, 0.0f, 3.0f)); // goal
		m4Model = m4Translate;
		m_pMeshList1[21]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f, 0.0f, 3.0f));
		m4Model = m4Translate;
		m_pMeshList1[22]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f, 1.0f, 3.0f));
		m4Model = m4Translate;
		m_pWallList1[8]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f, 0.0f, 3.0f));
		m4Model = m4Translate;
		m_pMeshList1[23]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f, 0.0f, 4.0f));
		m4Model = m4Translate;
		m_pMeshList1[24]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f, 0.0f, 4.0f));
		m4Model = m4Translate;
		m_pMeshList1[25]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f, 0.0f, 4.0f));
		m4Model = m4Translate;
		m_pMeshList1[26]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f, 1.0f, 4.0f));
		m4Model = m4Translate;
		m_pWallList1[9]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f, 0.0f, 4.0f));
		m4Model = m4Translate;
		m_pMeshList1[27]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f, 0.0f, 4.0f));
		m4Model = m4Translate;
		m_pMeshList1[28]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f, 0.0f, 4.0f));
		m4Model = m4Translate;
		m_pMeshList1[29]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(0.0f, 0.0f, 5.0f));
		m4Model = m4Translate;
		m_pMeshList1[30]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(1.0f, 0.0f, 5.0f));
		m4Model = m4Translate;
		m_pMeshList1[31]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(2.0f, 0.0f, 5.0f));
		m4Model = m4Translate;
		m_pMeshList1[32]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f, 0.0f, 5.0f));
		m4Model = m4Translate;
		m_pMeshList1[33]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(3.0f, 1.0f, 5.0f));
		m4Model = m4Translate;
		m_pWallList1[10]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(4.0f, 0.0f, 5.0f));
		m4Model = m4Translate;
		m_pMeshList1[34]->Render(m4Projection, m4View, m4Model);

		m4Translate = glm::translate(IDENTITY_M4, vector3(5.0f, 0.0f, 5.0f));
		m4Model = m4Translate;
		m_pMeshList1[35]->Render(m4Projection, m4View, m4Model);
	}


	

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}

void Application::AStar(void)
{
	//Finding the max heuristic
	priority = CalcH(startNode);
	//Push openList to start
	openList->push_back(startNode);
	//Set the current Node that goes through the scan to the start
	currNode = (*openList).front();
	//Adding the start to the closed list so it does not go back to the start
	(*closedList).push_back(startNode);
	//Looping until the last adjacent node put it is the end node
	while ((*openList).back() != endNode && nodesCheck<2001)
	{
		//Clear adjacent Nodes of previous Node found after we calculate where the currNode should  go
		adjacentNodes->clear();

		//Getting all unvisited neighbors
		GetUnvisitedNeighbor(currNode);

		for (int i = 0; i < adjacentNodes->size(); i++)
		{
			//Calculating cost for each adjacentNodes
			for (size_t j = 0; j < adjacentNodes->size(); j++)
			{
				(*adjacentNodes)[j]->fScore += currNode->step + (*adjacentNodes)[j]->weight;
			}


			//If a neighbor is in closed List and the closedList fScore is less than the neighbor is popped off the closed List
			if (Contains(closedList, (*adjacentNodes)[i]) == true && (*closedList)[loc]->fScore < (*adjacentNodes)[i]->step)
			{
				currNode = closedList->back();
				(*closedList).erase(closedList->begin() + i);
			}
			//If neighbor is neither in closed or openList calculate the priority
			if (!Contains(openList, (*adjacentNodes)[i]) && !Contains(closedList, (*adjacentNodes)[i]))
			{
				int lowestDifference = 100000;
				int indexForPriority = i;
				int cost = 0;
				//Calculating priority for all the adjacent Nodes
				for (size_t j = 0; j < adjacentNodes->size(); j++)
				{
					//Since we are looping If it is not in openList or not in closedList, found new path calculate cost and see if it is closer square
					if (!Contains(openList, (*adjacentNodes)[j]) && !Contains(closedList, (*adjacentNodes)[j]))
					{
						cost = (*adjacentNodes)[j]->fScore + CalcH((*adjacentNodes)[j]);
						int absoluteCost = priority - cost;
						absoluteCost = abs(absoluteCost);

						if (absoluteCost < lowestDifference)
						{
							int temp = priority - cost;
							lowestDifference = abs(temp);
							indexForPriority = j;
						}
						//Add the closest square to the openList 
						openList->push_back((*adjacentNodes)[indexForPriority]);
					}

				}
				//Move the currNode to the closestsquare and add step and make visited true
				currNode = (*adjacentNodes)[indexForPriority];
				currNode->step = (*adjacentNodes)[indexForPriority]->fScore;
				currNode->visited = true;
				//Push currNode up to closedList
				closedList->push_back(currNode);

				break;

			}
		}
		//If we hit a dead end go through our closedList until we find an adjacentNode in the openList we havent visited
		while (adjacentNodes->size() == 0)
		{
			closedList->pop_back();
			currNode = closedList->back();
			GetUnvisitedNeighbor(currNode);


			if (Contains(openList, currNode))
			{
				openList->erase(openList->begin() + loc);
			}
		}

		//If the currentNode is in the endNode's position push it up to the closedList		
		if (currNode->xPos == endPosX && currNode->yPos == endPosY)
		{
			closedList->push_back(currNode);
			//And then push it upt our path list
			for (size_t i = 0; i < closedList->size(); i++)
			{
				path->push_back((*closedList)[i]);
			}
			break;
		}
		nodesCheck++;
	}
}

//The method that checks if Node n is in the list
bool Application::Contains(std::vector<Node*>* list, Node * n)
{
	for (size_t i = 0; i < list->size(); i++)
	{
		if (n == (*list)[i])
		{
			//To remove from openList and closedList we set a global variable loc to the index where it found it so we can reference that specific Node
			loc = i;
			return true;
		}
	}
	return false;
}

//Getting unvisited neighbor by comparing the node n with the index of the adjacence matrix
void Application::GetUnvisitedNeighbor(Node * n)
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (adjMatrix[n->index][nodes[i]->index] == 1 && nodes[i]->visited == false)
		{
			adjacentNodes->push_back(nodes[i]);
		}
	}

}

//Calculating the heuristic using a Node given
int Application::CalcH(Node* n)
{
	int heuristic = 0;
	int x = abs(endPosX - n->xPos);
	int y = abs(endPosY - n->yPos);
	n->heuristic = x + y;
	return abs(n->heuristic);
}

// Setting start Node and and end Node 
void Application::SetNode()
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (startPosX == nodes[i]->xPos && startPosY == nodes[i]->yPos)
		{
			startNode = nodes[i];

		}

		if (endPosX == nodes[i]->xPos && endPosY == nodes[i]->yPos)
		{
			endNode = nodes[i];
		}

	}
}

// Creating adjacency matrix
void Application::SetEdges()
{

	for (size_t i = 0; i < nodes.size(); i++)
	{
		for (size_t j = 0; j < nodes.size(); j++)
		{
			if ((nodes[i]->xPos + 1) == nodes[j]->xPos&&nodes[i]->yPos == nodes[j]->yPos)
			{
				adjMatrix[i][j] = 1;

			}
			else if ((nodes[i]->xPos - 1) == nodes[j]->xPos && nodes[i]->yPos == nodes[j]->yPos)
			{
				adjMatrix[i][j] = 1;
			}
			else if ((nodes[i]->xPos) == nodes[j]->xPos && nodes[i]->yPos + 1 == nodes[j]->yPos)
			{
				adjMatrix[i][j] = 1;
			}
			else if ((nodes[i]->xPos) == nodes[j]->xPos && (nodes[i]->yPos - 1) == nodes[j]->yPos)
			{
				adjMatrix[i][j] = 1;
			}
			else
			{
				adjMatrix[i][j] = 0;
			}

		}
	}

	//Printing out adjmatrix for debugging
	
	for (size_t i = 0; i < nodes.size(); i++)
	{
	for (size_t j = 0; j < nodes.size(); j++)
	{
	std::cout << adjMatrix[i][j] << ' ';
	}
	std::cout << std::endl;
	}
	
}
void Application::Release(void)
{
	for (uint i = 0; i < m_uMeshCount1; i++)
	{
		SafeDelete(m_pMeshList1[i]);
	}

	for (uint i = 0; i < m_uWallCount1; i++)
	{
		SafeDelete(m_pWallList1[i]);
	}
	
	for (size_t i = 0; i < nodes.size(); i++)
	{
		SafeDelete(nodes[i]);
	}
	SafeDelete(currNode);
	SafeDelete(endNode);
	SafeDelete(startNode);
	SafeDelete(adjMatrix);
	for (size_t i = 0; i < openList->size(); i++)
	{
		SafeDelete((*openList)[i]);
	}
	for (size_t i = 0; i < closedList->size(); i++)
	{
		SafeDelete((*closedList)[i]);
	}
	SafeDelete(adjacentNodes);

	//release the model
	SafeDelete(m_pPipe);

	//release the rigid body for the model
	SafeDelete(m_pPipeRB);

	//release the model
	SafeDelete(m_pSteve);

	//release the rigid body for the model
	SafeDelete(m_pSteveRB);
	//release GUI
	ShutdownGUI();
}