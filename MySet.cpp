#ifndef MYSET_CPP
#define MYSET_CPP

#include "MySet.h"

template <typename T>
void MySet<T>::resize()
{
    capacity = (capacity == 0) ? 2 : capacity * 2;
    T* newData = new T[capacity];
    for (int i = 0; i < size; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
}

template <typename T>
int MySet<T>::findIndex(const T& value) const
{
    for (int i = 0; i < size; ++i)
        if (data[i] == value)
            return i;
    return -1;
}

template <typename T>
MySet<T>::MySet() : data(nullptr), size(0), capacity(0) {}

template <typename T>
MySet<T>::MySet(const MySet& other) : data(nullptr), size(other.size), capacity(other.capacity)
{
    if (capacity > 0)
    {
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
}

template <typename T>
MySet<T>& MySet<T>::operator=(const MySet& other)
{
    if (this != &other)
    {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        if (capacity > 0)
        {
            data = new T[capacity];
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        else
        {
            data = nullptr;
        }
    }
    return *this;
}

template <typename T>
MySet<T>::~MySet()
{
    delete[] data;
}

template <typename T>
void MySet<T>::Add(const T& value)
{
    if (!Contains(value))
    {
        if (size == capacity)
            resize();
        data[size++] = value;
    }
}

template <typename T>
void MySet<T>::Remove(const T& value)
{
    int index = findIndex(value);
    if (index != -1)
    {
        for (int i = index; i < size - 1; ++i)
            data[i] = data[i + 1];
        --size;
    }
}

template <typename T>
bool MySet<T>::Contains(const T& value) const
{
    return findIndex(value) != -1;
}

template <typename T>
MySet<T> MySet<T>::Union(const MySet& other) const
{
    MySet result = *this;
    for (int i = 0; i < other.size; ++i)
        result.Add(other.data[i]);
    return result;
}

template <typename T>
MySet<T> MySet<T>::Except(const MySet& other) const
{
    MySet result;
    for (int i = 0; i < size; ++i)
        if (!other.Contains(data[i]))
            result.Add(data[i]);
    return result;
}

template <typename T>
MySet<T> MySet<T>::Intersect(const MySet& other) const
{
    MySet result;
    for (int i = 0; i < size; ++i)
        if (other.Contains(data[i]))
            result.Add(data[i]);
    return result;
}

template <typename T>
int MySet<T>::GetSize() const { return size; }

template <typename T>
const T& MySet<T>::operator[](int index) const
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

#endif // MYSET_CPP
