
template <class T>
struct Item
{
	T inf;
	Item *previous;
	Item *next;
};

template <class T>
class DLList {
public:
	DLList(const T&);
	DLList();
	~DLList();
	DLList(const DLList &);
	DLList& operator=(const DLList &);

	void IterStart(Item<T>* = NULL);
	void IterEnd(Item<T>* = NULL);
	Item<T>* IterNext();
	Item<T>* IterPrev();
	bool IterView(T&) const;

	void InsertToBegin(const T&);
	void InsertToEnd(const T&);
	void InsertAfter(Item<T>*, const T&);
	void InsertBefore(Item<T>*, const T&);
	void DeleteAfter(Item<T>*, T&);
	void DeleteBefore(Item<T>*, T&);
	void DeleteElement(Item<T>*, T&);

	void Print() const;
	void Reverse();
	void Concat(const DLList<T>&);

	int length() const;
	bool empty() const;

private:
	Item<T> *start, *end, *current;
	void deleteDLList();
	void copyDLList(const DLList&);
};

template <class T>
DLList<T>::DLList(const T &x)
{
	start = new Item<T>;
	start->inf = x;
	start->next = start->previous = NULL;
	end = start;
}

template <class T>
DLList<T>::DLList()
{
	start = end = NULL;
}

template <class T>
DLList<T>::~DLList()
{
	deleteDLList();
}

template <class T>
DLList<T>::DLList(const DLList<T> &r)
{
	copyDLList();
}

template <class T>
DLList<T>& DLList<T>::operator=(const DLList<T> &r)
{
	if (this != &r)
	{
		deleteDLList();
		copyDLList(r);
	}
	return this;
}

template <class T>
void DLList<T>::deleteDLList()
{
	Item<T> *p;

	while (start)
	{
		p = start;
		start = start->next;
		delete p;
	}
	end = NULL;
}

template <class T>
void DLList<T>::copyDLList(const DLList<T> &r)
{
	start = end = NULL;
	Item<T> *p = r.start;

	while (p)
	{
		InsertToEnd(p->inf);
		p = p->next;
	}
}

template <class T>
void DLList<T>::IterStart(Item<T> *p)
{
	if (p) current = p;
	else current = start;
}

template <class T>
void DLList<T>::IterEnd(Item<T> *p)
{
	if (p) current = p;
	else current = end;
}

template <class T>
Item<T>* DLList<T>::IterNext()
{
	Item<T> *p = current;

	if (current) current = current->next;

	return p;
}

template <class T>
Item<T>* DLList<T>::IterPrev()
{
	Item<T> *p = current;

	if (current) current = current->previous;

	return p;
}

template <class T>
bool DLList<T>::IterView(T &x) const
{
	if (!current) return false;
	x = current->inf;
	return true;
}

template <class T>
void DLList<T>::InsertToBegin(const T &x)
{
	Item<T> *p = new Item<T>;

	p->inf = x;
	p->next = start;
	p->previous = NULL;

	if (!end)
	{
		start = end = p;
	}
	else
	{
		start->previous = p;
		start = p;
	}
}

template <class T>
void DLList<T>::InsertToEnd(const T &x)
{
	Item<T> *p = new Item<T>;

	p->inf = x;
	p->next = NULL;
	p->previous = end;

	if (!start)
	{
		start = end = p;
	}
	else
	{
		end->next = p;
		end = p;
	}
}

template <class T>
void DLList<T>::InsertAfter(Item<T> *p, const T &x)
{
	Item<T> *q = new Item<T>;

	q->inf = x;
	q->next = p->next;
	q->previous = p;
	p->next = q;

	if (q->next) p->next->previous = q;
	else end = q;
}

template <class T>
void DLList<T>::InsertBefore(Item<T> *p, const T &x)
{
	Item<T> *q = new Item<T>;

	q->inf = x;
	q->next = p;
	q->previous = p->previous;
	p->previous = q;

	if (q->previous) p->previous->next = q;
	else start = q;
}

template <class T>
void DLList<T>::DeleteAfter(Item<T> *p, T &x)
{
	if (p == end) return;
	Item<T> *q = p->next;
	x = q->inf;
	p->next = q->next;

	if (q->next) q->next->previous = p;
	else end = p;

	delete q;
}

template <class T>
void DLList<T>::DeleteBefore(Item<T> *p, T &x)
{
	if (p == start) return;
	Item<T> *q = p->previous;
	x = q->inf;
	p->previous = q->previous;

	if (q->previous) q->previous->next = p;
	else start = p;
	delete q;
}

template <class T>
void DLList<T>::DeleteElement(Item<T> *p, T &x)
{
	x = p->inf;
	if (start == end) start = end = NULL;
	else if (p == start)
	{
		start = start->next;
		start->previous = NULL;
	}
	else if (p == end)
	{
		end = end->previous;
		end->next = NULL;
	}
	else
	{
		p->previous->next = p->next;
		p->next->previous = p->previous;
	}

	delete p;
}

template <class T>
void DLList<T>::Print() const
{
	Item<T> *p = start;

	while (p)
	{
		if (p->next) cout << p->inf << ", ";
		else cout << p->inf;

		p = p->next;
	}
	cout << endl;
}

template <class T>
void DLList<T>::Reverse()
{
	Item <T> *currentItem, *temp;

	if (start == end) return;
	currentItem = start;
	start = end;
	end = currentItem;

	while (currentItem)
	{
		temp = currentItem->next;
		currentItem->next = currentItem->previous;
		currentItem->previous = temp;
		currentItem = temp;
	}
}

template <class T>
void DLList<T>::Concat(const DLList<T> &r)
{
	Item<T> *p = r.start;

	while (p)
	{
		InsertToEnd(p->inf);
		p = p->next;
	}
}

template <class T>
int DLList<T>::length() const
{
	Item <T> *p = start;
	int n = 0;
	while (p)
	{
		n++;
		p = p->succ;
	}
	return n;
}

template <class T>
bool DLList<T>::empty() const
{
	return start == NULL;
}