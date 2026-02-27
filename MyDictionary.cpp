#ifndef MYDICTIONARY_CPP
#define MYDICTIONARY_CPP

#include "MyDictionary.h"

template <typename K, typename V>
void MyDictionary<K, V>::resize()
{
    capacity = (capacity == 0) ? 2 : capacity * 2;
    K* newKeys = new K[capacity];
    V* newValues = new V[capacity];
    for (int i = 0; i < size; ++i)
    {
        newKeys[i] = keys[i];
        newValues[i] = values[i];
    }
    delete[] keys;
    delete[] values;
    keys = newKeys;
    values = newValues;
}

template <typename K, typename V>
int MyDictionary<K, V>::findIndex(const K& key) const
{
    for (int i = 0; i < size; ++i)
        if (keys[i] == key)
            return i;
    return -1;
}

template <typename K, typename V>
MyDictionary<K, V>::MyDictionary() : keys(nullptr), values(nullptr), size(0), capacity(0) {}

template <typename K, typename V>
MyDictionary<K, V>::MyDictionary(const MyDictionary& other)
    : keys(nullptr), values(nullptr), size(other.size), capacity(other.capacity)
{
    if (capacity > 0)
    {
        keys = new K[capacity];
        values = new V[capacity];
        for (int i = 0; i < size; ++i)
        {
            keys[i] = other.keys[i];
            values[i] = other.values[i];
        }
    }
}

template <typename K, typename V>
MyDictionary<K, V>& MyDictionary<K, V>::operator=(const MyDictionary& other)
{
    if (this != &other)
    {
        delete[] keys;
        delete[] values;
        size = other.size;
        capacity = other.capacity;
        if (capacity > 0)
        {
            keys = new K[capacity];
            values = new V[capacity];
            for (int i = 0; i < size; ++i)
            {
                keys[i] = other.keys[i];
                values[i] = other.values[i];
            }
        }
        else
        {
            keys = nullptr;
            values = nullptr;
        }
    }
    return *this;
}

template <typename K, typename V>
MyDictionary<K, V>::~MyDictionary()
{
    delete[] keys;
    delete[] values;
}

template <typename K, typename V>
void MyDictionary<K, V>::Add(const K& key, const V& value)
{
    int index = findIndex(key);
    if (index != -1)
    {
        values[index] = value; // обновление
        return;
    }
    if (size == capacity)
        resize();
    keys[size] = key;
    values[size] = value;
    ++size;
}

template <typename K, typename V>
void MyDictionary<K, V>::Remove(const K& key)
{
    int index = findIndex(key);
    if (index != -1)
    {
        for (int i = index; i < size - 1; ++i)
        {
            keys[i] = keys[i + 1];
            values[i] = values[i + 1];
        }
        --size;
    }
}

template <typename K, typename V>
bool MyDictionary<K, V>::ContainsKey(const K& key) const
{
    return findIndex(key) != -1;
}

template <typename K, typename V>
V& MyDictionary<K, V>::operator[](const K& key)
{
    int index = findIndex(key);
    if (index == -1)
    {
        Add(key, V());
        index = size - 1;
    }
    return values[index];
}

template <typename K, typename V>
const V& MyDictionary<K, V>::operator[](const K& key) const
{
    int index = findIndex(key);
    if (index == -1)
        throw std::out_of_range("Key not found");
    return values[index];
}

template <typename K, typename V>
int MyDictionary<K, V>::GetSize() const { return size; }

template <typename K, typename V>
const K& MyDictionary<K, V>::GetKey(int index) const
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return keys[index];
}

template <typename K, typename V>
const V& MyDictionary<K, V>::GetValue(int index) const
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return values[index];
}

#endif // MYDICTIONARY_CPP
