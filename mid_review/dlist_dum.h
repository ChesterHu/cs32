// Double link list with dummy node.
typedef int ItemType;

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
			Node* prev;
			Node* next;
		};
		
		Node* head;
};

// Default constructor
List::List()
{
	head = new Node;
	head->next = nullptr;
	head->prev = nullptr;
}

// Copy constructor
List::List(const List& other)
{
	head = new Node;
	head->next = nullptr;
	head->prev = nullptr;
	
	Node* p = head;
	for (Node* iter = other.head->next; iter != nullptr; iter = iter->next)
	{
		// Allocate new Node, copy data and connect to list.
		p->next = new Node;
		p->next->data = iter->data;
		p->next->next = nullptr;
		p->next->prev = p;
		// Move to next Node.
		p = p->next;
	}
}

// Deconstructor
List::~List()
{
	while (head != nullptr)
	{
		Node* iter = head;
		head = head->next;
		// No dangling pointer.
		if (head != nullptr)
			head->prev = nullptr;

		delete iter;
	}
}

// Assignment operator
List& List::operator=(const List& rhs)
{
	if (this != &rhs)
	{
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
	Node* iter = head;
	for (; iter->next != nullptr && iter->next->data < value; iter = iter->next);

	// If need insert
	if (iter->next == nullptr || iter->data != value)
	{
		Node* newGuy = new Node;
		newGuy->data = value;
		newGuy->next = iter->next;
		newGuy->prev = iter;
		if (iter->next != nullptr)
			iter->next->prev = newGuy;
		iter->next = newGuy;
		return true;
	}
	// Otherwise, no insert.
	return false;
}

bool List::erase(const ItemType value)
{
	Node* iter = head->next;
	for (; iter != nullptr && iter->data != value; iter = iter->next);
	
	// If no need erase
	if (iter == nullptr)
		return false;
	// erase node pointed by iter.
	iter->prev->next = iter->next;
	// If followed by a node.
	if (iter->next != nullptra)
		iter->next->prev = iter->prev;
	delete iter;
	
	return true;
}
