#include "Tree.h"
#include "Gameobject.h"


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


void Tree::Intersects(std::vector<const Gameobject*>& collector, const AABB& area) {






}


Node::Node(AABB aabbNode,NodeType type, const Tree*Owner):aabbNode(aabbNode),nodeType(type), OwnerTree(Owner)
{



}


Node::~Node()
{
}



bool Node::Insert(const Gameobject* obj) {


	bool ret = false;
//Check if the node has the GO
	if (aabbNode.Contains(obj->aabb))
	{
		//check node type
		if (ImBranch)
		{
			//if branch get to leaf recursive 
			for (int i = 0; i < BranchesNum; ++i) {

				if (BranchesFromNode[i].Insert(obj))
				{
					ret = true;
					break;
				}


			}
		}
		//if leaf
		else
		{
			//Push the GO
			ret = true;
			GOinside.push_back(obj);
			
	
			//Chech for size, if aabb full split
			if (GOinside.size() > OwnerTree->NodesSize) {
				SplitQuat();


				bool placed = false;
				//if when splitting GO are not assigned to a child of the current node then store them
				std::vector<const Gameobject*> LeftGO;	

				for (int i = 0; i < GOinside.size(); ++i) {

					for (int j = 0; j < BranchesNum; ++j) {

						if (BranchesFromNode[j].Insert(GOinside[i])) {

							placed = true;
							break;

						}

					}
					
					if (placed)
						placed = false;
					else
						LeftGO.push_back(GOinside[i]);


				}

				if (LeftGO.size() != GOinside.size)
					GOinside = LeftGO;//check

			}
		}

	}
	return ret;
}
bool Node::Remove(const Gameobject* obj) {


	bool ret = false;

	if (aabbNode.Contains(obj->aabb)) {
		//if Branch
		if (ImBranch) {
			for (int i = 0; i < BranchesNum; i++) {
			//Remove childen nodes
				if (BranchesFromNode[i].Remove(obj)) {

					std::vector<const Gameobject*> Collector;

					for (i = 0; i < BranchesNum; i++) {

						if (BranchesFromNode[i].BranchesNum > 0) {	
						
							break;
						}
						else {	

							int nodeSize = BranchesFromNode[i].GOinside.size();

							if (nodeSize > 0) {
							
								for (int j = 0; j < nodeSize; j++) {
								
									Collector.push_back(BranchesFromNode[i].GOinside[j]);

								}

								/*if (GOinside.size() + Collector.size() > OwnerTree->NodesSize) {
								
									break;


								}*/
							}
						}
					}

					if (i == BranchesNum) {	 


						if (!Collector.empty()) {
							for (int k = 0; k < Collector.size(); k++) {

								GOinside.push_back(Collector[k]);
							}
						
						}
						
					}

					break;
									
				}
								
			}
					   
		}
		//if leaf
		else {

			for (int i = 0; i < GOinside.size(); i++) {
			
				if (GOinside[i] == obj) {
				
					GOinside.erase(GOinside.begin() + i);
					
					ret = true;
					break;
				
				}
			}

		}

	}
	




	return ret;
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

	BranchesNum = 4;
	ImBranch = true;
};





