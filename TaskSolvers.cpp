#include "TaskSolvers.h"
#include "MySet.h"
#include "MyDictionary.h"
#include "SchoolStats.h"
#include "Pistol.h"
#include <iostream>
#include <fstream>
#include <string>

void SolveTask1()
{
    std::cout << "=== Задание 1. Музыкальные произведения ===\n";

    // Входные данные: общий перечень произведений
    std::string allWorksArray[] = { "Symphony No.5", "Imagine", "Bohemian Rhapsody", "Hotel California", "Yesterday" };
    MySet<std::string> allWorks;
    for (const auto& w : allWorksArray)
        allWorks.Add(w);

    // Множества произведений, которые нравятся каждому меломану
    MySet<std::string> meloman1;
    meloman1.Add("Imagine");
    meloman1.Add("Bohemian Rhapsody");
    meloman1.Add("Yesterday");

    MySet<std::string> meloman2;
    meloman2.Add("Imagine");
    meloman2.Add("Hotel California");

    MySet<std::string> meloman3;
    meloman3.Add("Imagine");
    meloman3.Add("Bohemian Rhapsody");
    meloman3.Add("Hotel California");

    MySet<std::string> meloman4;
    meloman4.Add("Imagine");
    meloman4.Add("Yesterday");

    MySet<std::string> melomans[] = { meloman1, meloman2, meloman3, meloman4 };
    const int n = 4; // количество меломанов

    // Находим пересечение всех множеств (нравится всем)
    MySet<std::string> commonToAll = melomans[0];
    for (int i = 1; i < n; ++i)
        commonToAll = commonToAll.Intersect(melomans[i]);

    // Находим объединение всех множеств (нравится хотя бы одному)
    MySet<std::string> atLeastOne;
    for (int i = 0; i < n; ++i)
        atLeastOne = atLeastOne.Union(melomans[i]);

    // Нравится некоторым (хотя бы одному, но не всем) = atLeastOne \ commonToAll
    MySet<std::string> someButNotAll = atLeastOne.Except(commonToAll);

    // Не нравится никому = все произведения \ atLeastOne
    MySet<std::string> none = allWorks.Except(atLeastOne);

    std::cout << "Все произведения:\n";
    for (int i = 0; i < allWorks.GetSize(); ++i)
        std::cout << "  " << allWorks[i] << "\n";

    std::cout << "\nНравятся всем:\n";
    for (int i = 0; i < commonToAll.GetSize(); ++i)
        std::cout << "  " << commonToAll[i] << "\n";

    std::cout << "\nНравятся некоторым (но не всем):\n";
    for (int i = 0; i < someButNotAll.GetSize(); ++i)
        std::cout << "  " << someButNotAll[i] << "\n";

    std::cout << "\nНе нравятся никому:\n";
    for (int i = 0; i < none.GetSize(); ++i)
        std::cout << "  " << none[i] << "\n";

    std::cout << std::endl;
}

void SolveTask2()
{
    std::cout << "=== Задание 2. Школы и баллы ===\n";

    std::ifstream file("students.txt");
    if (!file.is_open())
    {
        std::cerr << "Не удалось открыть файл students.txt\n";
        return;
    }

    int N;
    file >> N;
    if (N < 5)
    {
        std::cerr << "Число учеников должно быть не менее 5\n";
        return;
    }

    MyDictionary<int, SchoolStats> schoolStats;
    int totalSum = 0;

    for (int i = 0; i < N; ++i)
    {
        std::string surname, name;
        int school, score;
        file >> surname >> name >> school >> score;

        totalSum += score;
        SchoolStats stats = schoolStats[school];
        stats.sum += score;
        stats.count += 1;
        schoolStats[school] = stats; // обновляем
    }
    file.close();

    double districtAvg = static_cast<double>(totalSum) / N;
    std::cout << "Средний балл по району: " << districtAvg << "\n";

    // Собираем школы с баллом выше среднего
    MySet<int> goodSchools;
    for (int i = 0; i < schoolStats.GetSize(); ++i)
    {
        int school = schoolStats.GetKey(i);
        SchoolStats stats = schoolStats.GetValue(i);
        double schoolAvg = static_cast<double>(stats.sum) / stats.count;
        if (schoolAvg > districtAvg)
            goodSchools.Add(school);
    }

    if (goodSchools.GetSize() == 0)
    {
        std::cout << "Нет школ со средним баллом выше районного\n";
    }
    else if (goodSchools.GetSize() == 1)
    {
        int school = goodSchools[0];
        SchoolStats stats = schoolStats[school];
        double schoolAvg = static_cast<double>(stats.sum) / stats.count;
        std::cout << school << "\n";
        std::cout << "Средний балл = " << schoolAvg << "\n";
    }
    else
    {
        for (int i = 0; i < goodSchools.GetSize(); ++i)
            std::cout << goodSchools[i] << " ";
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void SolveTask3()
{
    std::cout << "=== Задание 3. Пистолет и Автомат ===\n";

    std::cout << "Создаём пистолет по умолчанию:\n";
    Pistol p;
    p.Shoot();
    p.Shoot();
    p.Reload();

    std::cout << "\nСоздаём автомат (конструктор по умолчанию):\n";
    Automatic a1;
    a1.Shoot();
    a1.Shoot();

    std::cout << "\nСоздаём автомат с макс. патронов 20 (скорострельность 10):\n";
    Automatic a2(20);
    a2.Shoot();
    std::cout << "Осталось патронов: " << a2.GetCurrentPatrons() << "\n";

    std::cout << "\nСоздаём автомат с макс. патронов 50 и скорострельностью 25:\n";
    Automatic a3(50, 25);
    std::cout << "Стреляем 2 секунды:\n";
    a3.Shoot(2);
    std::cout << "Осталось патронов: " << a3.GetCurrentPatrons() << "\n";

    std::cout << std::endl;
}
