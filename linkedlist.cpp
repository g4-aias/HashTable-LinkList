#include "linkedlist.h"


// Default Constructor
LinkedList::LinkedList()
{
	head = NULL;
	size = 0;
}

// Copy Constructor
LinkedList::LinkedList(const LinkedList& ll)
{
	CopyList(ll);
}

// Copy Helper
void LinkedList::CopyList(const LinkedList& ll)
{
	// do stuff
	if (ll.head == NULL)
	{
		head = NULL;
		size = 0;
	}
	else
	{
		// make a copy of the head first
		head = new Node(ll.head->data,NULL);

		Node* temp = head;
		Node* lltemp = ll.head;
		Node* node;

		while(lltemp->next != NULL)
		{
			lltemp = lltemp->next;
			node = new Node(lltemp->data, NULL);
			temp->next = node;
			temp = temp->next;
		}

		size = ll.size;
	}

}

// Destructor
LinkedList::~LinkedList()
{
	RemoveAll();
}

LinkedList& LinkedList::operator=(const LinkedList& ll)
{
	if (this == &ll)
		return *this;
	else
	{
		RemoveAll();
		CopyList(ll);
		return *this;
	}
}
  
void LinkedList::Insert(string s)
{
	if (size == 0 && head == NULL)
	{
		head = new Node(s,NULL);
		size++;
	}
	else if (Contains(s) == false) // no duplicates allowed
	{
		Node* node;

		node = new Node(s,head);
		head = node;

		size++;
	}
	
}

bool LinkedList::Remove(string s)
{
	// only remove the string if the list contains the string
	if(Contains(s) == false) 
		return false;
	else
	{
		Node* temp = head;
		Node* prev;
		
		// if head contains the string
		if (temp->data == s)
		{
			if (head->next == NULL)
			{
				delete head;
				head = NULL;
			}
			else
			{
				head = head->next;
				delete temp;
			}
		}
		else
		{
			while (temp->next != NULL)
			{
				if ((temp->next)->data != s) // look ahead before traversing
					temp = temp->next; 
				else
				{
					if ((temp->next)->next == NULL) // checks if it's the last node to be deleted
					{
						prev = temp;
						temp = temp->next;
						delete temp;

						prev->next = NULL;
						break;
					}
					else // general case
					{
						Node* front = temp;
						temp = temp->next;
						Node* back = temp->next;

						front->next = back;
						
						delete temp;
						break;
					}
				}
			}
		}
	}

	size--;
	return true;
}

bool LinkedList::Contains(string s) const
{

	if (head != NULL && size > 0)
	{
		Node* temp = head;

		// initial data check
		if (temp->data == s)
			return true;

		// traverse through the linked list
		while (temp->next != NULL)
		{
			temp = temp->next;

			if(temp->data == s)
				return true;
		}
	}

	return false;
}

void LinkedList::RemoveAll()
{
	if (head != NULL)
	{
		Node* temp = head;

		while (head->next != NULL)
		{
			head = head->next;
			delete temp;
			temp = head;
			size--;
		}

		delete head;
		head = NULL;
		size--;
	}

}

unsigned int LinkedList::Size() const
{
	return size;
}

vector<string> LinkedList::Dump() const
{
	vector<string> v; //creates an empty vector

	if (head != NULL && size > 0)
	{
		Node* temp = head;
		v.push_back(temp->data); // creates initial data

		while (temp->next != NULL) // traverse list
		{
			temp = temp->next;
			v.push_back(temp->data);
		}
	}

	return v;
}