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
private:
  struct QueueItem {
    T item;
    QueueItem *next;
  };

  QueueItem *headPtr;
  QueueItem *tailPtr;
  
  //Fill in the The private data members.
};



//Fill in the function definitions



template<typename T>
inline SharedQueue<T>::SharedQueue()
{
	headPtr = NULL;
	tailPtr = new QueueItem;
}

template<typename T>
inline SharedQueue<T>::~SharedQueue()
{
	delete headPtr;
}

template<typename T>
inline bool SharedQueue<T>::IsEmpty() const
{
	return (headPtr == NULL) && (tailPtr == NULL);
}

template<typename T>
inline void SharedQueue<T>::Add(T value)
{
	if (tailPtr == NULL) {
		tailPtr->item = value;
		tailPtr->next = NULL;
		headPtr = tailPtr;

	}
	else {
		QueueItem *tmp = new QueueItem;
		tailPtr->next = tmp;
		tailPtr->item = value;
		tmp->next = NULL;
		tailPtr = tmp;

		delete tmp;
	}
	
}

template<typename T>
inline bool SharedQueue<T>::Remove(T & item)
{
	QueueItem *tmp = headPtr;

	if (IsEmpty()) {
		return false;
	}

	else {
		if (tmp->next != NULL) {
			tmp = tmp->next;
			item = headPtr->item;

			headPtr = tmp;
		}
		else {
			item = headPtr->item;

		}
	}
	return false;
}

template<typename T>
inline void SharedQueue<T>::Print()
{
	QueueItem *tmp = headPtr;

	if (IsEmpty()) {
		std::cout << "List is Empty\n";

	}

	while (tmp != NULL) {
		std::cout << tmp->item << " ";
		tmp = tmp->next;
	}
}

#endif