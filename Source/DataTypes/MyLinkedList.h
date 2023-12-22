#pragma once

// LinearList<> is a dynamic container for storing objects.
// It behaves similar to std::vector<> but does not store data
// contiguously. Instead each object is stored within a Node<>
// which is created on the heap whenever a new item is added
// to the list.

// The advantages of LinkedList<> relate to item adding and removing.
// Removing items from the middle of the list is simple and does
// not leave a "hole" or NULL value. Also, unlike std::vector<>,
// LinkedList<> does not need to allocate, move, and delete memory
// when it needs to grow larger. Instead a new Node<> is created and
// linked to the appropriate nodes.

// Simplicity
// Efficiency

/*
	TODO:
	_List::Iterator;
	_Next() { current = current->next; }
*/

template <class LIST_OBJECT_TYPE>
struct _ListNode
{
	LIST_OBJECT_TYPE value;
	_ListNode<LIST_OBJECT_TYPE>* next = nullptr;
	_ListNode<LIST_OBJECT_TYPE>* prev = nullptr;

	_ListNode() {}
	_ListNode(LIST_OBJECT_TYPE value1) { value = value1; }
	// ~Node() { delete value; }; // Memory management
};

// TODO:: Find a better name
// 2WayNodeList, Line2List, DynamicLinkList, AaronsListSomething...
//
template <class LIST_OBJECT_TYPE>
class Linear2LinkedList
{
public:
	Linear2LinkedList();
	~Linear2LinkedList();

	LIST_OBJECT_TYPE Front();
	LIST_OBJECT_TYPE Back();

	void PushFront(LIST_OBJECT_TYPE item);
	void PushBack(LIST_OBJECT_TYPE item);
	void PushBack(LIST_OBJECT_TYPE* items, int size);
	void InsertBefore(int index, LIST_OBJECT_TYPE item);

	LIST_OBJECT_TYPE Withdraw(int index); // delete node, return value
	void Remove(int index);
	void Remove(LIST_OBJECT_TYPE object);
	// TODO:: Additional ways of removing such as value comparison
	// void Remove() {}; // remove by value?

	LIST_OBJECT_TYPE At(int index);
	int Size();

	void PopBack() { if(m_Count > -1) Remove(m_Count - 1); };
	void PopFront() { if (m_Count > -1) Remove(0); };

	void Clear();

	/* Additional features*/
	// Greatest at back
	void SortAscending() {}; // TODO::
	// Greatest at front
	void SortDescending() {}; // TODO::
	// incline/decline
	LIST_OBJECT_TYPE* CreateArray(); // Create an array containing items

private:
	_ListNode<LIST_OBJECT_TYPE>* m_Head = nullptr; // first
	int m_Count = 0;

	_ListNode<LIST_OBJECT_TYPE>* _NodeAtIndex(int index);
	void _PrintValues();
};

template <class LIST_OBJECT_TYPE>
Linear2LinkedList<LIST_OBJECT_TYPE>::Linear2LinkedList()
{
}

template <class LIST_OBJECT_TYPE>
Linear2LinkedList<LIST_OBJECT_TYPE>::~Linear2LinkedList()
{
	// Do not delete objects in Destructor.
	// Stack variables will try to delete their values when
	// you may not want them to. Example...
	// List t_List = Scene->GetList();
	// t_List will try to delete the Scene's list values when
	// it goes out of scope.
	// Better to manually call Clear() in the Scene's Destructor.
}

template <class LIST_OBJECT_TYPE>
LIST_OBJECT_TYPE Linear2LinkedList<LIST_OBJECT_TYPE>::Front()
{
	return m_Head->value;
}

template <class LIST_OBJECT_TYPE>
LIST_OBJECT_TYPE Linear2LinkedList<LIST_OBJECT_TYPE>::Back()
{
	return _NodeAtIndex(m_Count - 1)->value;
}

template <class LIST_OBJECT_TYPE>
void Linear2LinkedList<LIST_OBJECT_TYPE>::PushFront(LIST_OBJECT_TYPE item)
{
	// add to front
	_ListNode<LIST_OBJECT_TYPE>* t_NewNode = new _ListNode<LIST_OBJECT_TYPE>(item);
	m_Head->prev = t_NewNode;
	t_NewNode->next = m_Head;
	m_Head = t_NewNode;
	m_Count++;
}

template <class LIST_OBJECT_TYPE>
void Linear2LinkedList<LIST_OBJECT_TYPE>::PushBack(LIST_OBJECT_TYPE item)
{
	// add to end
	_ListNode<LIST_OBJECT_TYPE>* t_Node = new _ListNode<LIST_OBJECT_TYPE>(item);
	if (m_Count == 0)
	{
		m_Head = t_Node;
	}
	else
	{
		_ListNode<LIST_OBJECT_TYPE>* t_EndNode = _NodeAtIndex(m_Count - 1);
		t_EndNode->next = t_Node;
		t_Node->prev = t_EndNode;
	}
	m_Count++;
}
template <class LIST_OBJECT_TYPE>
void Linear2LinkedList<LIST_OBJECT_TYPE>::PushBack(LIST_OBJECT_TYPE* items, int size)
{
	for (int i = 0; i < size; i++)
	{
		PushBack(items[i]);
	}
}

template <class LIST_OBJECT_TYPE>
void Linear2LinkedList<LIST_OBJECT_TYPE>::InsertBefore(int index, LIST_OBJECT_TYPE item)
{
	_ListNode<LIST_OBJECT_TYPE>* t_LaterValue = _NodeAtIndex(index); // get later node
	_ListNode<LIST_OBJECT_TYPE>* t_NewNode = new _ListNode<LIST_OBJECT_TYPE>(item); // create new node
	// set prev/next pointers
	_ListNode<LIST_OBJECT_TYPE>* t_Holder = t_LaterValue->prev; // save ->prev pointer
	// set old nodes
	t_LaterValue->prev = t_NewNode;
	t_Holder->next = t_NewNode;
	// set new node
	t_NewNode->next = t_LaterValue;
	t_NewNode->prev = t_Holder;

	if (index == 0) { m_Head = t_NewNode; }
	m_Count++;
}

template <class LIST_OBJECT_TYPE>
LIST_OBJECT_TYPE Linear2LinkedList<LIST_OBJECT_TYPE>::Withdraw(int index)
{
	_ListNode<LIST_OBJECT_TYPE>* t_DeadNode = _NodeAtIndex(index);
	_ListNode<LIST_OBJECT_TYPE>* t_Front = t_DeadNode->prev;
	_ListNode<LIST_OBJECT_TYPE>* t_Back = t_DeadNode->next;
	// change next/prev pointers
	if (index == 0) // front
	{
		t_Back->prev = nullptr;
		m_Head = t_Back;
	}
	else if (index == m_Count - 1) // end
	{
		t_Front->next == nullptr;
	}
	else // middle
	{
		t_Front->next = t_Back;
		t_Back->prev = t_Front;
	}

	m_Count--;
	return t_DeadNode->value; // beware the memory!
}

template <class LIST_OBJECT_TYPE>
void Linear2LinkedList<LIST_OBJECT_TYPE>::Remove(int index)
{
	if (m_Count == 0) { return; } // Can't remove if list is empty
	_ListNode<LIST_OBJECT_TYPE>* t_DeadNode = _NodeAtIndex(index);
	_ListNode<LIST_OBJECT_TYPE>* t_Front = t_DeadNode->prev;
	_ListNode<LIST_OBJECT_TYPE>* t_Back = t_DeadNode->next;
	// change next/prev pointers
	if (index == 0) // front
	{
		if (m_Count == 1)
		{
			m_Head = nullptr;
		}
		else
		{
			t_Back->prev = nullptr;
			m_Head = t_Back;
		}
	}
	else if (index == m_Count - 1) // end
	{
		t_Front->next = nullptr;
	}
	else // middle
	{
		t_Front->next = t_Back;
		t_Back->prev = t_Front;
	}

	if (m_Count == 0) { m_Head = nullptr; }

	delete t_DeadNode;
	m_Count--;
}

template <class LIST_OBJECT_TYPE>
void Linear2LinkedList<LIST_OBJECT_TYPE>::Remove(LIST_OBJECT_TYPE object)
{
	for (int i = 0; i < m_Count; i++)
	{
		if (At(i) == object) // Compare values
		{
			Remove(i);
			return;
		}
	}
}

template <class LIST_OBJECT_TYPE>
LIST_OBJECT_TYPE Linear2LinkedList<LIST_OBJECT_TYPE>::At(int index)
{
	return _NodeAtIndex(index)->value;
}

template <class LIST_OBJECT_TYPE>
int Linear2LinkedList<LIST_OBJECT_TYPE>::Size()
{
	return m_Count;
}
template <class LIST_OBJECT_TYPE>
void Linear2LinkedList<LIST_OBJECT_TYPE>::Clear()
{
	int size = m_Count; // m_Count changes
	for (int i = 0; i < size; i++)
	{
		PopBack();
	}
}
// private
template <class LIST_OBJECT_TYPE>
_ListNode<LIST_OBJECT_TYPE>* Linear2LinkedList<LIST_OBJECT_TYPE>::_NodeAtIndex(int index)
{
	// if (index > m_Count - 1) { OutputMessage("\nLinear2LinkedList: At(index) index out of range!\n"); assert(0); } // out of range
	_ListNode<LIST_OBJECT_TYPE>* t_Iterator = m_Head;

	for (int i = 0; i < index; i++)
	{
		t_Iterator = t_Iterator->next;
	}

	return t_Iterator;
}
template <class LIST_OBJECT_TYPE>
void Linear2LinkedList<LIST_OBJECT_TYPE>::_PrintValues()
{
	_ListNode<LIST_OBJECT_TYPE>* t_Iterator = m_Head;
	// OutputMessage("\nList Values: ");
	for (int i = 0; i < m_Count; i++)
	{
		// OutputMessage("%i, ", t_Iterator->value);
		t_Iterator = t_Iterator->next;
	}
}

template <class LIST_OBJECT_TYPE>
LIST_OBJECT_TYPE* Linear2LinkedList<LIST_OBJECT_TYPE>::CreateArray()
{
	// !beware the memory!
	LIST_OBJECT_TYPE* t_Array = new LIST_OBJECT_TYPE[m_Count]; // Unhandled allocation
	return t_Array;
}
