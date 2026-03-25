#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <stddef>

namespace zinoviev
{
	template <class T>
	struct Vector
	{
		Vector();
		~Vector();
		bool is_empty();


	private:
		T* data_;
		size_t size_, capasity_;
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


#endif
