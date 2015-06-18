template <class T> class LList;

template <class T>
struct Item 
{
	T inf;
	Item *link;
};

template <class T>
class LList {
public:
	LList(const T&);
	LList();
	~LList();
	LList(const LList &);
	LList& operator=(const LList &);

	void IterStart(Item<T>* = NULL);
	Item<T>* Iter();
	bool IterView(T&) const;
	void InsertToEnd(const T&);
	void InsertToBegin(const T&);
	void InsertAfter(Item<T>*, const T&);
	void InsertBefore(Item<T>*, const T&);
	void DeleteAfter(Item<T>*, const T&);
	void DeleteBefore(Item<T>*, const T&);
	void DeleteElement(Item<T>*, const T&);

	int length() const;
	void print() const;
	void concat(const LList<T>&);
	void reverse();
	bool empty() const;

private:
	Item<T> *start, *end, *current;
	void deleteLList();
	void copyLList(const LList&);
};

template <class T>
LList<T>::LList(const T& x)
{
	start = new Item<T>;
	start->inf = x;
	start->link = NULL;
	end = start;
}

template <class T>
LList<T>::LList()
{
	start = end = NULL;
}

template <class T>
LList<T>::~LList()
{
	deleteList();
}

template <class T>
LList<T>::LList(const LList<T> &r)
{
	copyLList(r);
}

template <class T>
LList<T>& LList<T>::operator=(const LList<T> &r)
{
	if (this != &r)
	{
		deleteLList();
		copyList();
	}
	return *this;
}

template <class T>
void LList<T>::delLList()
{
	Item<T> *p;
	while (start)
	{
		p = start;
		start = start->link;
		delete p;
	}
	end = NULL;
}

template <class T>
void LList<T>::copyLList(const LList<T> &r)
{
	start = end = NULL;

	Item<T> *p = r.start;
	while (p)
	{
		InsertToEnd(p->inf);
		p = p->link;
	}
}

template <class T>
void LList<T>::InsertToEnd(const T &x)
{
	Item<T> *p = new Item<T>;

	p->inf = x;
	p->link = NULL;

	if (!start) start = end = p;
	else 
	{
		end->link = p;
		end = p;
	}
}