#include "BinTree.h"

namespace ExpressionTree
{

	BinTree::BinTree() : root(nullptr) {}

	Node *BinTree::Create_Node(int info)
	{
		Node *temp = new Node();
		temp->left = nullptr;
		temp->right = nullptr;
		temp->data = info;
		return temp;
	}

	bool BinTree::IsEmpty() const
	{
		return root == nullptr;
	}

	void BinTree::Insert(int info)
	{
		root = InsertRec(root, info);
	}

	void BinTree::LevelOrderTraversal()
	{
		if (root == nullptr)
		{
			std::cout << "Дерево пустое\n";
			return;
		}
		std::queue<Node *> q;
		q.push(root);
		while (!q.empty())
		{
			Node *node = q.front();
			q.pop();
			std::cout << node->data << " ";
			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}
		std::cout << std::endl;
	}

	void BinTree::RemoveNegative()
	{
		root = RemoveNegativeRec(root);
	}

	void BinTree::PrintTree()
	{
		PrintTreeRec(root, 0);
	}

	void BinTree::WriteToFile(const std::string &filename)
	{
		std::ofstream out(filename);
		if (out.is_open())
		{
			WriteToFileRec(root, out);
			out.close();
			std::cout << "Дерево записано в файл: " << filename << std::endl;
		}
		else
		{
			std::cerr << "Не удалось открыть файл для записи.\n";
		}
	}

	void BinTree::Clear()
	{
		ClearRec(root);
		root = nullptr;
		std::cout << "Дерево успешно удалено.\n";
	}

	Node *BinTree::InsertRec(Node *node, int info)
	{
		if (node == nullptr)
		{
			return Create_Node(info);
		}
		if (info < node->data)
		{
			node->left = InsertRec(node->left, info);
		}
		else
		{
			node->right = InsertRec(node->right, info);
		}
		return node;
	}

	Node *BinTree::RemoveNegativeRec(Node *node)
	{
		if (node == nullptr)
			return nullptr;

		node->left = RemoveNegativeRec(node->left);
		node->right = RemoveNegativeRec(node->right);

		if (node->data < 0)
		{
			Node *temp = (node->left) ? node->left : node->right;
			delete node;
			return temp;
		}
		return node;
	}

	void BinTree::PrintTreeRec(Node *node, int depth)
	{
		if (node)
		{
			PrintTreeRec(node->right, depth + 1);
			std::cout << std::string(depth * 4, ' ') << node->data << std::endl;
			PrintTreeRec(node->left, depth + 1);
		}
	}

	void BinTree::WriteToFileRec(Node *node, std::ofstream &out)
	{
		if (node)
		{
			WriteToFileRec(node->left, out);
			out << node->data << std::endl;
			WriteToFileRec(node->right, out);
		}
	}

	void BinTree::ClearRec(Node *node)
	{
		if (node)
		{
			ClearRec(node->left);
			ClearRec(node->right);
			delete node;
		}
	}
}
