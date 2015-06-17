template <class T> class Stack;

template <class T>
class Item 
{
	friend class Stack <T>; // By declaring Stack<T> as friend we grant him access to the private and protected members of Item. If we use struct instead, we can skip the friend declaration!
private:
	Item(const T& x = 0)
	{
		inf = x;
		link = NULL;
	}
	T inf;
	Item *link;
};

template <class T>
class Stack {
public:
	Stack(const T&);
	Stack();
	~Stack();
	Stack(const Stack &);
	Stack& operator=(const Stack &);
	void push(const T&);
	bool pop(T&);
	bool top(T&) const;
	bool empty() const;
private:
	Item<T> *start;
	void delStack();
	void copyStack(const Stack &);
};

template <class T>
Stack<T>::Stack(const T& x)
{
	start = new Item<T>(x);
}

template <class T>
Stack<T>::Stack()
{
	start = NULL;
}

template <class T>
Stack<T>::~Stack()
{
	delStack();
}

template <class T>
Stack<T>::Stack(const Stack<T> &r)
{
	copyStack(r);
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T> &r)
{
	if (this != &r)
	{
		delStack();
		copyStack(r);
	}
	return *this;
}

template <class T>
void Stack<T>::delStack()
{
	Item<T> *p;
	while (start)
	{
		p = start;
		start = start->link;
		delete p;
	}
}

template <class T>
void Stack<T>::copyStack(const Stack<T> &r)
{
	if (!r.start) start = NULL;
	else {
		Item<T> *p = r.start, *q, *s;
		start = new Item<T>(p->inf);
		q = start;
		p = p->link;
		while (p)
		{
			s = new Item<T>(p->inf);
			q->link = s;
			q = s;
			p = p->link;
		}
	}
}

template <class T>
void Stack<T>::push(const T& x)
{
	Item<T> *p = new Item<T>(x);
	p->link = start;
	start = p;
}

template <class T>
bool Stack<T>::pop(T& x)
{
	if (!start) return false;
	Item<T> *p = start;
	x = start->inf;
	start = start->link;
	delete p;
	return true;
}

template <class T>
bool Stack<T>::top(T& x) const
{
	if (!start) return false;
	x = start->inf;
	return true;
}

template <class T>
bool Stack<T>::empty() const
{
	return start == NULL;
}