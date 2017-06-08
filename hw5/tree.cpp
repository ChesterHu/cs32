#include <iostream>
using namespace std;


class tree
{
	public:
		  // constructor
		tree() : m_root(nullptr) {}
		  // destructor
		~tree() { delete m_root; }
		  // insert new node
		void insertNode(const int val);
		  // inorder
		void inorder() { inorderPrint(m_root); }
	private:
		struct Node
		{
			int data;
			Node* parent;
			Node* left;
			Node* right;

			Node(int val)
			{
				data = val;
				parent = left = right = nullptr;
			}

			~Node()
			{
				delete left;
				delete right;
			}

		};

		void inorderPrint(Node* root);
		Node* m_root;
};

void tree::insertNode(const int val)
{
	Node** ptr = &m_root;   // a pointer points to the pointer of a tree Node
	Node* curr = nullptr;           // the parent of current tree Node
	
	while(*ptr != nullptr)                                                // while the pointer ptr is not nullptr
	{
		if ((*ptr)->data == val)                                          // if the pointed pointer's data equals to the target value, return
			return;
		curr = *ptr;                                                    // assign the pointed pointer to the parent pointer
		ptr = (curr->data > val) ? &(curr->left) : &(curr->right);  // if target value is less than the current Node's value, then let ptr point to the left pointer, 
	}                                                                     // otherwise point to the right pointer.
	*ptr = new Node(val);    // allocate new Node on the pointed pointer
	(*ptr)->parent = curr; // let new Node's parent points to current Node.
}

void tree::inorderPrint(Node* root)
{
	if (root != nullptr)
	{
		inorderPrint(root->left);
		cout << " " << root->data;
		inorderPrint(root->right);
	}
}

int main()
{
	tree a;
	a.insertNode(50);
	a.insertNode(20);
	a.insertNode(60);
	a.insertNode(10);
	a.insertNode(40);
	a.insertNode(70);
	a.insertNode(15);
	a.insertNode(30);
	a.insertNode(65);
	a.insertNode(80);
	a.insertNode(1);
	a.insertNode(0);
	a.inorder();
	cout << endl;
}
