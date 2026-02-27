#ifndef SCHOOLSTATS_H
#define SCHOOLSTATS_H

/// <summary>
/// Структура для хранения статистики по школе.
/// </summary>
struct SchoolStats
{
    int sum;      // сумма баллов
    int count;    // количество учеников

    SchoolStats();
    SchoolStats(int s, int c);
};

#endif // SCHOOLSTATS_H

