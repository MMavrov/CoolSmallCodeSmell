template <class T>
struct Node {
	T inf;
	Node *left;
	Node *right;
};

template <class T>
class BinOrdTree
{
public:
	BinOrdTree();
	~BinOrdTree();
	BinOrdTree(const T&);
	BinOrdTree(const BinOrdTree&);
	BinOrdTree<T>& operator=(const BinOrdTree<T>&);

	void PrintSorted() const;

	void AddNode(const T&);
	void DeleteNode(const T&);
	void Create();

	bool empty() const;
	bool rootTree(T&) const;
	bool leftTree(BinOrdTree<T>&) const;
	bool rightTree(BinOrdTree<T>&) const;

private:
	Node<T> *root;
	void deleteTree(Node<T> *&);
	void del(Node<T> *&, const T&);
	void copyTree(Node<T> *&, const Node<T>*);
	void print(const Node<T> *);
	void add(Node<T> *&, const T&);
};

template <class T>
BinOrdTree<T>::BinOrdTree()
{
	root = NULL;
}

template <class T>
BinOrdTree<T>::~BinOrdTree()
{
	deleteTree(root);
}

template <class T>
BinOrdTree<T>::BinOrdTree(const T& x)
{
	root = new Node<T>;
	root->inf = x;
	root->left = root->rigt = NULL;
}

template <class T>
BinOrdTree<T>::BinOrdTree(const BinOrdTree<T> &t)
{
	copyTree(root, t.root);
}

template <class T>
BinOrdTree<T>& BinOrdTree<T>::operator=(const BinOrdTree<T> &t)
{
	if (this != &t)
	{
		deleteTree(root);
		copyTree(root, t.root);
	}
	return *this;
}

template <class T>
void BinOrdTree<T>::deleteTree(Node<T> *&t)
{
	if (t)
	{
		deleteBinOrdTree(t->left);
		deleteBinOrdTree(t->right);
		delete t;
		t = NULL;
	}
}

template <class T>
void BinOrdTree<T>::copyTree(Node<T> *&p, const Node<T> *t)
{
	if (t)
	{
		p = new Node<T>;
		p->inf = t->inf;

		if (t->left) copyTree(p->left, t->left);
		else p->left = NULL;

		if (t->right) copyTree(p->right, t->right);
		else p->right = NULL;
	}
}

template <class T>
bool BinOrdTree<T>::empty() const
{
	return root == NULL;
}

template <class T>
bool BinOrdTree<T>::rootTree(T &x) const
{
	if (!root) return false;
	x = root->inf;
	return true;
}

template<class T>
bool BinOrdTree<T>::leftTree(BinOrdTree<T> &t) const
{
	if (!root) return false;
	deleteTree(t.root);
	copyTree(t.root, root->left);
	return true;
}

template <class T>
bool BinOrdTree<T>::rightTree(BinOrdTree<T> &t) const
{
	if (!root) return false;
	deleteTree(t.root);
	copyTree(t.root, root->right);
	return true;
}

template <class T>
void BinOrdTree<T>::PrintSorted() const
{
	print(root);
	cout << endl;
}

template <class T>
void BinOrdTree<T>::print(const Node<T> *t)
{
	if (t)
	{
		print(t->left);
		cout << t->inf << " ";
		print(t->right);
	}
}

template <class T>
void BinOrdTree<T>::AddNode(const T& x)
{
	add(root, x);
}

template <class T>
void BinOrdTree<T>::add(Node<T> *&t, const T& x)
{
	if (!t)
	{
		t = new Node<T>;
		t->inf = x;
		t->left = t->right = NULL;
	}
	else if (x < t->inf) add(root->left, x);
	else if (x > t->inf) add(root->right, x);
	else cout << "Duplicate cannot be inserted!" << endl;
}

template <class T>
void BinOrdTree<T>::DeleteNode(const T& x)
{
	del(root, x);
}

template <class T>
void BinOrdTree<T>::del(Node<T> *&t, const T& x)
{
	if (!t) return;

	if (x < t->inf) del(t->left, x);
	else if (x > t->inf) del(t->right, x);
	else
	{
		Node<T> *p;
		if (!t->left)
		{
			p = t;
			t = t->right;
			delete p;
		}
		else if (!t->right)
		{
			p = t;
			t = t->left;
			delete p;
		}
		else
		{
			p = t->left;
			while (p->right) p = p->right;
			t->inf = p->inf;
			del(t->left, p->inf);
		}
	}
}

template<class T>
void BinOrdTree<T>::Create()
{
	deleteTree(root);
	T x;
	char c;
	do
	{
		cout << "Enter element:";
		cin >> x;
		AddNode(x);
		cout << "Enter more (y/n)?";
		cin >> c;
	} while (c == 'y' || c == 'Y')
}