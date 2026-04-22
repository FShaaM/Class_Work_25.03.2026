#ifndef VECTOR_HPP

#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <new>

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
        size_t getCapucity() const noexcept;
        void reserve(size_t cap);


        void push_back(const T& x);              // H.W. и тесты
        void pop_back();                       // H.W. и тесты
        void push_front(const T& x);

        void insert(size_t id, const T& t);
        void insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end);
        void erase(size_t id);
        void erase(size_t beg, size_t end);


        void swap(Vector< T >& rhs) noexcept;

        T& at(size_t id);
        const T& at(size_t id) const;

        T& operator[](size_t id) noexcept;
        const T& operator[](size_t id) const noexcept;

        Vector<T>& operator=(const Vector< T >&);
        Vector<T>& operator=(const Vector< T >&&) noexcept;


        class Iterator {
        private:
            T* ptr_;

        public:
            Iterator(T* ptr) noexcept;

            T& operator*() const noexcept;
            T* operator->() const noexcept;
            Iterator& operator++() noexcept;
            Iterator operator++(int) noexcept;
            Iterator& operator--() noexcept;
            Iterator operator--(int) noexcept;

            Iterator& operator+=(int n) noexcept;
            Iterator& operator-=(int n) noexcept;
            Iterator operator+(int n) const noexcept;
            Iterator operator-(int n) const noexcept;
            T& operator[](size_t n) const noexcept;

            bool operator==(const Iterator& other) const noexcept;
            bool operator!=(const Iterator& other) const noexcept;
            bool operator<(const Iterator& other) const noexcept;
            bool operator>(const Iterator& other) const noexcept;
            bool operator<=(const Iterator& other) const noexcept;
            bool operator>=(const Iterator& other) const noexcept;
        };

        class CIterator {
        private:
            const T* cptr_;

        public:
            CIterator(T* ptr) noexcept;
            CIterator(const T* ptr) noexcept;

            const T& operator*() const noexcept;
            const T* operator->() const noexcept;
            CIterator& operator++() noexcept;
            CIterator operator++(int) noexcept;
            CIterator& operator--() noexcept;
            CIterator operator--(int) noexcept;

            CIterator& operator+=(int n) noexcept;
            CIterator& operator-=(int n) noexcept;
            CIterator operator+(int n) const noexcept;
            CIterator operator-(int n) const noexcept;
            const T& operator[](size_t n) const noexcept;

            bool operator==(const CIterator& other) const noexcept;
            bool operator!=(const CIterator& other) const noexcept;
            bool operator<(const CIterator& other) const noexcept;
            bool operator>(const CIterator& other) const noexcept;
            bool operator<=(const CIterator& other) const noexcept;
            bool operator>=(const CIterator& other) const noexcept;
        };

        Iterator begin() noexcept;
        Iterator end() noexcept;
        CIterator begin() const noexcept;
        CIterator end() const noexcept;
        CIterator cbegin() const noexcept;
        CIterator cend() const noexcept;

        void insert(Iterator pos, const T& value);
        void insert(Iterator pos, size_t count, const T& value);
        void insert(Iterator pos, const Vector< T >& other);
        void erase(Iterator pos);
        void erase(Iterator first, Iterator last);
        void erase(Iterator pos, size_t n);


    private:
        T* data_;
        size_t size_;
        size_t capacity_;
    };
}

template <class T>
zinoviev::Vector<T>::Vector() :
    data_(nullptr),
    size_(0),
    capacity_(0)
{
}

template <class T>
zinoviev::Vector<T>::Vector(size_t size) :
    data_(size ? static_cast<T*>(operator new[](sizeof(T)* size)) : nullptr),
    size_(size),
    capacity_(size)
{
    size_t i = 0;

    try
    {
        for (; i < size_; ++i)
            new (data_ + i) T();
    }
    catch (...)
    {
        for (; i < size_; ++i)
            (data_ + i)->~T();

        ::operator delete[](data_);
        throw;
    }
}

template <class T>
zinoviev::Vector<T>::Vector(size_t size, const T& val) :
    data_(size ? static_cast<T*>(operator new[](sizeof(T)* size)) : nullptr),        // Для делигирования раньше был вызов Vector(size_t size)
    size_(size),                                                                     //и вызывались конструктор и деструктор (можно было без try / catch),
    capacity_(size)                                                                  //но сейчас мы руками выделяем память и получался бы двойной вызов конструкторов (Убрали делегирование)

{
    size_t i = 0;
    try
    {
        for (; i < size_; ++i)
            new (data_ + i) T(val);
    }
    catch (...)
    {
        for (size_t j = 0; j < i; ++j)
            (data_ + j)->~T();

        ::operator delete[](data_);
        throw;
    }
}

template <class T>
zinoviev::Vector<T>::Vector(const Vector< T >& r) :
    data_(r.size_ ? static_cast<T*>(operator new[](sizeof(T)* r.size_)) : nullptr),
    size_(r.size_),
    capacity_(r.size_)
{
    size_t i = 0;

    try
    {
        for (; i < size_; ++i)
            new (data_ + i) T(r.data_[i]);
    }
    catch (...)
    {
        for (size_t j = 0; j < i; ++j)
            (data_ + j)->~T();

        ::operator delete[](data_);
        throw;
    }
}

template <class T>
zinoviev::Vector<T>::Vector(const Vector< T >&& rhs) noexcept :
    data_(rhs.data_),
    size_(rhs.size_),
    capacity_(rhs.capacity_)
{
    rhs.data_ = nullptr; // остальные зануления делать ОШИБОЧНО, лучше сделать пустой вектор и обменять
}

template <class T>
zinoviev::Vector<T>::~Vector()
{
    for (size_t i = 0; i < size_; ++i)
        (data_ + i)->~T();

    ::operator delete[](data_);
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
size_t zinoviev::Vector<T>::getCapucity() const noexcept
{
    return capacity_;
}

template <class T>
void zinoviev::Vector<T>::reserve(size_t cap)
{
    if (cap <= capacity_)
        return;

    T* new_data = nullptr;

    size_t i = 0;
    try
    {
        new_data = static_cast<T*>(operator new[](sizeof(T)* cap));

        for (; i < size_; ++i)
        {
            new (new_data + i) T(data_[i]);
        }

        for (size_t j = 0; j < size_; ++j)
        {
            (data_ + j)->~T();
        }
        ::operator delete[](data_);

        data_ = new_data;
        capacity_ = cap;
    }
    catch (...)
    {
        for (size_t j = 0; j < i; ++j)
        {
            (new_data + j)->~T();
        }
        ::operator delete[](new_data);
        throw;
    }
}


template <class T>
void zinoviev::Vector<T>::push_back(const T& x)
{
    if (size_ == capacity_)
    {
        size_t new_cap = (capacity_ == 0 ? 2 : capacity_ * 2);
        T* new_data = nullptr;
        size_t old_size = size_;

        size_t i = 0;
        try
        {
            new_data = static_cast<T*>(operator new[](sizeof(T)* new_cap));

            for (; i < old_size; ++i)
            {
                new (new_data + i) T(data_[i]);
            }
            new (new_data + old_size) T(x);
            i = old_size + 1;

            for (size_t j = 0; j < old_size; ++j)
            {
                (data_ + j)->~T();
            }
            ::operator delete[](data_);

            data_ = new_data;
            ++size_;
            capacity_ = new_cap;
        }
        catch (...)
        {
            for (size_t j = 0; j < i; ++j)
            {
                (new_data + j)->~T();
            }
            ::operator delete[](new_data);
            throw;
        }
    }
    else
    {
        new (data_ + size_) T(x);
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

template <class T>
void zinoviev::Vector<T>::push_front(const T& x)                   //Copy-and-Swap обеспечивает строгую гарантию
{
    size_t new_cap = (capacity_ == 0 ? 2 : capacity_ + 20);
    T* new_data = nullptr;
    size_t old_size = size_;

    size_t i = 0;
    try
    {
        new_data = static_cast<T*>(operator new[](sizeof(T)* new_cap));

        new (new_data + i) T(x);
        ++i;
        for (size_t j = 0; j < old_size; ++j)
        {
            new (new_data + j + 1) T(data_[j]);
            ++i;
        }

        for (size_t j = 0; j < old_size; ++j)
        {
            (data_ + j)->~T();
        }
        ::operator delete[](data_);

        data_ = new_data;
        ++size_;
        capacity_ = new_cap;
    }
    catch (...)
    {
        for (size_t j = 0; j < i; ++j)
        {
            (new_data + j)->~T();
        }
        ::operator delete[](new_data);
        throw;
    }
}

template <class T>
void zinoviev::Vector<T>::insert(size_t id, const T& t)
{
    if (id >= size_)
    {
        push_back(t);
        return;
    }
    Vector< T > v;
    v.reserve(size_ + 1);

    for (size_t i = 0; i < id; ++i)
        v.push_back(data_[i]);

    v.push_back(t);

    for (size_t i = id; i < size_; ++i)
        v.push_back(data_[i]);

    swap(v);
}

template <class T>
void zinoviev::Vector<T>::insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end)
{
    if (beg > end)
        std::swap(beg, end);
    if (end >= rhs.size_)
        end = rhs.size_;
    if (beg >= rhs.size_ || beg == end)
        return;
    if (id > size_)
        id = size_;

    Vector< T > v;
    size_t new_size = size_ + end - beg;
    v.reserve(new_size);

    for (size_t i = 0; i < id; ++i)
        v.push_back(data_[i]);

    for (size_t i = beg; i < end; ++i)
        v.push_back(rhs.data_[i]);

    for (size_t i = id; i < size_; ++i)
        v.push_back(data_[i]);

    swap(v);
}

template <class T>
void zinoviev::Vector<T>::erase(size_t id)
{
    if (size_ <= id)
        return;

    Vector< T > v;

    for (size_t i = 0; i < id; ++i)
        v.push_back(data_[i]);
    for (size_t i = id + 1; i < size_; ++i)
        v.push_back(data_[i]);

    swap(v);
}

template <class T>
void zinoviev::Vector<T>::erase(size_t beg, size_t end)
{
    if (beg > end)
        std::swap(beg, end);
    if (size_ <= beg || beg == end)
        return;

    Vector< T > v;

    for (size_t i = 0; i < beg; ++i)
        v.push_back(data_[i]);
    for (size_t i = end; i < size_; ++i)
        v.push_back(data_[i]);

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
    if (this == std::addressof(rhs))                   // без проверки меняет расположение в память
        return *this;

    Vector< T > cpy(rhs);
    swap(cpy);

    return *this;
}

template <class T>
zinoviev::Vector<T>& zinoviev::Vector<T>::operator=(const Vector< T >&& rhs) noexcept
{
    if (this == std::addressof(rhs))                   // а здесь не поменялось нечего с этой проверкой и без неё
        return *this;

    Vector< T > cpy = std::move(rhs);
    swap(cpy);                        // ОШИБОЧНО будет сразу в swap(...) писать rhs
    return *this;
}


template <class T>
void zinoviev::Vector<T>::swap(Vector< T >& rhs) noexcept
{
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
}




template <class T>
zinoviev::Vector<T>::Iterator::Iterator(T* ptr) noexcept :
    ptr_(ptr)
{}

template <class T>
T& zinoviev::Vector<T>::Iterator::operator*() const noexcept
{
    return *ptr_;
}

template <class T>
T* zinoviev::Vector<T>::Iterator::operator->() const noexcept
{
    return ptr_;
}

template <class T>
typename zinoviev::Vector<T>::Iterator& zinoviev::Vector<T>::Iterator::operator++() noexcept
{
    ++ptr_;
    return *this;
}

template <class T>
typename zinoviev::Vector<T>::Iterator zinoviev::Vector<T>::Iterator::operator++(int) noexcept
{
    Iterator tmp = *this;
    ++ptr_;
    return tmp;
}

template <class T>
typename zinoviev::Vector<T>::Iterator& zinoviev::Vector<T>::Iterator::operator--() noexcept
{
    --ptr_;
    return *this;
}

template <class T>
typename zinoviev::Vector<T>::Iterator zinoviev::Vector<T>::Iterator::operator--(int) noexcept
{
    Iterator tmp = *this;
    --ptr_;
    return tmp;
}



template <class T>
typename zinoviev::Vector<T>::Iterator& zinoviev::Vector<T>::Iterator::operator+=(int n) noexcept
{
    ptr_ += n;
    return *this;
}

template <class T>
typename zinoviev::Vector<T>::Iterator& zinoviev::Vector<T>::Iterator::operator-=(int n) noexcept
{
    ptr_ -= n;
    return *this;
}

template <class T>
typename zinoviev::Vector<T>::Iterator zinoviev::Vector<T>::Iterator::operator+(int n) const noexcept
{
    Iterator tmp = *this;
    tmp += n;
    return tmp;
}

template <class T>
typename zinoviev::Vector<T>::Iterator zinoviev::Vector<T>::Iterator::operator-(int n) const noexcept
{
    Iterator tmp = *this;
    tmp -= n;
    return tmp;
}

template <class T>
T& zinoviev::Vector<T>::Iterator::operator[](size_t n) const noexcept
{
    return ptr_[n];
}



template <class T>
bool zinoviev::Vector<T>::Iterator::operator==(const Iterator& other) const noexcept
{
    return this->ptr_ == other.ptr_;
}

template <class T>
bool zinoviev::Vector<T>::Iterator::operator!=(const Iterator& other) const noexcept
{
    return !(*this == other);
}

template <class T>
bool zinoviev::Vector<T>::Iterator::operator<(const Iterator& other) const noexcept
{
    return this->ptr_ < other.ptr_;
}

template <class T>
bool zinoviev::Vector<T>::Iterator::operator>(const Iterator& other) const noexcept
{
    return this->ptr_ > other.ptr_;
}

template <class T>
bool zinoviev::Vector<T>::Iterator::operator<=(const Iterator& other) const noexcept
{
    return this->ptr_ <= other.ptr_;
}

template <class T>
bool zinoviev::Vector<T>::Iterator::operator>=(const Iterator& other) const noexcept
{
    return this->ptr_ >= other.ptr_;
}



template <class T>
zinoviev::Vector<T>::CIterator::CIterator(T* ptr) noexcept :
    cptr_(ptr)
{}

template <class T>
zinoviev::Vector<T>::CIterator::CIterator(const T* ptr) noexcept :
    cptr_(ptr)
{}

template <class T>
const T& zinoviev::Vector<T>::CIterator::operator*() const noexcept
{
    return *cptr_;
}

template <class T>
const T* zinoviev::Vector<T>::CIterator::operator->() const noexcept
{
    return cptr_;
}

template <class T>
typename zinoviev::Vector<T>::CIterator& zinoviev::Vector<T>::CIterator::operator++() noexcept
{
    ++cptr_;
    return *this;
}

template <class T>
typename zinoviev::Vector<T>::CIterator zinoviev::Vector<T>::CIterator::operator++(int) noexcept
{
    CIterator tmp = *this;
    ++cptr_;
    return tmp;
}

template <class T>
typename zinoviev::Vector<T>::CIterator& zinoviev::Vector<T>::CIterator::operator--() noexcept
{
    --cptr_;
    return *this;
}

template <class T>
typename zinoviev::Vector<T>::CIterator zinoviev::Vector<T>::CIterator::operator--(int) noexcept
{
    CIterator tmp = *this;
    --cptr_;
    return tmp;
}



template <class T>
typename zinoviev::Vector<T>::CIterator& zinoviev::Vector<T>::CIterator::operator+=(int n) noexcept
{
    cptr_ += n;
    return *this;
}

template <class T>
typename zinoviev::Vector<T>::CIterator& zinoviev::Vector<T>::CIterator::operator-=(int n) noexcept
{
    cptr_ -= n;
    return *this;
}

template <class T>
typename zinoviev::Vector<T>::CIterator zinoviev::Vector<T>::CIterator::operator+(int n) const noexcept
{
    CIterator tmp = *this;
    tmp += n;
    return tmp;
}

template <class T>
typename zinoviev::Vector<T>::CIterator zinoviev::Vector<T>::CIterator::operator-(int n) const noexcept
{
    CIterator tmp = *this;
    tmp -= n;
    return tmp;
}

template <class T>
const T& zinoviev::Vector<T>::CIterator::operator[](size_t n) const noexcept
{
    return cptr_[n];
}



template <class T>
bool zinoviev::Vector<T>::CIterator::operator==(const CIterator& other) const noexcept
{
    return this->cptr_ == other.cptr_;
}

template <class T>
bool zinoviev::Vector<T>::CIterator::operator!=(const CIterator& other) const noexcept
{
    return !(*this == other);
}

template <class T>
bool zinoviev::Vector<T>::CIterator::operator<(const CIterator& other) const noexcept
{
    return this->cptr_ < other.cptr_;
}

template <class T>
bool zinoviev::Vector<T>::CIterator::operator>(const CIterator& other) const noexcept
{
    return this->cptr_ > other.cptr_;
}

template <class T>
bool zinoviev::Vector<T>::CIterator::operator<=(const CIterator& other) const noexcept
{
    return this->cptr_ <= other.cptr_;
}

template <class T>
bool zinoviev::Vector<T>::CIterator::operator>=(const CIterator& other) const noexcept
{
    return this->cptr_ >= other.cptr_;
}





template <class T>
typename zinoviev::Vector<T>::Iterator zinoviev::Vector<T>::begin() noexcept
{
    return Iterator(data_);
}

template <class T>
typename zinoviev::Vector<T>::Iterator zinoviev::Vector<T>::end() noexcept
{
    return Iterator(data_ + size_);
}

template <class T>
typename zinoviev::Vector<T>::CIterator zinoviev::Vector<T>::begin() const noexcept
{
    return CIterator(data_);
}

template <class T>
typename zinoviev::Vector<T>::CIterator zinoviev::Vector<T>::end() const noexcept
{
    return CIterator(data_ + size_);
}

template <class T>
typename zinoviev::Vector<T>::CIterator zinoviev::Vector<T>::cbegin() const noexcept
{
    return CIterator(data_);
}

template <class T>
typename zinoviev::Vector<T>::CIterator zinoviev::Vector<T>::cend() const noexcept
{
    return CIterator(data_ + size_);
}



template <class T>
void zinoviev::Vector<T>::insert(Iterator pos, const T& value)
{
    size_t index = pos - begin();
    insert(index, value);
}

template <class T>
void zinoviev::Vector<T>::insert(Iterator pos, size_t count, const T& value)
{
    size_t index = pos - begin();

    Vector<T> tmp(count, value);
    insert(index, tmp, 0, count);
}

template <class T>
void zinoviev::Vector<T>::insert(Iterator pos, const Vector< T >& other)
{
    size_t index = pos - begin();
    insert(index, other, 0, other.getSize());
}

template <class T>
void zinoviev::Vector<T>::erase(Iterator pos)
{
    size_t index = pos - begin();
    erase(index);
}

template <class T>
void zinoviev::Vector<T>::erase(Iterator first, Iterator last)
{
    size_t beg = first - begin();
    size_t end = last - begin();
    erase(beg, end);
}

template <class T>
void zinoviev::Vector<T>::erase(Iterator pos, size_t n)
{
    if (n == 0)
        return;

    size_t index = pos - begin();
    size_t last = index + n;

    if (last > size_)
        last = size_;

    erase(index, last);
}

#endif
