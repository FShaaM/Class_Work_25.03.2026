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

        void push_back(const T& x);              // H.W. и тесты
        void pop_back();                       // H.W. и тесты

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
{
}

template <class T>
zinoviev::Vector<T>::Vector(size_t size) :
    data_(size ? new T[size] : nullptr),
    size_(size),
    capasity_(size)
{
}

template <class T>
zinoviev::Vector<T>::Vector(size_t size, const T& val) :
    Vector(size)                                                      // для делигирования
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = val;                                          // теперь вызывается конструктор и деструктор(можно без try / catch)
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

template <class T>
void zinoviev::Vector<T>::push_back(const T& x)
{
    if (size_ == capasity_)
    {
        size_t new_cap = (capasity_ == 0 ? 2 : capasity_ * 2);
        T* new_data = nullptr;
        try
        {
            new_data = new T[new_cap];

            for (size_t i = 0; i < size_; ++i)
            {
                new_data[i] = data_[i];
            }
            new_data[size_] = x;
            ++size_;

            delete[] data_;
            data_ = new_data;
            capasity_ = new_cap;
        }
        catch (...)
        {
            delete[] new_data;
            throw;
        }
    }
    else
    {
        data_[size_] = x;
        ++size_;
    }
}

template <class T>
void zinoviev::Vector<T>::pop_back()
{
    if (!data_ || !size_)
        return;

    --size_;
    data_[size_].~T();
}

#endif
