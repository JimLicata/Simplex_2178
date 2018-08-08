#include "MyOctant.h"
using namespace Simplex;

uint MyOctant::octantCount = 0;
uint MyOctant::maxLevel = 3;
uint MyOctant::idealEntityCount = 5;

void Simplex::MyOctant::Init(void)
{
	children = 0;
	size = 0.0f;
	ID = octantCount;
	level = 0;
	v3Center = vector3(0.0f);
	v3Max = vector3(0.0f);
	v3Min = vector3(0.0f);
	root = nullptr;
	parent = nullptr;
	meshMngr = MeshManager::GetInstance();
	entityMngr = MyEntityManager::GetInstance();

	for (uint i = 0; i < 8; i++)
	{
		child[i] = nullptr;
	}
}

Simplex::MyOctant::MyOctant(uint maxLvl, uint idealEntityCnt)
{
	Init();
	octantCount = 0;
	maxLevel = maxLvl;
	idealEntityCount = idealEntityCnt;
	ID = octantCount;
	root = this;
	childList.clear();

	std::vector<vector3> minMax;

	uint objects = entityMngr->GetEntityCount();
	for (uint i = 0; i < objects; i++)
	{
		MyEntity* entity = entityMngr->GetEntity(i);
		MyRigidBody* rigidBody = entity->GetRigidBody();
		minMax.push_back(rigidBody->GetMinGlobal());
		minMax.push_back(rigidBody->GetMaxGlobal());
	}
	MyRigidBody* rigidBody = new MyRigidBody(minMax);

	vector3 halfWidth = rigidBody->GetHalfWidth();
	float max = halfWidth.x;
	for (uint i = 0; i < 3; i++)
	{
		if (max < halfWidth[i])
		{
			max = halfWidth[i];
		}
	}
	vector3 center = rigidBody->GetCenterLocal();
	minMax.clear();
	SafeDelete(rigidBody);
	v3Center = center;
	v3Max = v3Center + vector3(max);
	v3Min = v3Center - vector3(max);
	size = max * 2.0f;

	octantCount++;
	ConstructTree(maxLevel);
}

Simplex::MyOctant::MyOctant(vector3 center, float sz)
{
	Init();
	size = sz;
	v3Center = center;
	v3Max = v3Center + vector3(size) / 2.0f;
	v3Min = v3Center - vector3(size) / 2.0f;
	octantCount++;
}

Simplex::MyOctant::MyOctant(MyOctant const& other)
{
	v3Center = other.v3Center;
	v3Max = other.v3Max;
	v3Min = other.v3Min;
	childList = other.childList;
	size = other.size;
	ID = other.ID;
	level = other.level;
	children = other.children;
	root = other.root;
	meshMngr = MeshManager::GetInstance();
	entityMngr = MyEntityManager::GetInstance();
	for (uint i = 0; i < 8; i++)
	{
		child[i] = other.child[i];
	}
}

MyOctant& Simplex::MyOctant::operator=(MyOctant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	} 
	return *this;
}

Simplex::MyOctant::~MyOctant(void)
{
	Release();
}

void Simplex::MyOctant::Swap(MyOctant & other)
{
	std::swap(children, other.children);
	std::swap(ID, other.ID);
	std::swap(root, other.root);
	std::swap(childList, other.childList);
	std::swap(v3Center, other.v3Center);
	std::swap(v3Max, other.v3Max);
	std::swap(v3Min, other.v3Min);
	meshMngr = MeshManager::GetInstance();
	entityMngr = MyEntityManager::GetInstance();

	std::swap(level, other.level);
	std::swap(parent, other.parent);
	for (uint i = 0; i < 8; i++)
	{
		std::swap(child[i], other.child[i]);
	}
}

float Simplex::MyOctant::GetSize(void)
{
	return size;
}

vector3 Simplex::MyOctant::GetCenterGlobal(void)
{
	return v3Center;
}

vector3 Simplex::MyOctant::GetMinGlobal(void)
{
	return v3Min;
}

vector3 Simplex::MyOctant::GetMaxGlobal(void)
{
	return v3Max;
}

bool Simplex::MyOctant::IsColliding(uint RBIndex)
{
	uint numOfObjects = entityMngr->GetEntityCount();
	if (RBIndex >= numOfObjects)
		return false;

	MyEntity* entity = entityMngr->GetEntity(RBIndex);
	MyRigidBody* rigidBody = entity->GetRigidBody();
	vector3 max = rigidBody->GetMaxGlobal();
	vector3 min = rigidBody->GetMinGlobal();

	// check for collisions in the x direction
	if (v3Max.x < min.x) return false;
	if (v3Min.x > max.x) return false;

	// check for collisions in the y direction
	if (v3Max.y < min.y) return false;
	if (v3Min.y > max.y) return false;

	// check for collisions in the z direction
	if (v3Max.z < min.z) return false;
	if (v3Min.z > max.z) return false;

	// if all checks fail
	return true;
}

void Simplex::MyOctant::Display(uint index, vector3 color)
{
	if (ID == index)
	{
		meshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, v3Center) * glm::scale(vector3(size)), color, RENDER_WIRE);
		return;
	}
	for (uint i = 0; i < children; i++)
	{
		child[i]->Display(index);
	}
}

void Simplex::MyOctant::Display(vector3 color)
{
	for (uint i = 0; i < children; i++)
	{
		child[i]->Display(color);
	}
	meshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, v3Center) * glm::scale(vector3(size)), color, RENDER_WIRE);
}

void Simplex::MyOctant::DisplayLeafs(vector3 color)
{
	uint numOfLeafs = childList.size();
	for (uint i = 0; i < numOfLeafs; i++)
	{
		childList[i]->DisplayLeafs(color);
	}
	meshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, v3Center) * glm::scale(vector3(size)), color, RENDER_WIRE);
}

void Simplex::MyOctant::ClearEntityList(void)
{
	for (uint i = 0; i < children; i++)
	{
		child[i]->ClearEntityList();
	}
	entityList.clear();
}

void Simplex::MyOctant::Subdivide(void)
{
	if (level >= maxLevel) return;

	if (children != 0) return;

	children = 8;

	float halfSize = size / 2.0f;
	float quatSize = size / 4.0f;
	vector3 center;

	// bottom left far
	center = v3Center;
	center.x -= quatSize;
	center.y -= quatSize;
	center.z -= quatSize;
	child[0] = new MyOctant(center, halfSize);

	// bottom left near
	center.z += halfSize;
	child[1] = new MyOctant(center, halfSize);

	// bottom right near
	center.x += halfSize;
	child[2] = new MyOctant(center, halfSize);

	// bottom right far
	center.z -= halfSize;
	child[3] = new MyOctant(center, halfSize);

	// top right far
	center.y += halfSize;
	child[4] = new MyOctant(center, halfSize);

	// top left far
	center.x -= halfSize;
	child[5] = new MyOctant(center, halfSize);

	// top left near
	center.z += halfSize;
	child[6] = new MyOctant(center, halfSize);

	// top right near
	center.x += halfSize;
	child[7] = new MyOctant(center, halfSize);

	for (uint  i = 0; i < 8; i++)
	{
		child[i]->root = root;
		child[i]->level = level + 1;
		child[i]->parent = this;
		if (child[i]->ContainsMoreThan(idealEntityCount))
		{
			child[i]->Subdivide();
		}
	}
}

MyOctant * Simplex::MyOctant::GetChild(uint index)
{
	if (index > 7)
		return nullptr;

	else 
		return child[index];
}

MyOctant * Simplex::MyOctant::GetParent(void)
{
	return parent;
}

bool Simplex::MyOctant::IsLeaf(void)
{
	if (children == 0)
		return true;

	else
		return false;
}

bool Simplex::MyOctant::ContainsMoreThan(uint entities)
{
	uint count = 0;
	uint numOfObjects = entityMngr->GetEntityCount();
	for (uint i = 0; i < numOfObjects; i++)
	{
		if (IsColliding(i))
		{
			count++;
		}
		if (count > entities)
		{
			return true;
		}
	}
	return false;
}

void Simplex::MyOctant::KillBranches(void)
{
	for (uint i = 0; i < children; i++)
	{
		child[i]->KillBranches();
		delete child[i];
		child[i] = nullptr;
	}
	children = 0;
}

void Simplex::MyOctant::ConstructTree(uint maxLvl)
{
	if (level != 0) return;

	maxLevel = maxLvl;
	octantCount = 1;

	entityList.clear();

	KillBranches();
	childList.clear();

	if (ContainsMoreThan(idealEntityCount))
	{
		Subdivide();
	}

	AssignIDtoEntity();

	ConstructList();

}

void Simplex::MyOctant::AssignIDtoEntity(void)
{
	for (uint i = 0; i < children; i++)
	{
		child[i]->AssignIDtoEntity();
	}
	if (children == 0)
	{
		uint numOfEntities = entityMngr->GetEntityCount();
		for (uint i = 0; i < numOfEntities; i++)
		{
			if (IsColliding(i))
			{
				entityList.push_back(i);
				entityMngr->AddDimension(i, ID);
			}
		}
	}
}

uint Simplex::MyOctant::GetOctantCount(void)
{
	return octantCount;
}

void Simplex::MyOctant::Release(void)
{
	if (level == 0)
	{
		KillBranches();
	}
	childList.clear();
	entityList.clear();
	children = 0;
	size = 0;
}



void Simplex::MyOctant::ConstructList(void)
{
	for (uint i = 0; i < children; i++)
	{
		child[i]->ConstructList();
	}

	if (entityList.size() > 0)
	{
		root->childList.push_back(this);
	}
}
