// Circular double list without dummy node.
typedef int ItemTpye;

class List
{
	public:
		List();
		List(const List& other);
		~List();
		List& operator=(const List& rhs);

		bool insert(const ItemType value);
		bool erase(const ItemType value);
	
	private:
		struct Node
		{
			ItemType data;
			Node* next;
			Node* prev;
		}
		Node* head;
}

// Default constructor
List::List()
{
	head = nullptr;
}

// Copy constructor
List::List(const List& other)
{
	head = nullptr;
	// If copy from an empty list.
	if (other.head == nullptr)
		return;
	head = new Node;
	head->data = other.head->data;
	head->next = head;
	head->prev = head;
	
	// Copy the rest of the list
	Node* ptr = head;
	for (Node* iter = other.head->next; iter != other.head; iter = iter->next)
	{
		Node* newGuy = new Node;
		// Connect to list.
		newGuy->next = p->next;
		newGuy->prev = p;
		// Modify list connection.
		p->next->prev = newGuy;
		p->next = newGuy;
	}	
}

// Deconstructor
List::~List()
{
	if (head == nullptr)
		return;
	// Break the circle.
	head->prev->next = nullptr;
	head->prev = nullptr;
	// Free memory.
	while (head != nullptr)
	{
		Node* p = head;
		head = head->next;
		// No dangling pointer.
		if (head != nullptr)
			head->prev = nullptr;
		delete p;
	}
}

// Assignment operator
List& List::operator=(const List& rhs)
{
	if (this != &rhs)
	{
		// Copy
		List temp(rhs);
		// Swap
		Node* temp_ptr = temp.head;
		temp.head = head;
		head = temp_ptr;
	}

	return *this;
}

// Insert
bool List::insert(const ItemType& value)
{
	// If empty list
	if (head == nullptr)
	{
		head = new Node;
		head->data = value;
		head->next = head;
		head->prev = head;
		return true;
	}

	Node* iter = head;
	while (iter->data < value)
	{
		iter = iter->next;
		if (iter == head)
			break;
	}
	if (iter->data == value)
		return false;
	// Insert
	Node* newGuy = new Node;
	newGuy->data = value;
	// Connect to list
	newGuy->next = iter;
	newGuy->prev = iter->prev;
	// Modify list connection
	iter->prev->next = newGuy;
	iter->prev = newGuy;

	return true;
}

// Erase
bool List::erase(const ItemTpye& value)
{
	// If empty list.
	if (head == nullptr)
		return false;
	
	Node* iter = head;
	while (iter->data != value)
	{
		iter = iter->next;
		if (iter == head)
			return false;
	}

	// If remove head node
	if (iter == head)
	{
		// If only one node
		if (head->next == head)
		{
			head = nullptr;
			delete iter;

			return true;
		}
		head = head->next;
	}
	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;
	delete iter;

	return true;

}
