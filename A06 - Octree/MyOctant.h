#ifndef __MYOCTANTCLASS_H_
#define __MYOCTANTCLASS_H_

#include "MyEntityManager.h"

namespace Simplex
{
	class MyOctant
	{
		static uint octantCount;
		static uint maxLevel;
		static uint idealEntityCount;

		uint ID = 0;
		uint level = 0;
		uint children = 0;

		float size = 0.0f;

		MeshManager* meshMngr = nullptr;
		MyEntityManager* entityMngr = nullptr;

		vector3 v3Center = vector3(0.0f);
		vector3 v3Min = vector3(0.0f);
		vector3 v3Max = vector3(0.0f);

		MyOctant* parent = nullptr;
		MyOctant* child[8];

		std::vector<uint> entityList;

		MyOctant* root = nullptr;
		std::vector<MyOctant*> childList;

	public:
		MyOctant(uint maxLvl = 2, uint idealEntityCnt = 5);
		MyOctant(vector3 center, float sz);
		MyOctant(MyOctant const& other);
		MyOctant& operator=(MyOctant const& other);
		~MyOctant(void);
		void Swap(MyOctant& other);
		float GetSize(void);
		vector3 GetCenterGlobal(void);
		vector3 GetMinGlobal(void);
		vector3 GetMaxGlobal(void);
		bool IsColliding(uint RBIndex);
		void Display(uint index, vector3 color = C_YELLOW);
		void Display(vector3 color = C_YELLOW);
		void DisplayLeafs(vector3 color = C_YELLOW);
		void ClearEntityList(void);
		void Subdivide(void);
		MyOctant* GetChild(uint index);
		MyOctant* GetParent(void);
		bool IsLeaf(void);
		bool ContainsMoreThan(uint entities);
		void KillBranches(void);
		void ConstructTree(uint maxLevel = 3);
		void AssignIDtoEntity(void);
		uint GetOctantCount(void);

	private:
		void Release(void);
		void Init(void);
		void ConstructList(void);


	};
}
#endif
