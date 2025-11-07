#pragma once
#include <iostream>
using namespace std;

template<typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
};

template<typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		if (count == 0) {
			return;
		}

		Node<T>* curr = head;
		std::cout << curr->data;
		for (int i = 0; i < count - 1; i++) {
			curr = curr->next;
			std::cout << " " << curr->data;
		}
		std::cout << std::endl;
	}

	void printReverse() const {
		if (count == 0) {
			return;
		}

		Node<T>* curr = tail;
		std::cout << curr->data;
		for (int i = 0; i < count - 1; i++) {
			curr = curr->prev;
			std::cout << " " << curr->data;
		}
		std::cout << std::endl;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}

	Node<T>* getHead() {
		return head;
	}
	const Node<T>* getHead() const {
		return head;
	}
	Node<T>* getTail() {
		return tail;
	}
	const Node<T>* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		if (count == 0) {
			delete head;
			head = new Node<T>;
			head->data = data;
			head->prev = nullptr;
			head->next = nullptr;
		}
		else {
			auto temp = new Node<T>;
			temp->data = data;
			temp->next = head;
			temp->prev = nullptr;
			head->prev = temp;
			head = temp;
		}
		count++;
		if (count == 1) {
			tail = head;
		}

	}
	void addTail(const T& data) {
		if (count == 0) {
			delete tail;
			tail = new Node<T>;
			tail->data = data;
			tail->next = nullptr;
			tail->prev = nullptr;
		}
		else {
			auto temp = new Node<T>;
			temp->prev = tail;
			temp->data = data;
			temp->next = nullptr;
			tail->next = temp;
			tail = temp;
		}
		count++;
		if (count == 1) {
			head = tail;
		}
	}

	// Removal
	bool removeHead() {
		if (count == 0) return false;
		if (count == 1) {
			clear();
			return true;
		}
		auto temp = head;
		head = temp->next;
		head->prev = nullptr;
		delete temp;
		temp = nullptr;
		count--;
		return true;

	}
	bool removeTail() {
		if (count == 0) return false;
		if (count == 1) {
			clear();
			return true;
		}
		auto temp = tail;
		tail = temp->prev;
		tail->next = nullptr;
		delete temp;
		temp = nullptr;
		count--;
		return true;

	}
	void clear() {
		if (count == 0) {
			head = nullptr;
			tail = nullptr;
			return;
		}

		Node<T>* curr = head;
		for (int i = 0; i < count; i++) {
			Node<T>* temp = curr->next;
			delete curr;
			curr = temp;
		}

		delete curr;
		curr = nullptr;
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) return *this;
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


		clear();

		Node<T>* rhsCurr = rhs.head;
		Node<T>* prev = nullptr;

		for (int i = 0; i < rhs.count; i++) {
			auto curr = new Node<T>;
			curr->data = rhsCurr->data;
			curr->prev = prev;
			curr->next = nullptr;
			if (curr->prev) {
				curr->prev->next = curr;
			}
			rhsCurr = rhsCurr->next;
			prev = curr;

			if (i == 0) head = curr;
			if (i == rhs.count - 1) tail = curr;
		}

		count = rhs.count;
		return *this;
	}

	// Construction/Destruction
	LinkedList() {
		count = 0;
		head = nullptr;
		tail = nullptr;
	}
	LinkedList(const LinkedList<T>& list) {
		head = nullptr;
		tail = nullptr;
		count = 0;

		Node<T>* rhsCurr = list.head;
		Node<T>* prev = nullptr;

		for (int i = 0; i < list.count; i++) {
			auto curr = new Node<T>;
			curr->data = rhsCurr->data;
			curr->prev = prev;
			curr->next = nullptr;
			if (curr->prev) {
				curr->prev->next = curr;
			}
			rhsCurr = rhsCurr->next;
			prev = curr;

			if (i == 0) head = curr;
			if (i == list.count - 1) tail = curr;
		}

		count = list.count;

	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}

	~LinkedList() {
		clear();
	}

	private:
		// Stores pointers to first and last nodes and count
		Node<T>* head;
		Node<T>* tail;
		unsigned int count;
};


