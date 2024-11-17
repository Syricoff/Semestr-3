#include "ExpTree.h"
#include "MyError.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <stack>
#include <cstdlib>


namespace ExpressionTree
{
	Node* ExpTree::Create_Node(int info)
	{
		Node* temp = new Node();
		temp->left = nullptr;
		temp->right = nullptr;
		temp->data = info;
		return temp;
	};
	Node* ExpTree::Create_Node(Node* left, Node* right, int info)
	{
		Node* temp = new Node;
		temp->left = left;
		temp->right = right;
		temp->data = info;
		return temp;
	};

	Node* ExpTree::constructTree(std::string infix)
	{
		infixExp = infix;
		std::string postfix = Convert_In_To_Post(infix);
		std::stack<Node*> s;
		int i = 0;
		Node* node;
		for (char c : postfix)
		{
			if (isOperator(c))
			{
				Node* x = s.top();
				s.pop();

				Node* y = s.top();
				s.pop();

				Node* node = Create_Node(y, x, c);
				s.push(node);
			}
			else
			{

				s.push(Create_Node(c));
			}
			countElem++;
			i++;
		}
		root = s.top();
		return root;
	}
	bool ExpTree::isDigit(char ch)
	{
		if (ch > 47 && ch < 57)
			return true;
		return false;
	}
	bool ExpTree::isOperator(char ch)
	{
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^')
			return true;
		return false;
	}
	bool ExpTree::IsExpCorrect(std::string infix)
	{
		for (unsigned int i = 0; i < infix.length(); i++)
		{
			if (!isDigit(infix[i]) && !isOperator(infix[i]) && infix[i] != '(' && infix[i] != ')')
				return false;
		}
		return true;
	}
	void ExpTree::show_node(Node* T)
	{
		std::cout << T->data << " ";
	}
	void ExpTree::preorder(Node* T)
	{
		if (T != nullptr)
		{
			show_node(T);
			preorder(T->left);
			preorder(T->right);
		}

	}
	void ExpTree::preorder_printing()
	{
		if (countElem != 0)
		{
			std::cout << "Префиксный обход" << std::endl;
			preorder(root);
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Дерево пустое\n";
		}

	}
	void ExpTree::postorder(Node* T)
	{
		if (T != nullptr)
		{
			postorder(T->left);
			postorder(T->right);
			show_node(T);
		}
	}
	void ExpTree::postorder_printing()
	{
		if (countElem != 0)
		{
			std::cout << "Постфиксный обход" << std::endl;
			postorder(root);
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Дерево пустое\n";
		}



	}
	void ExpTree::inorder(Node* T)
	{
		if (T != NULL)
		{
			inorder(T->left);
			show_node(T);
			inorder(T->right);
		}
	}
	void ExpTree::inorder_printing()
	{
		if (countElem != 0)
		{
			std::cout << "Инфиксный обход" << std::endl;
			inorder(root);
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Дерево пустое\n";
		}

	}
	int ExpTree::getPriority(char ch)
	{
		switch (ch)
		{
		case '^':
			return 4;
		case '%':
			return 3;
		case '/':
		case '*':
			return 2;
		case '+':
		case '-':
			return 1;
		default:
			return 0;
		}
	}
	void ExpTree::delTree(Node* tr)
	{
		if (tr != nullptr)
		{
			delTree(tr->left);
			delTree(tr->right);
			delete tr;
			countElem = 0;
		}
	}
	void ExpTree::clearTree()
	{
		delTree(root);
		std::cout << "Дерево успешно удалено\n";
	}

	void ExpTree::printTree()
	{
		if (countElem != 0)
		{
			printNode(root, 0);
		}
		else
		{
			std::cout << "Дерево пустое\n";
		}

	}


	void ExpTree::printNode(Node* t, int n)
	{
		if (t)
		{
			printNode(t->right, n + 2);
			for (int i = 0; i < n; i++)
			{
				std::cout << " ";
			}
			std::cout << t->data;
			printNode(t->left, n + 2);
		}
		else
		{
			std::cout << std::endl;
		}

	}


	int ExpTree::getCountElement() const
	{
		return countElem;
	}
	std::string ExpTree::Convert_In_To_Post(std::string infix)
	{
		std::string postfix;
		unsigned int counter1 = 0;
		std::stack<char> st;
		int postCount = 0;
		char element;
		while (counter1 < infix.length())
		{
			element = infix[counter1];
			if (element == '(')
			{
				st.push(element);
				counter1++;
				continue;
			}
			if (element == ')')
			{
				while (!st.empty() && st.top() != '(')
				{
					postfix.push_back(st.top());
					st.pop();
				}
				if (!st.empty())
				{
					st.pop();
				}
				counter1++;
				continue;
			}

			if (getPriority(element) == 0)
			{
				postfix.push_back(element);
			}
			else
			{
				if (st.empty())
				{
					st.push(element);
				}
				else
				{
					while (!st.empty() && st.top() != '(' &&
						getPriority(element) <= getPriority(st.top()))
					{
						postfix.push_back(st.top());
						st.pop();
					}
					st.push(element);
				}
			}
			counter1++;
		}

		while (!st.empty())
		{
			postfix.push_back(st.top());
			st.pop();
		}
		return postfix;
	}

	void ExpTree::WriteFile(std::string nameFile)
	{
		std::ofstream out;
		out.open(nameFile, std::ios::out);
		preorderF(root);
		inorderF(root);
		postorderF(root);
		if (out.is_open())
		{
			if (!flag)
			{
				out << preorderS << std::endl;
				out << inorderS << std::endl;
				out << postorderS << std::endl;

				out.close();
				std::cout << "Запись в файл завершена!" << std::endl;
				flag = true;
			}

		}
		else
		{
			throw MyError{ "File didn't open" };
		}
	}
	void ExpTree::string_node(Node* T, std::string& line)
	{
		line.push_back(T->data);
	}
	void ExpTree::preorderF(Node* T)
	{
		if (T != nullptr)
		{
			string_node(T, preorderS);
			preorderF(T->left);
			preorderF(T->right);
		}

	}
	void ExpTree::inorderF(Node* T)
	{
		if (T != nullptr)
		{
			inorderF(T->left);
			string_node(T, inorderS);
			inorderF(T->right);
		}

	}
	void ExpTree::postorderF(Node* T)
	{
		if (T != nullptr)
		{
			postorderF(T->left);
			postorderF(T->right);
			string_node(T, postorderS);

		}

	}

}