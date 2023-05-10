#include <vector>                      
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <future>
#include <random>
#include <chrono>
#include <cstdlib>
typedef int Type;

template<typename T>
void arrayDesort(T* first, int size)
{
	#include <random>
	using namespace std;

	for (int i = 0; i < size; i++, first++)
	{
		*first = std::rand();
	}
}

template<typename T>
bool checkSorting(T* left, T* right)
{
	size_t size = right - left;
	bool isSorted = true;

	for (int i = 0; i < size; i++)
	{
		if (*(left + i) > *(left + i + 1)) isSorted = false;
	}

	if (isSorted) return true;
	else return false;
}

template<typename T>
void swap(T& first, T& second)
{
	T c = first;
	first = second;
	second = c;
	return;
}

template<typename T>
bool defaultCmp(const T& first, const T& second)
{
	return first < second;
}


template<typename T>
void qsort(T* left, T* right, bool(*cmp)(const T&, const T&) = nullptr)
{
	T* ll = left;
	T* rr = right;
	T piv = *(left + (right - left) / 2);
	if (cmp == nullptr) cmp = defaultCmp;

	while (ll < rr)
	{
		while (cmp(*ll, piv)) ll++;
		while (cmp(piv, *rr)) rr--;
		if (ll <= rr)
		{
			swap(*ll, *rr);
			ll++;
			rr--;
		}
	}
	if (left < rr) qsort(left, rr);
	if (right > ll) qsort(ll, right);
}


int naive_quick_sort(std::vector<Type>::iterator begin, std::vector<Type>::iterator end) {
	auto const sz = end - begin;
	if (sz <= 1) return 0;

	auto pivot = begin + sz / 2;
	auto const pivot_v = *pivot;

	std::swap(*pivot, *(end - 1));
	auto p = std::partition(begin, end, [&](const Type& a) { return a < pivot_v; });
	std::swap(*p, *(end - 1));

	if (sz > 4096) {
		auto left = std::async(std::launch::async, [&]() {
			return naive_quick_sort(begin, p);
		});
		naive_quick_sort(p + 1, end);
	}
	else {
		naive_quick_sort(begin, p);
		naive_quick_sort(p + 1, end);
	}
	return 0;
}

/*

template<typename T>
void qsortMultiThread(T* left, T* right, bool(*cmp)(const T&, const T&) = nullptr)
{
	T* ll = left;
	T* rr = right;
	T piv = *(left + (right - left) / 2);
	if (cmp == nullptr) cmp = defaultCmp;

	while (ll < rr)
	{
		while (cmp(*ll, piv)) ll++;
		while (cmp(piv, *rr)) rr--;
		if (ll <= rr)
		{
			swap(*ll, *rr);
			ll++;
			rr--;
		}
	}
	if (left < rr) {
		mu1.lock();
		std::thread t1(qsort<T>, std::ref(left), std::ref(rr),mu1 ,cmp); t1.detach();
	}
	if (right > ll) {
		mu2.lock();
		std::thread t2(qsort<T>, std::ref(ll), std::ref(right),mu2 ,cmp); t2.detach();
	}
	while(!mu1.try_lock() && !mu2.try_lock()){}
}*/

template<typename T>
void evenOddSort(T* left, T* right, bool(*cmp)(const T&, const T&) = nullptr)
{
	size_t size = right - left;
	T* p = left;
	T* np;
	if (cmp == nullptr) cmp = defaultCmp;
	bool isUnsorted = true;

	while (isUnsorted)
	{
		isUnsorted = false;

		for (int i = 0; i <= size - 1; i += 2)
		{
			p += 2;
			np = p + 1;
			if (!cmp(*(p), *(np)))
			{
				swap(*(p), *(np));
				isUnsorted = true;
			}
		}

		p = left + 1;
		for (int i = 1; i <= size - 1; i += 2)
		{
			p += 2;
			np = p + 1;
			if (!cmp(*(p), *(np)))
			{
				swap(*(p), *(np));
				isUnsorted = true;
			}
		}
		p = left;
	}
}

template<typename T>
void bubleSort(T* left, T* right, bool(*cmp)(const T&, const T&) = nullptr)
{
	size_t size = right - left;
	T* p = left;
	if (cmp == nullptr) cmp = defaultCmp;
	bool isUnsorted = true;

	while (isUnsorted)
	{
		isUnsorted = false;
		for (int i = 0; i < size; i++, p++)
		{
			if (!cmp(*p, *(p + 1)))
			{
				swap(*p, *(p + 1));
				isUnsorted = true;
			}
		}
		p = left;
		--size;
	}
}

template<typename T>
void shakerSort(T* left, T* right, bool(*cmp)(const T&, const T&) = nullptr)
{
	size_t size = right - left;
	size_t start = 0;
	T* p = left;
	if (cmp == nullptr) cmp = defaultCmp;
	bool isUnsorted = true;

	while (isUnsorted)
	{
		isUnsorted = false;
		for (int i = start; i < size; i++, p++)
		{
			if (cmp(*p, *(p + 1)))
			{
				swap(*p, *(p + 1));
			}
		}

		for (int i = size; i > start; i--, p--)
		{
			if (!cmp(*p, *(p - 1)))
			{
				swap(*p, *(p - 1));
				isUnsorted = true;
			}
		}
		++start;
		--size;
	}
}