template <class T> class Queue;

template <class T>
class Item 
{
	friend class Queue<T>; 
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
class Queue {
public:
	Queue(const T&);
	Queue();
	~Queue();
	Queue(const Queue &);
	Queue& operator=(const Queue &);

	void Push(const T&);
	bool Pop(T&);
	bool Peek(T&) const;
	bool Empty() const;
private:
	Item<T> *front, *rear;
	void deleteQueue();
	void copyQueue(const Queue &);
};

template <class T>
Queue<T>::Queue(const T& x)
{
	front = new Item<T>(x);
	rear = front;
}

template <class T>
Queue<T>::Queue()
{
	front = rear = NULL;
}

template <class T>
Queue<T>::~Queue()
{
	delQueue();
}

template <class T>
Queue<T>::Queue(const Queue<T> &r)
{
	copyQueue(r);
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T> &r)
{
	if (this != &r)
	{
		delQueue();
		copyQueue(r);
	}
	return *this;
}

template <class T>
void Queue<T>::deleteQueue()
{
	T x;
	while (Pop(x));
}

template <class T>
void Queue<T>::copyQueue(const Queue<T> &r)
{
	front = rear = NULL;

	if (r.front) 
	{
		Item<T> *p = r.front;
		while (p)
		{
			Push(p->inf);
			p = p->link;
		}
	}
}

template <class T>
void Queue<T>::Push(const T& x)
{
	Item<T> *p = new Item<T>(x);
	if (front)
	{
		rear->link = p;
		rear = p;
	}
	else
		front = rear = p;
}

template <class T>
bool Queue<T>::Pop(T& x)
{
	if (!front) return false;

	Item<T> *p = front;
	x = p->inf;

	if (front == rear) front = rear = NULL;
	else front = front->link;

	delete p;
	return true;
}

template <class T>
bool Queue<T>::Peek(T& x) const
{
	if (!front) return false;
	
	x = front->inf;
	return true;
}

template <class T>
bool Queue<T>::Empty() const
{
	return front == NULL;
}