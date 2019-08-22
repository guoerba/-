#include "MSort.h"


template<class T>
MSort<T>::MSort()
	: a(0),len(0)
{
}

template<typename T>
MSort<T>::MSort(T *array, uint n, SortFunction sf, Compare func)
	: len(n),comp(std::move(func))
{
	a = new T[n];
	for (uint i = 0; i < n; i++)
		a[i] = array[i];
	switch (sf)
	{
	case choose:ChooseSort(); break;
	case bubble:BubbleSort(); break;
	case insert:InsertSort(); break;
	case shell: ShellSort(); break;
	case quick: QuickSort(); break;
	case heap: HeapSort(); break;
	case merge:
	case count:
	case radix:
	case bucket:break;
	}
}

template<class T>
MSort<T>::~MSort()
{
}

template<typename T>
void MSort<T>::free(T * array)
{
	delete[]array;
	array = 0;
}

template<typename T>
void MSort<T>::free()
{
	delete[]a;
	a = 0;
}

template<typename T>
uint MSort<T>::data(T *array)
{
	array = a;
	return len;
}

template<typename T>
T * MSort<T>::data()
{
	return a;
}

template<typename T>
void MSort<T>::ChooseSort()
{
	for (uint i = 0; i < len; i++)
	{
		T min = i;
		for (uint j = i; j < len; j++)
		{
			if (comp(a[j], a[min]))
				min = j;
		}
		swap(a[min], a[i]);
	}
}

template<typename T>
void MSort<T>::BubbleSort()
{
	for (uint i = 0; i < len - 1; i++)
	{
		for (uint j = len - 1; j > i; j--)
		{
			if (comp(a[j], a[j - 1]))
				swap(a[j], a[j - 1]);
		}
	}
}

template<typename T>
void MSort<T>::InsertSort()
{
	if (len < 2)
		return;
	for (uint i = 0; i < len - 1; i++)
	{
		for (uint j = i + 1; j > 0; j--)
		{
			if (comp(a[j], a[j - 1]))
				swap(a[j], a[j - 1]);
			else
				break;
		}
	}
}

template<typename T>
void MSort<T>::ShellSort()
{
	if (len < 2)
		return;
	for (uint step = len / 2; step > 0; step /= 2)
	{
		for (uint i = 0,stepsize = len - step; i < stepsize; i++)
		{
			for (uint j = i + step, end = (i + step) % step; j > end; j -= step)
			{
				if (comp(a[j], a[j - step]))
					swap(a[j], a[j - step]);
				else
					break;
			}
		}
	}
}

template<typename T>
void MSort<T>::QuickSort()
{
	uint l = 0, r = len - 1, mid = 0;
	std::stack<uint>p;
	p.push(r); p.push(l);
	while (!p.empty())
	{
		l = p.top(); p.pop();
		r = p.top(); p.pop();
		if (l >= r)
			continue;
		mid = partition(r, l, r);
		p.push(r); p.push(mid + 1);
		p.push(mid - 1); p.push(l);
	}
}

template<typename T>
void MSort<T>::HeapSort()
{
	Heap<T>*heap = new Heap<T>(a, len, comp);
	const T *b = heap->heap();
	for (uint i = 0; i < len; i++)
		a[i] = b[i];
	delete heap;
}

template<typename T>
void MSort<T>::swap(T & a, T & b)
{
	if (a == b)
		return;
	T temp = a;
	a = b;
	b = temp;
}

template<typename T>
uint MSort<T>::partition(uint mid, uint l, uint r)//返回mid的最后位置[l,r]
{
	uint i = l, j = l;
	while (i < r)
	{
		if (comp(a[i], a[mid]))
			swap(a[i], a[j++]);
		i++;
	}
	swap(a[mid], a[j]);
	return j;
}

template<typename T>
void MSort<T>::keepheap(T * heap, uint heaplen)
{
	for (uint j = heaplen; j > 1 ; j /= 2)
	{
		uint before = j / 2 - 1, now = j - 1;
		if (comp(heap[now], heap[before]))
			swap(heap[before], heap[now]);
		else
			break;
	}
}

template<typename T>
void MSort<T>::buildheap()
{
	T *heap = new T[len];
	uint heapsize = 0;
	for (uint i = 0; i < len; i++)
	{
		heap[heapsize++] = a[i];
		keepheap(heap, heapsize);
	}
	for (uint i = 0; i < len; i++)
		a[i] = heap[i];
	delete[]heap;
}

template class MSort<short>;
template class MSort<unsigned short>;
template class MSort<int>;
template class MSort<unsigned int>;
template class MSort<long>;
template class MSort<unsigned long>;
template class MSort<long long>;
template class MSort<unsigned long long>;

template<typename T>
Heap<T>::Heap()
{
}

template<typename T>
Heap<T>::Heap(T * array, uint len, Compare func)
{
	CreateHeap(array, len, func);
}

template<typename T>
Heap<T>::~Heap()
{
	delete[]a;
	a = 0;
}

template<typename T>
const T * Heap<T>::heap()
{
	Sort();
	return a;
}

template<typename T>
void Heap<T>::CreateHeap(T * array, uint len, Compare func)
{
	heapsize = len;
	comp = std::move(func);
	a = new T[heapsize];
	for (uint i = 0; i < len; i++)
		a[i] = array[i];

	for (uint i = heapsize / 2; i > 0; i--)
		KeepHeap(i - 1);
}

template<typename T>
void Heap<T>::KeepHeap(uint i)
{
	uint l = leftchild(i), r = rightchild(i),top = 0;
	if (l >= heapsize)
		return;
	comp(a[i], a[l]) ? top = i : top = l;
	if (r >= heapsize)
	{
		swap(a[i], a[top]);
		return;
	}
	if(!comp(a[top], a[r]))
		top = r;
	if (i != top)
	{
		swap(a[i], a[top]);
		KeepHeap(top);
	}
}

template<typename T>
void Heap<T>::Sort()
{
	uint len = heapsize;
	for (uint i = len; i > 1; i--)
	{
		swap(a[0], a[i - 1]);
		heapsize--;
		KeepHeap(0);
	}
	heapsize = len;
	for (uint i = 0, size = heapsize / 2; i < size; i++)
		swap(a[i], a[heapsize - i - 1]);
}

template<typename T>
uint Heap<T>::parent(uint i)
{
	if (!i)
		return i;
	return ((i + 1) >> 1) - 1;
}

template<typename T>
uint Heap<T>::leftchild(uint i)
{
	return ((i + 1) << 1) - 1;
}

template<typename T>
uint Heap<T>::rightchild(uint i)
{
	return (i + 1) << 1;
}

template<typename T>
void Heap<T>::swap(T & a, T & b)
{
	if (a == b)
		return;
	T temp = a;
	a = b;
	b = temp;
}
