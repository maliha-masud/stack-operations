#include <iostream>
using namespace std;

template <class T>
class Node {
public:
	T data; //store any data of type T
	Node<T>* next; //pointer to next element

	Node<T>() {}
};

template <class T>
class Stack {
	Node<T>* top; //points to last added element ("top" of stack)
	//int size;

public:
	//default constructor
	Stack() {
		top = NULL;
	}

	void Push(T c) //add to start
	{
		if (top == NULL) //first element being pushed
		{
			Node<T>* temp = new Node<T>;
			temp->data = c;
			temp->next = NULL;
			top = temp;
		}
		else //elements already exist in stack
		{
			Node<T>* temp = new Node<T>;
			temp->data = c;
			temp->next = top;
			top = temp;
		}
	}

	T Pop() //delete at start
	{
		if (top != NULL) //elements exist in stack
		{
			T c = top->data;
			Node<T>* temp = top;
			top = top->next;
			delete temp;
			return c; //return data of top element
		}

		//if stack is empty
		return -1;
	}

	//helper functions
	T peek() {
		if (top != NULL)
			return top->data;

		return -1; //if stack is empty
	}

	bool isEmpty() {
		if (top == NULL)
			return 1;

		return 0;
	}
};
