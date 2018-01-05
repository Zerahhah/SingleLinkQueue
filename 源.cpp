#include<iostream>
#include<memory>
#include<string>
#include<Windows.h>

template<typename T>struct Node
{
	Node(T t) :item(t), next(nullptr) {};
	Node() :next(nullptr) {};
public:
	T item;
	std::shared_ptr<Node<T>> next;
};

template<typename T>class MyQueue {
public:
	MyQueue();
	~MyQueue() = default;
	void enqueue(T t);
	bool isEmpty();
	std::size_t size();
	T front();
	T back();
	T pop();
private:
	std::size_t count;
	std::shared_ptr<Node<T>> first;
	std::shared_ptr<Node<T>> last;
};

template<typename T>MyQueue<T>::MyQueue() :count(0){
	first = std::make_shared<Node<T>>();
	first->next = nullptr;
	last = std::make_shared<Node<T>>();
	last->next = nullptr;
};

template<typename T>void MyQueue<T>::enqueue(T t) {
	std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(t);
	if (isEmpty()) { 
		last->next = node;
		first->next = node;
		++count;
	}
	else{
		last->next->next = node;
		last->next = node;
		++count;
	}
}

template<typename T>bool MyQueue<T>::isEmpty() { return count == 0; }

template<typename T>size_t MyQueue<T>::size() { return count; }

template<typename T>T MyQueue<T>::front() {
	if (first->next != nullptr) {
		return first->next->item;
	}
	else {
		std::cerr << "ERROR：队列为空，无法获得队首元素！" << std::endl;
		throw std::runtime_error("the queue is empty!");
	}
}

template<typename T>T MyQueue<T>::back() {
	if (last->next != nullptr) {
		return last->next->item;
	}
	else {
		std::cerr << "ERROR：队列为空，无法获得队尾元素！" << std::endl;
		throw std::runtime_error("the queue is empty!");
	}
}
template<typename T>T MyQueue<T>::pop() {//返回弹出的值的版本
	if (first->next != nullptr) {
		std::shared_ptr<Node<T>> delnode = first->next;
		first->next = first->next->next;
		T item = delnode->item;
		--count;
		delnode->next = nullptr;
		return item;
	}
	else {
		std::cerr << "ERROR：队列为空，无法弹出元素！" << std::endl;
		throw std::runtime_error("the queue is empty!");
	}
}

int main() {
	MyQueue<std::string> q1;
	q1.enqueue("first");
	std::cout << q1.back() << std::endl;
	q1.enqueue("second");
	std::cout << q1.back() << std::endl;
	q1.enqueue("thrid");
	std::cout << q1.back() << std::endl;
	q1.enqueue("fourth");
	std::cout << q1.back() << std::endl;
	q1.enqueue("fifth");
	std::cout << q1.back() << std::endl;
	q1.enqueue("sixth");
	std::cout << q1.back() << std::endl;
	while (!q1.isEmpty()) {
		std::cout << q1.pop() << std::endl;
	}

	system("pause");
	return 0;
}