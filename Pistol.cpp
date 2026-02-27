#include "Pistol.h"

// Реализация методов класса Pistol
Pistol::Pistol() : maxPatrons(10), currentPatrons(10) {}

Pistol::Pistol(int max) : maxPatrons(max > 0 ? max : 10), currentPatrons(max > 0 ? max : 10) {}

Pistol::Pistol(int max, int current) : maxPatrons(max > 0 ? max : 10), currentPatrons(current >= 0 ? current : 0)
{
    if (currentPatrons > maxPatrons) currentPatrons = maxPatrons;
}

Pistol::~Pistol() {}

void Pistol::Shoot()
{
    if (currentPatrons > 0)
    {
        std::cout << "Bang!\n";
        --currentPatrons;
    }
    else
    {
        std::cout << "Нет патронов!\n";
    }
}

void Pistol::Reload()
{
    currentPatrons = maxPatrons;
    std::cout << "Перезаряжено. Патронов: " << currentPatrons << "\n";
}

int Pistol::GetCurrentPatrons() const { return currentPatrons; }

int Pistol::GetMaxPatrons() const { return maxPatrons; }

// Реализация методов класса Automatic
Automatic::Automatic() : Pistol(30), fireRate(30) {}

Automatic::Automatic(int maxPatrons) : Pistol(maxPatrons), fireRate(maxPatrons / 2) {}

Automatic::Automatic(int maxPatrons, int rate) : Pistol(maxPatrons), fireRate(rate > 0 ? rate : 1) {}

void Automatic::Shoot()
{
    int shots = fireRate;
    for (int i = 0; i < shots; ++i)
    {
        if (currentPatrons > 0)
        {
            std::cout << "Bang! (automatic)\n";
            --currentPatrons;
        }
        else
        {
            std::cout << "Патроны кончились!\n";
            break;
        }
    }
}

void Automatic::Shoot(int seconds)
{
    if (seconds <= 0)
    {
        std::cout << "Некорректное время\n";
        return;
    }
    int totalShots = seconds * fireRate;
    for (int i = 0; i < totalShots; ++i)
    {
        if (currentPatrons > 0)
        {
            std::cout << "Bang! (automatic, time firing)\n";
            --currentPatrons;
        }
        else
        {
            std::cout << "Патроны кончились!\n";
            break;
        }
    }
}

int Automatic::GetFireRate() const { return fireRate; }
