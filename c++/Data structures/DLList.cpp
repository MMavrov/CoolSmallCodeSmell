template <class T> class DLList;

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
}

template <class T>
DLList<T>::DLList()
{
}

template <class T>
DLList<T>::~DLList()
{
}

template <class T>
DLList<T>::DLList(const DLList<T> &r)
{
}

template <class T>
DLList<T>& DLList<T>::operator=(const DLList<T> &r)
{
}

template <class T>
void DLList<T>::deleteDLList()
{
}

template <class T>
void DLList<T>::copyDLList(const DLList<T> &r)
{
}

template <class T>
void DLList<T>::IterStart(Item<T> *p)
{
}

template <class T>
void DLList<T>::IterEnd(Item<T> *p)
{
}

template <class T>
Item<T>* DLList<T>::IterNext()
{
}

template <class T>
Item<T>* DLList<T>::IterPrev()
{
}

template <class T>
bool DLList<T>::IterView(T &x) const
{
}

template <class T>
void DLList<T>::InsertToBegin(const T &x)
{
}

template <class T>
void DLList<T>::InsertToEnd(const T &x)
{
}

template <class T>
void DLList<T>::InsertAfter(Item<T> *p, const T &x)
{
}

template <class T>
void DLList<T>::InsertBefore(Item<T> *p, const T &x)
{
}

template <class T>
void DLList<T>::DeleteAfter(Item<T> *p, T &x)
{
}

template <class T>
void DLList<T>::DeleteBefore(Item<T> *p, T &x)
{
}

template <class T>
void DLList<T>::DeleteElement(Item<T> *p, T &x)
{
}

template <class T>
void DLList<T>::Print() const
{
}

template <class T>
void DLList<T>::Reverse()
{
}

template <class T>
void DLList<T>::Concat(const DLList<T> &r)
{
}

template <class T>
int DLList<T>::length() const
{
}

template <class T>
bool DLList<T>::empty() const
{
}