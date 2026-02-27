#ifndef MYDICTIONARY_H
#define MYDICTIONARY_H

#include <stdexcept>

/// <summary>
/// Шаблонный класс, реализующий словарь с уникальными ключами на основе параллельных массивов.
/// </summary>
/// <typeparam name="K">Тип ключа. Должен поддерживать оператор ==.</typeparam>
/// <typeparam name="V">Тип значения.</typeparam>
template <typename K, typename V>
class MyDictionary
{
public:
    /// <summary>
    /// Конструктор по умолчанию.
    /// </summary>
    MyDictionary();

    /// <summary>
    /// Конструктор копирования.
    /// </summary>
    MyDictionary(const MyDictionary& other);

    /// <summary>
    /// Оператор присваивания.
    /// </summary>
    MyDictionary& operator=(const MyDictionary& other);

    /// <summary>
    /// Деструктор.
    /// </summary>
    ~MyDictionary();

    /// <summary>
    /// Добавляет пару ключ-значение. Если ключ уже существует, значение обновляется.
    /// </summary>
    void Add(const K& key, const V& value);

    /// <summary>
    /// Удаляет элемент по ключу, если он существует.
    /// </summary>
    void Remove(const K& key);

    /// <summary>
    /// Проверяет наличие ключа в словаре.
    /// </summary>
    bool ContainsKey(const K& key) const;

    /// <summary>
    /// Возвращает ссылку на значение по ключу. Если ключа нет, создаёт элемент со значением по умолчанию.
    /// </summary>
    V& operator[](const K& key);

    /// <summary>
    /// Возвращает значение по ключу (только для чтения). Если ключ отсутствует, генерирует исключение.
    /// </summary>
    const V& operator[](const K& key) const;

    /// <summary>
    /// Возвращает количество элементов в словаре.
    /// </summary>
    int GetSize() const;

    /// <summary>
    /// Возвращает массив ключей (только для чтения) по индексу.
    /// </summary>
    const K& GetKey(int index) const;

    /// <summary>
    /// Возвращает массив значений (только для чтения) по индексу.
    /// </summary>
    const V& GetValue(int index) const;

private:
    K* keys;
    V* values;
    int size;
    int capacity;

    /// <summary>
    /// Увеличивает вместимость массивов в два раза.
    /// </summary>
    void resize();

    /// <summary>
    /// Возвращает индекс ключа или -1, если ключ не найден.
    /// </summary>
    int findIndex(const K& key) const;

};

// Подключаем реализацию шаблонного класса
#include "MyDictionary.cpp"

#endif // MYDICTIONARY_H
