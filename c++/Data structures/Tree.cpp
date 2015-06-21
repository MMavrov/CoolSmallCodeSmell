template <class T>
struct Node {
	T inf;
	Node *left;
	Node *right;
};

template <class T>
class Tree
{
public:
	Tree();
	~Tree();
	Tree(const T&);
	Tree(const Tree&);
	Tree<T>& operator=(const Tree<T>&);

	void Create();
	void Create3(const T&, const Tree<T>&, const Tree<T>&);
	void Preorder();
	void Inorder();
	void Postorder();

	bool empty() const;
	bool rootTree(T&) const;
	bool leftTree(Tree<T>&) const;
	bool rightTree(Tree<T>&) const;

private:
	Node<T> *root;
	void deleteTree(Node<T> *&);
	void copyTree(Node<T> *&, const Node<T>*);
	void preorder(const Node<T> *);
	void postorder(const Node<T> *);
	void inorder(const Node<T> *);
	void createTree(Node<T> *&);
};

template <class T>
Tree<T>::Tree()
{
	root = NULL;
}

template <class T>
Tree<T>::~Tree()
{
	deleteTree(root);
}

template <class T>
Tree<T>::Tree(const T& x)
{
	root = new Node<T>;
	root->inf = x;
	root->left = root->rigt = NULL;
}

template <class T>
Tree<T>::Tree(const Tree<T> &t)
{
	copyTree(root, t.root);
}

template <class T>
Tree<T>& Tree<T>::operator=(const Tree<T> &t)
{
	if (this != &t)
	{
		deleteTree(root);
		copyTree(root, t.root);
	}
	return *this;
}

template <class T>
void Tree<T>::deleteTree(Node<T> *&t)
{
	if (t)
	{
		deleteTree(t->left);
		deleteTree(t->right);
		delete t;
		t = NULL;
	}
}

template <class T>
void Tree<T>::copyTree(Node<T> *&p, const Node<T> *t)
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
bool Tree<T>::empty() const
{
	return root == NULL;
}

template <class T>
bool Tree<T>::rootTree(T &x) const
{
	if (!root) return false;
	x = root->inf;
	return true;
}

template<class T>
bool Tree<T>::leftTree(Tree<T> &t) const
{
	if (!root) return false;
	deleteTree(t.root);
	copyTree(t.root, root->left);
	return true;
}

template <class T>
bool Tree<T>::rightTree(Tree<T> &t) const
{
	if (!root) return false;
	deleteTree(t.root);
	copyTree(t.root, root->right);
	return true;
}

template <class T>
void Tree<T>::Preorder()
{
	preorder(root);
	cout << endl;
}

template <class T>
void Tree<T>::Inorder()
{
	inorder(root);
	cout << endl;
}

template <class T>
void Tree<T>::Postorder()
{
	postorder(root);
	cout << endl;
}

template <class T>
void Tree<T>::preorder(const Node<T> *t)
{
	if (t)
	{
		cout << t->inf << " ";
		preorder(t->left);
		preorder(t->right);
	}
}

template <class T>
void Tree<T>::inorder(const Node<T> *t)
{
	if (t)
	{
		preorder(t->left);
		cout << t->inf << " ";
		preorder(t->right);
	}
}

template <class T>
void Tree<T>::postorder(const Node<T> *t)
{
	if (t)
	{
		preorder(t->left);
		preorder(t->right);
		cout << t->inf << " ";
	}
}

template <class T>
void Tree<T>::Create3(const T &rootInf, const Tree<T> &left, const Tree<T> &right)
{
	deleteTree(root);

	root = new Tree<T>;
	root->inf = rootInf;
	copyTree(root->left, left.root);
	copyTree(root->right, right.root);
}

template <class T>
void Tree<T>::Create()
{
	deleteTree(root);
	createTree(root);
}

template <class T>
void Tree<T>::createTree(Node<T> *&t)
{
	T x;
	char c;
	cout << "root: ";
	cin >> x;

	t = new Node<T>;
	t->inf = x;

	cout << "Left tree of:" << x << " (y/n)?";
	cin >> c;
	if (c == 'y' || c == 'Y') createTree(t->left);
	else t->left = NULL;

	cout << "Right tree of:" << x << " (y/n)?";
	cin >> c;
	if (c == 'y' || c == 'Y') createTree(t->right);
	else t->right = NULL;
}