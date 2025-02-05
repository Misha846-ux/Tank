#pragma once
#include "Node.h"
template <typename T>
ref class MyList
{
private:
	Node<T>^ nextElement;
public:
	MyList() {
		this->nextElement = nullptr;
	}
	void addToHead() {
		Node<T>^ newElement = gcnew Node<T>();
		newElement->nextElement = this->nextElement;
		this->nextElement = newElement;
	}
	void addToTail() {
		Node<T>^ newElement = gcnew Node<T>();
		if (this->nextElement != nullptr) {
			EnemyNode^ cell = this->nextElement;
			while (cell->nextElement != nullptr) {
				cell = cell->nextElement;
			}
			cell->nextElement = newElement;
		}
		else {
			this->nextElement = newElement;
		}
	}
	T^ getEnemyFromPosition(int position) {
		if (position <= 1) {
			return this->nextElement->data;
		}
		else {
			int score = 1;
			Node<T>^ cell1 = this->nextElement;
			while (score < position && cell1->nextElement != nullptr) {
				score++;
				cell1 = cell1->nextElement;
			}
			return cell1->data;
		}
	}
	void setFirstLink(Node<T>^ nextElement) {
		this->nextElement = nextElement;
	}
	void deleteFromHead() {
		if (this->nextElement != nullptr) {
			Node<T>^ cell = this->nextElement->nextElement;
			delete this->nextElement;
			this->nextElement = cell;
		}
	}
	void deleteFromPosition(int position) {
		if (position <= 1) {
			this->deleteFromHead();
		}
		else {
			int score = 1;
			Node<T>^ cell1 = this->nextElement;
			Node<T>^ cell2 = cell1;
			while (score < position && cell1->nextElement != nullptr) {
				score++;
				cell2 = cell1;
				cell1 = cell1->nextElement;
			}
			cell2->nextElement = cell1->nextElement;
			delete cell1;
		}
	}
	Node<T>^ getFirstLink() {
		return this->nextElement;
	}
};

