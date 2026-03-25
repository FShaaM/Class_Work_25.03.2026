#ifndef PE_VECTOR_HPP

#define PE_VECTOR_HPP
#include<cstddef>

namespace zinoviev
{
	template <class T>
	struct Vector
	{
		Vector();
		~Vector();
		Vector(size_t size, const T& val);
		explicit Vector(size_t size);

		bool is_empty() const noexcept;
		size_t getSize() const noexcept;

		//void push_back(const T&);              // H.W. и тесты
		//void pop_back();                       // H.W. и тесты

		Vector<T>& operator=(const Vector<T>&) = delete;

	private:
		T* data_;
		size_t size_;
		size_t capasity_;
	};
}

template <class T>
zinoviev::Vector<T>::~Vector()
{
	delete[] data_;
}

template <class T>
zinoviev::Vector<T>::Vector() :
	data_(nullptr),
	size_(0),
	capasity_(0)
{}

template <class T>
zinoviev::Vector<T>::Vector(size_t size) :
	data_(size ? new T[size] : nullptr),
	size_(size),
	capasity_(size)
{}

template <class T>
zinoviev::Vector<T>::Vector(size_t size, const T& val) :
	Vector(size)                                                      // для делигирования
{
	for (size_t i = 0; i < size; ++i)
	{
		data_[i] = val;                                          // теперь вызывается конструктор и деструктор (можно без try/catch)
	}
}

template <class T>
bool zinoviev::Vector<T>::is_empty() const noexcept
{
	return !size_;
}

template <class T>
size_t zinoviev::Vector<T>::getSize() const noexcept
{
	return size_;
}

#endif
