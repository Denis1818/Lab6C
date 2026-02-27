#ifndef MYSET_H
#define MYSET_H

#include <stdexcept>

/// <summary>
/// Шаблонный класс, реализующий множество уникальных элементов на основе динамического массива.
/// Элементы хранятся в неупорядоченном виде, доступ по индексу невозможен.
/// </summary>
/// <typeparam name="T">Тип элементов множества. Должен поддерживать оператор ==.</typeparam>
template <typename T>
class MySet
{
public:
    /// <summary>
    /// Конструктор по умолчанию. Создаёт пустое множество.
    /// </summary>
    MySet();

    /// <summary>
    /// Конструктор копирования.
    /// </summary>
    MySet(const MySet& other);

    /// <summary>
    /// Оператор присваивания.
    /// </summary>
    MySet& operator=(const MySet& other);

    /// <summary>
    /// Деструктор. Освобождает динамическую память.
    /// </summary>
    ~MySet();

    /// <summary>
    /// Добавляет элемент в множество, если его там ещё нет.
    /// </summary>
    /// <param name="value">Добавляемый элемент.</param>
    void Add(const T& value);

    /// <summary>
    /// Удаляет элемент из множества, если он присутствует.
    /// </summary>
    /// <param name="value">Удаляемый элемент.</param>
    void Remove(const T& value);

    /// <summary>
    /// Проверяет наличие элемента в множестве.
    /// </summary>
    /// <returns>true, если элемент присутствует; иначе false.</returns>
    bool Contains(const T& value) const;

    /// <summary>
    /// Возвращает новое множество, являющееся объединением текущего и другого множества.
    /// </summary>
    MySet Union(const MySet& other) const;

    /// <summary>
    /// Возвращает новое множество, являющееся разностью текущего и другого множества.
    /// </summary>
    MySet Except(const MySet& other) const;

    /// <summary>
    /// Возвращает новое множество, являющееся пересечением текущего и другого множества.
    /// </summary>
    MySet Intersect(const MySet& other) const;

    /// <summary>
    /// Возвращает текущее количество элементов в множестве.
    /// </summary>
    int GetSize() const;

    /// <summary>
    /// Позволяет перебирать элементы множества (доступ по индексу только для чтения).
    /// </summary>
    const T& operator[](int index) const;

private:
    T* data;            // массив элементов
    int size;           // текущее количество элементов
    int capacity;       // вместимость массива

    /// <summary>
    /// Увеличивает вместимость массива в два раза.
    /// </summary>
    void resize();

    /// <summary>
    /// Возвращает индекс элемента в массиве или -1, если элемент не найден.
    /// </summary>
    int findIndex(const T& value) const;
};

// Подключаем реализацию шаблонного класса
#include "MySet.cpp"

#endif // MYSET_H
