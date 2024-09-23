#pragma once
#include <iostream>

class DoubleList
{
public:
	struct Node
	{
		int data;
		Node* next;
		Node* prev;
	};

	DoubleList();
	~DoubleList();
	bool IsEmpty() const;
	void PrintDoubleList() const;
	void PushBack(int data);
	void PushFront(int data);
	void Insert(size_t index, int data);
	void PopBack();
	void PopFront();
	void Remove(size_t index);
	void Clear();
	int FindElement(int data) const;
	int RFindElement(int data) const;
	size_t getSize() const;
	Node* getHead() const;
	Node* getTail() const;
	friend std::ostream& operator<<(std::ostream& out, const DoubleList& dl);

private:
	Node* head;
	Node* tail;
	size_t size;
};