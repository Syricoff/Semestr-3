#include "DoubleList.h"

DoubleList::DoubleList()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

DoubleList::~DoubleList()
{
	if (IsEmpty())
	{
		return;
	}
	Node* curr = head->next;
	while (curr)
	{
		delete curr->prev;
		curr = curr->next;
	}
	delete tail;
}

bool DoubleList::IsEmpty() const
{
	return !size;
}

void DoubleList::PrintDoubleList() const
{
	std::cout << *this;
}

void DoubleList::PushBack(int data)
{
	Node* temp = new Node;
	temp->data = data;
	if (IsEmpty())
	{
		temp->prev = nullptr;
		head = temp;
	}
	else
	{
		tail->next = temp;
		temp->prev = tail;
	}
	temp->next = nullptr;
	tail = temp;
	size++;
}

void DoubleList::PushFront(int data)
{
	Node* temp = new Node;
	temp->data = data;
	if (IsEmpty())
	{
		temp->next = nullptr;
		tail = temp;
	}
	else
	{
		head->prev = temp;
		temp->next = head;
	}
	temp->prev = nullptr;
	head = temp;
	size++;
}

void DoubleList::Insert(size_t index, int data)
{
	if (index >= 0 && index <= size)
	{
		if (index == 0)
		{
			PushFront(data);
			return;
		}
		if (index == size)
		{
			PushBack(data);
			return;
		}
		Node* currLeft = head;
		for (int i = 0; i < index - 1; i++)
		{
			currLeft = currLeft->next;
		}
		Node* currRight = currLeft->next;
		Node* temp = new Node;
		temp->data = data;
		temp->prev = currLeft;
		temp->next = currRight;
		currLeft->next = temp;
		currRight->prev = temp;
		size++;
	}
}

void DoubleList::PopBack()
{
	if (IsEmpty())
	{
		return;
	}
	if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		size--;
		return;
	}
	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;
	size--;
}

void DoubleList::PopFront()
{
	if (IsEmpty())
	{
		return;
	}
	if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		size--;
		return;
	}
	head = head->next;
	delete head->prev;
	head->prev = nullptr;
	size--;
}

void DoubleList::Remove(size_t index)
{
	if (index >= 0 && index <= size)
	{
		if (IsEmpty())
		{
			return;
		}
		if (index == 0)
		{
			PopFront();
			return;
		}
		if (index == size - 1)
		{
			PopBack();
			return;
		}
		Node* currLeft = head;
		for (int i = 0; i < index - 1; i++)
		{
			currLeft = currLeft->next;
		}
		Node* currRight = currLeft->next->next;
		currLeft->next = currRight;
		delete currRight->prev;
		currRight->prev = currLeft;
		size--;
	}
}

void DoubleList::Clear()
{
	this->~DoubleList();
	head = nullptr;
	tail = nullptr;
	size = 0;
}

int DoubleList::FindElement(int data) const
{
	size_t index = 0;
	Node* curr = head;
	bool find = false;
	while (curr)
	{
		if (curr->data == data)
		{
			find = true;
			break;
		}
		curr = curr->next;
		index++;
	}
	return (find ? index : -1);
}

int DoubleList::RFindElement(int data) const
{
	size_t index = size - 1;
	Node* curr = tail;
	bool find = false;
	while (curr)
	{
		if (curr->data == data)
		{
			find = true;
			break;
		}
		curr = curr->prev;
		index--;
	}
	return (find ? index : -1);
}

size_t DoubleList::getSize() const
{
	return size;
}

DoubleList::Node* DoubleList::getHead() const
{
	return head;
}

DoubleList::Node* DoubleList::getTail() const
{
	return tail;
}

std::ostream& operator<<(std::ostream& out, const DoubleList& dl)
{
	DoubleList::Node* curr = dl.getHead();
	out << "[";
	while (curr)
	{
		out << curr->data << (curr->next ? ", " : "");
		curr = curr->next;
	}
	out << "] \nsize: " << dl.getSize() << "\n";
	return out;
}