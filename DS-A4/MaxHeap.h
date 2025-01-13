#include <vector>
#include <iostream>
#pragma once
#define MAXHEAP_H
using namespace std;


template <typename T>
class MaxHeap
{
	vector<T> heap;
	int size;

	int parent(int i) { return (i - 1) / 2; };
	int lchild(int i) { return 2 * i + 1; };
	int rchild(int i) { return 2 * i + 2; };


	void heapifyUp(int i)
	{
		if (i == 0)
		{
			return;
		}
		int p = parent(i);
		if (heap[i] > heap[p])
		{
			swap(heap[i], heap[p]);
			heapifyUp(p);
		}
	}

	void heapifyDown(int i)
	{
		int leftchild = lchild(i);
		int rightchild = rchild(i);
		int largest = i;

		if (leftchild < heap.size() && heap[leftchild] > heap[largest]) {
			largest = leftchild;
		}
		if (rightchild < heap.size() && heap[rightchild] > heap[largest]) {
			largest = rightchild;
		}
		if (largest != i) {
			swap(heap[i], heap[largest]);
			heapifyDown(largest);
		} 
	}

public:
	MaxHeap() {};
	void insert(T data)
	{
		heap.push_back(data);
		heapifyUp(heap.size() - 1);


	}

	T extractMax()
	{
		if (heap.empty())
		{
			throw runtime_error("heap is empty");

		}
		T root = heap[0];
		heap[0] = heap.back();
		heap.pop_back();

		heapifyDown(0);
		return root;
	}


	T peekMax() const {
		if (heap.empty()) {
			throw runtime_error("Heap is empty");
		}
		return heap[0];
	}

	void display()
	{
		for (const auto& ele : heap)
		{
			cout << ele << " ";
		}
	}

};
