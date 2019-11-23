#ifndef TREE_H
#define TREE_H


enum class TreeType {


	NON=-1,
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



class Tree
{
public:
	Tree();
	~Tree();

public:
	


};

class Node {

public:
	Node();
	~Node();



};




#endif//TREE__H_