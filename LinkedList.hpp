#pragma once
#include <iostream>
using namespace std;


template <typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
	// Behaviors
	void printForward() const {
		Node* current = head;
		for (int i = 0; i < count; i++) {
			std::cout << current->data << std::endl;
			current = current->next;
		}
	}
	void printReverse() const {
		Node* current = tail;
		for (int i = 0; i < count; i++) {
			std::cout << current->data << std::endl;
			current = current->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		if (count == 0){
			head = new Node(data, nullptr, nullptr);
			tail = head;
		}
		else {
			Node* newHead = new Node(data, nullptr, head);
			head->prev = newHead;
			head = newHead;
		}
		count++;
	}
	void addTail(const T& data) {
		if (count == 0){
			tail = new Node(data, nullptr, nullptr);
			head = tail;
		}
		else {
			Node* newTail = new Node(data, tail, nullptr);
			tail->next = newTail;
			tail = newTail;
		}
		count++;
	}

	// Removal
	bool removeHead() {
		if (count == 0) {
			return false;
		}
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			Node* temp = head->next;
			delete head;
			head = temp;
			head->prev = nullptr;
		}
		count--;
		return true;
	}
	bool removeTail() {
		if (count == 0) {
			return false;
		}
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			Node* temp = tail->prev;
			delete tail;
			tail = temp;
			tail->next = nullptr;
		}
		count--;
		return true;
	}

	void Clear() {
		while (removeHead()) {}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) {
			return *this;
		}
		this->Clear();
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return *this;
	}

	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) return *this;
		Node* temp = rhs.head;
		this->Clear();
		this->head = temp;
		while (temp != nullptr) {
			addTail(temp->data);
			temp = temp->next;
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list) : head(list.head), tail(list.tail), count(list.count) {}

	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	int getCount() {
		return count;
	}

	~LinkedList() {
		this->Clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


