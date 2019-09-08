#ifndef __Lab14__SharedQueue__
#define __Lab14__SharedQueue__

#include <mutex>

template <typename T>
class SharedQueue {
public:
  SharedQueue();
  ~SharedQueue();
  
    /*
     These declarations mean that we do NOT get the automatically
     defined copy/copy-assign functions.  If you try to call one
     by copying the queue, you'll get a compiler error.
     
     This is a common technique for things that are uncopyable (like std::thread and std::mutex, for example).
     
     We really DO want a destructor, so cheating at the
     rule of 3 here makes sense here.
     */
    SharedQueue(const SharedQueue<T>&) = delete;
    SharedQueue<T>& operator=(const SharedQueue<T>&) = delete;

    
  //Return true if the queue is empty
  bool IsEmpty() const;
  
  //Enqueue the next item at the tail of the queue.
  void Add(T value);
  
  //Dequeue the next queue element and store it in "item" variable.  The function returns false if the queue is empty and no item can be retrieved.
  bool Remove(T &item);
  void Print();
  int Size();
private:
	//Fill in the The private data members.
  struct QueueItem {
    T item;
    QueueItem *next;
  }*headPtr, *tailPtr;
 
  std::mutex lock;
  int size;
};


//Fill in the function definitions

template<typename T>
inline SharedQueue<T>::SharedQueue()
{
	headPtr = NULL;
	tailPtr = NULL;
}

template<typename T>
inline SharedQueue<T>::~SharedQueue()
{
	while (!IsEmpty()) {
		QueueItem *tmp = headPtr;
		headPtr = headPtr->next;
		tmp->next = NULL;
		delete tmp;
	}

}

template<typename T>
inline bool SharedQueue<T>::IsEmpty() const
{
	return (headPtr == NULL);
}

template<typename T>
inline void SharedQueue<T>::Add(T value)
{
	QueueItem *newNode = new QueueItem;
	newNode->item = value;
	newNode->next = NULL;

	//Make sure process completes
	lock.lock();
	if (IsEmpty()) {
		headPtr = newNode;
		tailPtr = newNode;

		lock.unlock();
		return;
	
	}
	
	tailPtr->next = newNode;
	tailPtr = newNode;

	size++;
	
	lock.unlock();
	
}

template<typename T>
inline bool SharedQueue<T>::Remove(T & item)
{
	
	//Make sure process completes
	lock.lock();

	if (IsEmpty()) {
		lock.unlock();
		std::cout << "Queue is Empty \n";
		return false;
	}

	QueueItem *tmp = headPtr;

	item = tmp->item;

	headPtr = headPtr->next;

	delete tmp; //Delete previous head

	if (IsEmpty()) {
		tailPtr = NULL;
	}
	size--;
	lock.unlock();
	return true;
}

template<typename T>
inline void SharedQueue<T>::Print()
{
	lock.lock();
	
	if (IsEmpty()) {
		std::cout << "List is Empty\n";
		lock.unlock();
		return;
	}

	QueueItem *tmp = headPtr;

	while (tmp != NULL) {
		std::cout << tmp->item << " ";
		tmp = tmp->next;
	}
	std::cout << "\n";

	lock.unlock();
}

template<typename T>
inline int SharedQueue<T>::Size()
{
	return size;
}

#endif