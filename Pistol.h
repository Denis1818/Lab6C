#ifndef PISTOL_H
#define PISTOL_H

#include <iostream>

/// <summary>
/// Базовый класс, представляющий пистолет.
/// </summary>
class Pistol
{
protected:
    int maxPatrons;     // максимальное количество патронов в обойме
    int currentPatrons; // текущее количество патронов

public:
    /// <summary>
    /// Конструктор по умолчанию. Создаёт пистолет с максимальным количеством патронов 10.
    /// </summary>
    Pistol();

    /// <summary>
    /// Конструктор с указанием максимального количества патронов.
    /// </summary>
    /// <param name="max">Максимальное количество патронов.</param>
    explicit Pistol(int max);

    /// <summary>
    /// Конструктор с указанием максимального количества патронов и начального количества.
    /// </summary>
    /// <param name="max">Максимальное количество патронов.</param>
    /// <param name="current">Начальное количество патронов.</param>
    Pistol(int max, int current);

    /// <summary>
    /// Виртуальный деструктор.
    /// </summary>
    virtual ~Pistol();

    /// <summary>
    /// Выполняет один выстрел, если есть патроны. Уменьшает количество патронов на 1.
    /// </summary>
    virtual void Shoot();

    /// <summary>
    /// Перезаряжает пистолет до максимума.
    /// </summary>
    void Reload();

    /// <summary>
    /// Возвращает текущее количество патронов.
    /// </summary>
    int GetCurrentPatrons() const;

    /// <summary>
    /// Возвращает максимальное количество патронов.
    /// </summary>
    int GetMaxPatrons() const;
};

/// <summary>
/// Класс Автомат, наследник Пистолета. Добавляет свойство скорострельности.
/// </summary>
class Automatic : public Pistol
{
public:
    /// <summary>
    /// Конструктор без параметров. Скорострельность = 30, максимальное количество патронов = 30.
    /// </summary>
    Automatic();

    /// <summary>
    /// Конструктор с указанием максимального количества патронов.
    /// Скорострельность устанавливается равной половине максимального количества патронов.
    /// </summary>
    /// <param name="maxPatrons">Максимальное количество патронов.</param>
    explicit Automatic(int maxPatrons);

    /// <summary>
    /// Конструктор с указанием максимального количества патронов и скорострельности.
    /// </summary>
    /// <param name="maxPatrons">Максимальное количество патронов.</param>
    /// <param name="rate">Скорострельность (должна быть положительной).</param>
    Automatic(int maxPatrons, int rate);

    /// <summary>
    /// Выполняет серию выстрелов в количестве, равном скорострельности.
    /// Каждый выстрел использует один патрон. Если патроны заканчиваются, стрельба прекращается.
    /// </summary>
    void Shoot() override;

    /// <summary>
    /// Стреляет в течение заданного количества секунд.
    /// Общее количество выстрелов = секунды * скорострельность.
    /// </summary>
    /// <param name="seconds">Количество секунд стрельбы.</param>
    void Shoot(int seconds);

    /// <summary>
    /// Возвращает скорострельность.
    /// </summary>
    int GetFireRate() const;
private:
    int fireRate; // скорострельность (выстрелов в секунду)

};

#endif // PISTOL_H
