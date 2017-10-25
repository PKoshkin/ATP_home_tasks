#ifndef DEQUE_KOSHKIN_PAVEL_493
#define DEQUE_KOSHKIN_PAVEL_493

#include <iostream>

#include <stdlib.h> // size_t, srand, rand
#include <time.h>	// time
#include <cstddef>	// ptrdiff_t

//std::conditional
#include <type_traits>
#include <typeinfo>

template <class T>
class Deque
{
private:
	T* arr;             // Массив с данными
	size_t size_;       // Кол-во элементов в массиве
	size_t capacity_;   // Текущий размер массива
	size_t left;        // Индекс первого элемента в массиве

public:
	template <bool isConst = false> // Константный и неконстантный итераторы
	// Наследуемся от std::iterator
	class DequeIterator : public std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, typename std::conditional<isConst, const T*, T*>::type, typename std::conditional<isConst, const T&, T&>::type >
	{
	private:
		typename std::conditional<isConst, const Deque*, Deque*>::type owner; //Указатель на Deque, на эл-ты которого указывает итереатор
		int index; //Индекс в структуре
		bool isReversed; // Реверсивный или нереверсивный итеретор

	public:

		//Констуктор с тремя аргументами
		DequeIterator(typename std::conditional<isConst, const Deque*, Deque*>::type inOwner, int inIndex, bool inIsReversed = false)
		{
			owner = inOwner;
			index = inIndex;
			isReversed = inIsReversed;
		}

		// Конструктор по умолчанию
		DequeIterator()
		{
			index = 0;
			owner = NULL;
			isReversed = false;
		}
		
		// Конструктор копирования
		DequeIterator(const DequeIterator& it)
		{
			index = it.index;
			owner = it.owner;
			isReversed = it.isReversed;
		}

		DequeIterator& operator++ ()
		{
			if (!isReversed)
				index++;
			else
				index--;
			return *this;
		}

		DequeIterator& operator-- ()
		{
			if (!isReversed)
				index--;
			else
				index++;
			return *this;
		}

		DequeIterator operator++ (int)
		{
			DequeIterator temp = *this;
			if (!isReversed)
				index++;
			else
				index--;
			return temp;
		}

		DequeIterator operator-- (int)
		{
			DequeIterator temp = *this;
			if (!isReversed)
				index--;
			else
				index++;
			return temp;
		}

		reference operator * ()
		{
			return (*owner)[index];
		}

		T operator * () const
		{
			return (*owner)[index];
		}

		reference operator [] (ptrdiff_t inIndex)
		{
			return *(*this + inIndex);
		}

		T operator [] (ptrdiff_t inIndex) const
		{
			return *(*this + inIndex);
		}

		T* operator -> ()
		{
			return &((*owner)[index]);
		}

		DequeIterator& operator = (const DequeIterator& it)
		{
			index = it.index;
			owner = it.owner;
			isReversed = it.isReversed;
			return *this;
		}

		bool operator == (DequeIterator it)
		{
			return index == it.index;
		}

		bool operator != (DequeIterator it)
		{
			return index != it.index;
		}

		friend ptrdiff_t operator - (DequeIterator itL, DequeIterator itR)
		{
			if (itL.isReversed && itR.isReversed)
				return itR.index - itL.index;
			else
				return itL.index - itR.index;
		}

		DequeIterator operator - (ptrdiff_t num)
		{
			if (!isReversed)
				return DequeIterator(owner, index - num, isReversed);
			else
				return DequeIterator(owner, index + num, isReversed);
		}

		DequeIterator operator + (ptrdiff_t num)
		{
			if (!isReversed)
				return DequeIterator(owner, index + num, isReversed);
			else
				return DequeIterator(owner, index - num, isReversed);
		}

		friend DequeIterator operator + (ptrdiff_t numL, DequeIterator itR)
		{
			if (!(itR.isReversed))
				return DequeIterator(itR.owner, itR.index + numL, itR.isReversed);
			else
				return DequeIterator(itR.owner, itR.index - numL, itR.isReversed);
		}

		void operator += (ptrdiff_t num)
		{
			if (!isReversed)
				index += num;
			else
				index -= num;
		}

		void operator -= (ptrdiff_t num)
		{
			if (!isReversed)
				index -= num;
			else
				index += num;
		}

		friend bool operator < (DequeIterator itL, DequeIterator itR)
		{
			if (itL.isReversed && itR.isReversed)
				return (itL.index > itR.index);
			else
				return (itL.index < itR.index);
		}

		friend bool operator <= (DequeIterator itL, DequeIterator itR)
		{
			if (itL.isReversed && itR.isReversed)
				return (itL.index >= itR.index);
			else
				return (itL.index <= itR.index);
		}

		friend bool operator > (DequeIterator itL, DequeIterator itR)
		{
			if (itL.isReversed && itR.isReversed)
				return (itL.index < itR.index);
			else
				return (itL.index > itR.index);
		}

		friend bool operator >= (DequeIterator itL, DequeIterator itR)
		{
			if (itL.isReversed && itR.isReversed)
				return (itL.index <= itR.index);
			else
				return (itL.index >= itR.index);
		}
	};

	DequeIterator<false> begin()
	{
		return DequeIterator<false>(this, 0);
	}

	DequeIterator<false> end()
	{
		return DequeIterator<false>(this, size_);
	}

	DequeIterator<true> begin() const
	{
		return DequeIterator<true>(this, 0);
	}

	DequeIterator<true> end() const
	{
		return DequeIterator<true>(this, size_);
	}

	DequeIterator<true> cbegin() const
	{
		return DequeIterator<true>(this, 0);
	}

	DequeIterator<true> cend() const
	{
		return DequeIterator<true>(this, size_);
	}

	DequeIterator<false> rbegin()
	{
		return DequeIterator<false>(this, size_ - 1, true);
	}

	DequeIterator<false> rend()
	{
		return DequeIterator<false>(this, -1, true);
	}
	
	DequeIterator<true> rbegin() const
	{
		return DequeIterator<true>(this, size_ - 1, true);
	}

	DequeIterator<true> rend() const
	{
		return DequeIterator<true>(this, -1, true);
	}

	DequeIterator<true> crbegin() const
	{
		return DequeIterator<true>(this, size_ - 1, true);
	}

	DequeIterator<true> crend() const
	{
		return DequeIterator<true>(this, -1, true);
	}

	Deque() // Конструктор без аргументов
	{
		size_ = 0;
		capacity_ = 0;
		left = 0;
		arr = new T[1];
	}

	~Deque()
	{
		if (arr != NULL)
			delete[] arr;
	}

	T& get(int index)
	{
		return arr[index];
	}

	bool needRealloc() const // Говорит, является ли очередь пустой
	{
		return (capacity_ - size_ == 0);
	}

	int frontIndex()
	{
		return left;
	}

	bool empty() const
	{
		return (size_ == 0);
	}

	size_t size() const
	{
		return size_;
	}

	int capacity() const
	{
		return capacity_;
	}

	T& back()
	{
		return arr[(left + size_ - 1) % capacity_];
	}

	T back() const
	{
		return arr[(left + size_ - 1) % capacity_];
	}

	T& front()
	{
		return arr[left];
	}

	T front() const
	{
		return arr[left];
	}

	void push_back(T in) // Добавляение сзади
	{
		if (needRealloc())
		{
			if (capacity_ != 0)
				capacity_ *= 2;
			else
				capacity_ = 1;

			T* newArr = arr;
			arr = new T[capacity_];
			for (size_t i = 0; i < size_; i++)
				arr[i] = newArr[(left + i) % size_];

			delete[] newArr;
			arr[size_] = in;
			left = 0;
			size_++;
		}
		else
		{
			arr[(left + size_) % capacity_] = in;
			size_++;
		}
	}

	void push_front(T in) // Добавление вперед
	{
		if (needRealloc())
		{
			if (capacity_ != 0)
				capacity_ *= 2;
			else
				capacity_ = 1;

			T* newArr = arr;
			arr = new T[capacity_];

			for (size_t i = 0; i < size_; i++)
				arr[i + 1] = newArr[(left + i) % size_];

			delete[] newArr;
			arr[0] = in;
			left = 0;
		}
		else
		{
			if (left == 0)
			{
				arr[capacity_ - 1] = in;
				left = capacity_ - 1;
			}
			else
			{
				arr[left - 1] = in;
				left--;
			}
		}
		size_++;
	}

	T pop_back() // Удаление последнего
	{
		T result = arr[(left + size_ - 1) % capacity_];

		size_--;
		if (4 * size_ <= capacity_)
		{
			T* newArr = arr;
			arr = new T[size_];
			for (size_t i = 0; i < size_; i++)
				arr[i] = newArr[(left + i) % capacity_];

			delete[] newArr;
			left = 0;
			capacity_ = size_;
		}

		return result;
	}

	T pop_front() // Удаление первого
	{
		T result = arr[left];

		size_--;
		left = (left + 1) % capacity_;

		if (4 * size_ <= capacity_)
		{
			T* newArr = arr;
			arr = new T[size_];
			for (size_t i = 0; i < size_; i++)
				arr[i] = newArr[(left + i) % capacity_];

			delete[] newArr;
			left = 0;
			capacity_ = size_;
		}

		return result;
	}

	T& operator [] (size_t index)
	{
		return *(arr + (left + index) % capacity_);
	}

	T operator [] (size_t index) const
	{
		return *(arr + (left + index) % capacity_);
	}

	friend std::ostream& operator << (std::ostream& out, Deque& inDeq)
	{
		for (size_t i = 0; i < inDeq.size_; i++)
		{
			out << "arr[" << (inDeq.left + i) % inDeq.capacity_ << "] = " << inDeq.arr[(inDeq.left + i) % inDeq.capacity_] << std::endl;
		}
		return out;
	}

	typedef DequeIterator<false> iterator;
};

#endif //DEQUE_KOSHKIN_PAVEL_493