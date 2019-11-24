#ifndef TREE_H
#define TREE_H

#include "Globals.h"
#include "MathGeoLib/include/Geometry/AABB.h"
#include <vector>





enum class TreeType {


	NONE=-1,
	QUAT_TREE,
	OCT_TREE,
	KD_TREE,
	MAX

};

enum class NodeType {

	NONE = -1,
	ROOT_NODE,
	LEAF_NODE,
	MAX


};

class Gameobject;
class Node;


class Tree
{
public:
	Tree(AABB aabb, TreeType type, uint sizeNode);
	~Tree();

public:
	
	void Clear();

	void Draw();

	void Create(const AABB& RootSpace);
	bool Remove(const Gameobject* object);
	void Intersects(std::vector<const Gameobject*>& collector, const AABB& area);
	bool Insert(const Gameobject*object);


public:

	
	TreeType treeType = TreeType::NONE;
	Node* RootNode;
	uint NodesSize;
	std::vector<const Gameobject*> Trees_Obj;
	
};

class Node {

public:
	Node();
	Node(AABB aabbNode, NodeType type, const Tree*Owner);
	~Node();

public:

	bool Insert(const Gameobject* obj);
	bool Remove(const Gameobject* obj);
	void Clear();

	void Draw();

	void Intersects(std::vector<const Gameobject*>& collector, const AABB& area);

	void SplitQuat();
	
public:

	AABB aabbNode;
	NodeType nodeType;
	Node*BranchesFromNode = nullptr;
	uint BranchesNum = 0;
	const Tree* OwnerTree = nullptr;
	bool ImBranch = false;
	std::vector<const Gameobject*>GOinside;
};




#endif//TREE__H_