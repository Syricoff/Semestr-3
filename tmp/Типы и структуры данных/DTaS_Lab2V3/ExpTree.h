#ifndef EXPTREE_H
#define EXPTREE_H
#include <string>
#include <vector>
namespace ExpressionTree
{
	struct Node
	{
		char data;
		Node* left, * right;
	};
	class ExpTree
	{
	private:
		Node* root = nullptr;
		bool flag = false;
		int countElem = 0;
		std::string preorderS;
		std::string postorderS;
		std::string inorderS;
	public:
		std::string infixExp;
		Node* Create_Node(int);
		Node* Create_Node(Node*, Node*, int);
		Node* constructTree(std::string);
		int getPriority(char ch);
		std::string Convert_In_To_Post(std::string infix);

		void show_node(Node* T);
		void preorder(Node* T);
		void preorder_printing();
		void postorder(Node* T);
		void postorder_printing();
		void inorder(Node* T);
		void inorder_printing();
		void printTree();
		void delTree(Node*);
		void clearTree();
		void printNode(Node* t, int n);
		int getCountElement() const;
		void preorderF(Node* T);
		void inorderF(Node* T);
		void postorderF(Node* T);
		void WriteFile(std::string);
		void string_node(Node*, std::string&);

		bool IsExpCorrect(std::string infix);
		bool isOperator(char ch);
		bool isDigit(char c);

	};

}

#endif