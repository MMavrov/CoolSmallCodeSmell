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
	void DeleteAfter(Item<T>*, T&);
	void DeleteBefore(Item<T>*, T&);
	void DeleteElement(Item<T>*, T&);

	void Concat(const LList<T>&);
	void Reverse();
	void Print() const;

	int length() const;
	bool empty() const;

private:
	Item<T> *start, *end, *current;
	void deleteLList();
	void copyLList(const LList&);
};

template <class T>
LList<T>::LList(const T &x)
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
void LList<T>::deleteLList()
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
void LList<T>::IterStart(Item<T> *p)
{
	if (p) current = p;
	else current = start;
}

template <class T>
Item<T>* LList<T>::Iter()
{
	Item<T> *x = current
	if (current) current = current->link;

	return x;
}

template <class T>
bool LList<T>::IterView(T &x) const
{
	if (!current) return false;
	else x = current->inf;

	return true;
}

template <class T>
void LList<T>::InsertToBegin(const T &x)
{
	Item<T> *p = new Item<T>;
	p->inf = x;
	p->link = start;
	start = p;

	if (!end) end = p;
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

template <class T>
void LList<T>::InsertAfter(Item<T> *p, const T &x)
{
	Item<T> *q = new Item<T>;

	q->inf = x;
	q->link = p->link;

	p->link = q;
	if (p == end) end = q;
}

template <class T>
void LList<T>::InsertBefore(Item<T> *p, const T &x)
{
	Item<T> *q = new Item<T>;

	q->inf = x;
	q->link = p;

	if (p == start) start = q;
}

template <class T>
void LList<T>::DeleteAfter(Item<T> *p, T &x)
{
	Item<T> *q = p->link;

	x = q->inf;
	p->link = q->link;

	if (q == end) end = p;
	delete q;
}

template <class T>
void LList<T>::DeleteBefore(Item<T> *p, T &x)
{
	Item<T> *q = start;

	if (q->link == p)
	{
		x = q->inf;
		start = start->link;
		delete q;
	}
	else
	{
		while (q->link != p) q = q->link;
		DeleteElement(q, x);
	}
}

template <class T>
void LList<T>::DeleteElement(Item<T> *p, T &x)
{
	if (p == start)
	{
		x = p->inf;
		if (start == end) start = end = NULL;
		else start = start->link;
		delete p;
	}
	else if (p == end)
	{
		Item<T> * q = start;
		while (q->link != end) q = q->link;
		q->link = NULL;
		delete end;
		end = q;
	}
	else DeleteBefore(p->link, x);
}

template <class T>
void LList<T>::Print() const
{
	Item<T> *p = start;

	while (p)
	{
		cout << p->inf << ", ";
		p = p->link;
	}
	cout << endl;
}

template <class T>
void LList<T>::Concat(const LList<T> &r)
{
	Item<T> *p = r.start;

	while (p)
	{
		InsertToEnd(p->inf);
		p = p->link;
	}
}

template <class T>
void LList<T>::Reverse()
{
	Item<T> *currentItem, *currentItemLink, *temp;

	if (start == end) return;

	currentItem = start;
	currentItemLink = NULL;
	start = end;
	end = currentItem;

	while (p)
	{
		temp = currentItem->link;

		currentItem->link = currentItemLink;
		currentItemLink = currentItem;
		currentItem = temp;
	}
}

template <class T>
bool LList<T>::empty() const
{
	return start == NULL;
}

template <class T>
int LList<T>::length() const
{
	Item<T> *p = start;
	int n = 0;
	while (p)
	{
		n++;
		p = p->link;
	}
	return n;
}
