#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "Header.h"
#include <thread>
#include "heap.h"

int arr[UINT16_MAX];
std::vector<int> v;

int main()
{
	for (int i = 0; i < UINT16_MAX; i++)
	{
		v.push_back(std::rand());
	}

	arrayDesort(&arr[0], UINT16_MAX - 1);

	auto s = std::chrono::high_resolution_clock::now();

	naive_quick_sort(v.begin(), v.end());

	auto e = std::chrono::high_resolution_clock::now();
	auto tTime = e - s;

	std::cout << "Time of quick paralel sort in nanoseconds: " << tTime.count() << std::endl;


	////--------test of my qsort--------////
	arrayDesort(&arr[0], UINT16_MAX);

	auto start = std::chrono::high_resolution_clock::now();

	qsort(&arr[0], &arr[UINT16_MAX - 1]);

	auto end = std::chrono::high_resolution_clock::now();
	auto totalTime = end - start;

	std::cout << "Time of quick sort in nanoseconds: " << totalTime.count() << std::endl;
	////////////////////////////////////////


	////--------test of bublesort--------////
	arrayDesort(&arr[0], UINT16_MAX);
	start = std::chrono::high_resolution_clock::now();

	bubleSort(&arr[0], &arr[UINT16_MAX - 1]);

	end = std::chrono::high_resolution_clock::now();
	totalTime = end - start;

	std::cout << "Time of buble sort in nanoseconds: " << totalTime.count() << std::endl;
	/////////////////////////////////////////
	

	////--------test of shaker sort--------////
	arrayDesort(&arr[0], UINT16_MAX);
	start = std::chrono::high_resolution_clock::now();

	shakerSort(&arr[0], &arr[UINT16_MAX - 1]);

	end = std::chrono::high_resolution_clock::now();
	totalTime = end - start;

	std::cout << "Time of shaker sort in nanoseconds: " << totalTime.count() << std::endl;
	///////////////////////////////////////////


	////--------test of std::sort()--------////
	arrayDesort(&arr[0], UINT16_MAX);
	start = std::chrono::high_resolution_clock::now();

	std::sort(&arr[0], &arr[UINT16_MAX - 1]);

	end = std::chrono::high_resolution_clock::now();
	totalTime = end - start;

	std::cout << "Time of std::sort() in nanoseconds: " << totalTime.count() << std::endl;
	////////////////////////////////////////////
	//heap h;
	//
	//for (int i = 0; i < 10; i++)
	//{
	//	int tmp;
	//	std::cin >> tmp;
	//	h.addElem(tmp);
	//}

	//while (!h.isEmpty())
	//{
	//	int tmp = h.getMax();
	//	std::cout << tmp << std::endl;
	//}


	return 0;
}