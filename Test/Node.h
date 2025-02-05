#pragma once
template <typename T>
ref class Node
{
public:
	T^ data;
	Node^ nextElement;
	Node() {
		this->data = gcnew T();
		this->nextElement = nullptr;
	}
};

