#include "Tree.h"



Tree::Tree(AABB aabb, TreeType type, uint sizeNode):treeType(type),NodesSize(sizeNode)
{

	RootNode = new Node(aabb,NodeType::ROOT_NODE,this);


}


Tree::~Tree()
{

}
void Tree::Draw(){

}
void Tree::Clear() {



}


void Tree::Create(const AABB& limits) {


}
bool Tree::Remove(const Gameobject* object) {



	return true;
}
bool Tree::Insert(const Gameobject*object) {


	return true;
}

void Tree::Intersects(std::vector<const Gameobject*>& collector, const AABB& area) {






}


Node::Node(AABB aabbNode,NodeType type, const Tree*Owner):aabbNode(aabbNode),nodeType(type), OwnerTree(Owner)
{



}


Node::~Node()
{
}



bool Node::Insert(const Gameobject* obj) {

	


	return true;
}
bool Node::Remove(const Gameobject* obj) {

	return true;
}
void Node::Clear(){



}

void Node::Intersects(std::vector<const Gameobject*>& collector, const AABB& area) {





}
void Node::SplitQuat() {

	/*

	----Z
	|		
	X		----------- 
			| NW | NE |
			|---------|
			| SW | SE |
			-----------
	
	*/

	AABB auxAABBs[4];
	BranchesFromNode = new Node[4];

	//SE
	auxAABBs[0].maxPoint = {aabbNode.MaxX(), aabbNode.MaxY(), aabbNode.MaxZ() };
	auxAABBs[0].minPoint = {(aabbNode.MaxX() + aabbNode.MinX())*0.5f , aabbNode.MinY(), (aabbNode.MaxZ() + aabbNode.MinZ())*0.5f };
				
	//NE
	auxAABBs[1].maxPoint = { (aabbNode.MaxX() + aabbNode.MinX())*0.5f, aabbNode.MaxY(), aabbNode.MaxZ() };
	auxAABBs[1].minPoint = { aabbNode.MinX(), aabbNode.MinY(), (aabbNode.MaxZ() + aabbNode.MinZ())*0.5f };
				
	//SW
	auxAABBs[2].maxPoint = { aabbNode.MaxX(), aabbNode.MaxY(),(aabbNode.MaxZ() + aabbNode.MinZ())*0.5f };
	auxAABBs[2].minPoint = { (aabbNode.MaxX() + aabbNode.MinX())*0.5f, aabbNode.MinY(), aabbNode.MinZ() };
			
	//NW
	auxAABBs[3].maxPoint = { (aabbNode.MaxX() + aabbNode.MinX())*0.5f, aabbNode.MaxY(),(aabbNode.MaxZ() + aabbNode.MinZ())*0.5f };
	auxAABBs[3].minPoint = { aabbNode.MinX(), aabbNode.MinY(), aabbNode.MinZ() };


	for (int i = 0; i < 4;++i) {
	BranchesFromNode[i] = Node(auxAABBs[i],NodeType::LEAF_NODE,OwnerTree);
	}


};





