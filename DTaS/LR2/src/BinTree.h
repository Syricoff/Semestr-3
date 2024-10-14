#ifndef BINTREE_H
#define BINTREE_H

#include <fstream>
#include <iostream>
#include <queue>

namespace ExpressionTree
{

	struct Node
	{
		int data;
		Node *left;
		Node *right;
	};

	class BinTree
	{
	public:
		BinTree();
		bool IsEmpty() const;

		void Insert(int info);
		void LevelOrderTraversal();
		void RemoveNegative();
		void PrintTree();
		void WriteToFile(const std::string &filename);
		void Clear();

	private:
		Node *root;

		Node *Create_Node(int info);
		Node *InsertRec(Node *node, int info);
		Node *RemoveNegativeRec(Node *node);
		void PrintTreeRec(Node *node, int depth);
		void WriteToFileRec(Node *node, std::ofstream &out);
		void ClearRec(Node *node);
	};
}

#endif // BINTREE_H
