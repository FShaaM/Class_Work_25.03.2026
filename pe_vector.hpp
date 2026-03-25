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
		bool is_empty()const noexcept;


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

	template <class T>
	bool zinoviev::Vector<T>::is_empty() const noexcept
	{
		return size_;
	}

	template <class T>
  size_t zinoviev::Vector<T>::getSize() const noexcept
  {
	  return size_;
  }

#endif
