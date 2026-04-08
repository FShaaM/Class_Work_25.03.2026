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
        Vector(const Vector< T >& r);
        Vector(const Vector< T >&& r) noexcept;
        Vector(size_t size, const T& val);
        explicit Vector(size_t size);

        bool is_empty() const noexcept;
        size_t getSize() const noexcept;

        void push_back(const T& x);              // H.W. и тесты
        void pop_back();                       // H.W. и тесты
        void push_front(const T& x);

        T& operator[](size_t id) noexcept;
        const T& operator[](size_t id) const noexcept;

        T& at(size_t id);
        const T& at(size_t id) const;

        Vector<T>& operator=(const Vector< T >&);
        Vector<T>& operator=(const Vector< T >&&) noexcept;

        void swap(Vector< T >& rhs) noexcept;

    private:
        T* data_;
        size_t size_;
        size_t capasity_;
    };
}

template <class T>
zinoviev::Vector<T>::Vector(const Vector< T >& r) :
    Vector(r.getSize())
{
    for (size_t i = 0; i < r.getSize(); ++i)
        data_[i] = r.data_[i];
}

template <class T>
zinoviev::Vector<T>::Vector(const Vector< T >&& rhs) noexcept :
    data_(rhs.data_),
    size_(rhs.size_),
    capasity_(rhs.capasity_)
{
    rhs.data_ = nullptr;
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

// черновая реализация
template <class T>
void zinoviev::Vector<T>::push_front(const T& x)                   //Copy-and-Swap обеспечивает строгую гарантию
{
    Vector< T > v(getSize() + 1);
    v[0] = x;

    for (size_t i = 1; i < v.getSize(); ++i)
        v[i] = (*this)[i - 1];

    swap(v);
}




// дописать тесты
template <class T>
T& zinoviev::Vector<T>::operator[](size_t id) noexcept
{
    const Vector< T >* cthis = this;
    const T& cr = (*cthis)[id];
    T& r = const_cast<T&>(cr);
    return r;

    // return const_cast<T&>((*static_cast< const Vector< T >* >(this))[id]);
}

template <class T>
const T& zinoviev::Vector<T>::operator[](size_t id) const noexcept
{
    return data_[id];
}

template <class T>
T& zinoviev::Vector<T>::at(size_t id)
{
    const Vector< T >* cthis = this;
    const T& cr = cthis->at(id);
    T& r = const_cast<T&>(cr);
    return r;
}

template <class T>
const T& zinoviev::Vector<T>::at(size_t id) const
{
    if (id < getSize())
        return (*this)[id];

    throw std::logic_error("id out of buond");
}

template <class T>
zinoviev::Vector<T>& zinoviev::Vector<T>::operator=(const Vector< T >& rhs)
{
    Vector< T > cpy(rhs);
    swap(cpy);

    return *this;
}

template <class T>
zinoviev::Vector<T>& zinoviev::Vector<T>::operator=(const Vector< T >&& rhs) noexcept
{
    Vector< T > cpy = std::move(rhs);
    swap(cpy);
    return *this;
}


template <class T>
void zinoviev::Vector<T>::swap(Vector< T >& rhs) noexcept
{
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(capasity_, rhs.capasity_);
}

#endif
