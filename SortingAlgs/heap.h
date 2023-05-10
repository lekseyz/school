#pragma once
#include <vector>
#include <iostream>

struct heap
{
	std::vector<int> heap;
	int size;

	void addElem(int node)
	{
		int count = size;
		int tmp;
		heap.push_back(node);
		size++;
		bool isOnPlace = false;

		while (!isOnPlace)
		{
			if (count > 0 && size % 2 == 0)
			{
				tmp = (size - 2) / 2;
				if (heap[tmp] < heap[count]) std::swap(heap[tmp], heap[count]);
				else isOnPlace = true;
				count = tmp;
			}
			else if (count > 0)
			{
				tmp = (size - 1) / 2;
				if (heap[tmp] < heap[count]) std::swap(heap[tmp], heap[count]);
				else isOnPlace = true;
				count = tmp;
			}
			else
			{
				isOnPlace = true;
			}
		}
	}

	void heapify(int n)
	{
		int child1 = n * 2 + 2;
		int child2 = n * 2 + 1;
		int largest = n;
		bool isOnPlace = false;

		while (!isOnPlace)
		{
			if (child1 < size && heap[largest] < heap[child1])
			{
				largest = child1;
			}
			else if (child2 < size && heap[largest] < heap[child1])
			{
				largest = child2;
			}
			else
			{
				isOnPlace = true;
			}

			std::swap(heap[largest], heap[n]);
			child1 = largest * 2 + 2;
			child2 = largest * 2 + 1;
		}

	}

	void buildHeap(int* left, int* right)
	{
		while (left <= right)
		{
			addElem(*left);
			left++;
		}
	}

	int getMax()
	{
		int max = heap[0];
		heap[0] = heap[size - 1];
		this->heapify(0);
		return max;
	}

	bool isEmpty()
	{
		return size == 0;
	}
};