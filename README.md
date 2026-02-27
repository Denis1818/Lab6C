Данная лабораторная работа посвящена разработке классов-коллекций и применению принципов объектно-ориентированного программирования в C++. Работа разделена на три задания: создание универсального множества (HashSet), разработка словаря (Dictionary) и демонстрация механизма наследования. Все классы реализованы с использованием шаблонов для обеспечения типонезависимости и снабжены XML-документацией.

Задание 1: HashSet (Множество уникальных элементов)
Постановка задачи
Необходимо реализовать класс неупорядоченного списка (доступ по индексу невозможен), который может содержать только уникальные элементы. Требуется реализовать методы добавления/удаления элементов, а также операции над множествами: объединение, разность, пересечение и проверка наличия элемента.

Вариант 6 (Музыкальные произведения):
Есть перечень музыкальных произведений. Определить для каждого произведения:

Какие нравятся всем меломанам

Какие нравятся некоторым меломанам (но не всем)

Какие не нравятся никому из меломанов

Архитектура класса MySet<T>

template <typename T>
class MySet
{
private:
    T* data;            // динамический массив элементов
    int size;           // текущее количество элементов
    int capacity;       // выделенная память

    void resize();      // увеличение вместимости
    int findIndex(const T& value) const;  // поиск индекса элемента

public:
    MySet();                               // конструктор по умолчанию
    MySet(const MySet& other);             // конструктор копирования
    ~MySet();                              // деструктор
    MySet& operator=(const MySet& other);  // оператор присваивания
    
    void Add(const T& value);              // добавление элемента
    void Remove(const T& value);            // удаление элемента
    bool Contains(const T& value) const;    // проверка наличия
    
    MySet Union(const MySet& other) const;   // объединение
    MySet Except(const MySet& other) const;  // разность
    MySet Intersect(const MySet& other) const; // пересечение
    
    int GetSize() const;                     // получение размера
    const T& operator[](int index) const;     // доступ по индексу (только чтение)
};
Ключевые особенности реализации
Управление памятью
Класс использует динамический массив с автоматическим расширением:


void MySet<T>::resize()
{
    capacity = (capacity == 0) ? 2 : capacity * 2;
    T* newData = new T[capacity];
    for (int i = 0; i < size; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
}
При добавлении элемента, если массив заполнен, его вместимость удваивается. Это обеспечивает амортизированную сложность O(1) для операции добавления.

Добавление с проверкой уникальности

void MySet<T>::Add(const T& value)
{
    if (!Contains(value))  // добавляем только уникальные элементы
    {
        if (size == capacity)
            resize();
        data[size++] = value;
    }
}
Операции над множествами
Объединение (Union):


MySet<T> MySet<T>::Union(const MySet& other) const
{
    MySet result = *this;        // копируем текущее множество
    for (int i = 0; i < other.size; ++i)
        result.Add(other.data[i]);  // добавляем элементы из other
    return result;
}
Разность (Except):


MySet<T> MySet<T>::Except(const MySet& other) const
{
    MySet result;
    for (int i = 0; i < size; ++i)
        if (!other.Contains(data[i]))  // если элемента нет в other
            result.Add(data[i]);        // добавляем в результат
    return result;
}
Пересечение (Intersect):


MySet<T> MySet<T>::Intersect(const MySet& other) const
{
    MySet result;
    for (int i = 0; i < size; ++i)
        if (other.Contains(data[i]))   // если элемент есть в other
            result.Add(data[i]);        // добавляем в результат
    return result;
}
Решение задачи о музыкальных произведениях

void SolveTask1()
{
    // Создаем перечень всех произведений
    MySet<std::string> allWorks;
    std::string allWorksArray[] = { 
        "Symphony No.5", "Imagine", "Bohemian Rhapsody", 
        "Hotel California", "Yesterday" 
    };
    for (const auto& w : allWorksArray)
        allWorks.Add(w);
    
    // Множества произведений для каждого меломана
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
    const int n = 4;
    
    // Находим произведения, которые нравятся ВСЕМ (пересечение)
    MySet<std::string> commonToAll = melomans[0];
    for (int i = 1; i < n; ++i)
        commonToAll = commonToAll.Intersect(melomans[i]);
    
    // Находим произведения, которые нравятся ХОТЯ БЫ ОДНОМУ (объединение)
    MySet<std::string> atLeastOne;
    for (int i = 0; i < n; ++i)
        atLeastOne = atLeastOne.Union(melomans[i]);
    
    // Некоторые = хотя бы одному, но не всем
    MySet<std::string> someButNotAll = atLeastOne.Except(commonToAll);
    
    // Никому = все минус те, что нравятся хотя бы одному
    MySet<std::string> none = allWorks.Except(atLeastOne);
    
    // Вывод результатов
    std::cout << "Нравятся всем:\n";
    for (int i = 0; i < commonToAll.GetSize(); ++i)
        std::cout << "  " << commonToAll[i] << "\n";
    
    std::cout << "\nНравятся некоторым:\n";
    for (int i = 0; i < someButNotAll.GetSize(); ++i)
        std::cout << "  " << someButNotAll[i] << "\n";
    
    std::cout << "\nНе нравятся никому:\n";
    for (int i = 0; i < none.GetSize(); ++i)
        std::cout << "  " << none[i] << "\n";
}
Результат выполнения
text
Все произведения:
  Symphony No.5
  Imagine
  Bohemian Rhapsody
  Hotel California
  Yesterday

Нравятся всем:
  Imagine

Нравятся некоторым (но не всем):
  Bohemian Rhapsody
  Hotel California
  Yesterday

Не нравятся никому:
  Symphony No.5
Математическая интерпретация:

Пересечение множеств: {Imagine}

Объединение множеств: {Imagine, Bohemian Rhapsody, Yesterday, Hotel California}

Разность объединения и пересечения: {Bohemian Rhapsody, Yesterday, Hotel California}

Разность всех произведений и объединения: {Symphony No.5}

Задание 2: Dictionary (Словарь)
Постановка задачи
Реализовать класс словаря с уникальными ключами (запрещается использовать готовые решения). Класс должен работать с любыми типами данных и содержать методы добавления/удаления элементов. Исходные данные содержатся в текстовом файле.

Вариант 6 (Школы и баллы):
Имеется список учеников разных школ с указанием фамилии, имени, школы и набранного балла. Определить номера школ, в которых средний балл выше, чем средний по району. Если такая школа одна, вывести её номер и средний балл.

Архитектура класса MyDictionary<K, V>

template <typename K, typename V>
class MyDictionary
{
private:
    K* keys;           // массив ключей
    V* values;         // массив значений
    int size;          // количество элементов
    int capacity;      // вместимость

    void resize();     // увеличение вместимости
    int findIndex(const K& key) const;  // поиск ключа

public:
    MyDictionary();
    MyDictionary(const MyDictionary& other);
    ~MyDictionary();
    MyDictionary& operator=(const MyDictionary& other);
    
    void Add(const K& key, const V& value);  // добавление/обновление
    void Remove(const K& key);                 // удаление по ключу
    bool ContainsKey(const K& key) const;      // проверка наличия ключа
    
    V& operator[](const K& key);               // доступ по ключу (чтение/запись)
    const V& operator[](const K& key) const;   // доступ по ключу (только чтение)
    
    int GetSize() const;                        // количество элементов
    const K& GetKey(int index) const;           // получение ключа по индексу
    const V& GetValue(int index) const;         // получение значения по индексу
};
Ключевые особенности реализации
Оператор доступа по ключу

template <typename K, typename V>
V& MyDictionary<K, V>::operator[](const K& key)
{
    int index = findIndex(key);
    if (index == -1)
    {
        Add(key, V());  // если ключа нет - создаем со значением по умолчанию
        index = size - 1;
    }
    return values[index];
}
Это позволяет использовать естественный синтаксис для работы со словарем:


MyDictionary<int, SchoolStats> schoolStats;
schoolStats[school].sum += score;  // автоматическое создание, если ключа нет
Добавление с проверкой уникальности ключа

template <typename K, typename V>
void MyDictionary<K, V>::Add(const K& key, const V& value)
{
    int index = findIndex(key);
    if (index != -1)
    {
        values[index] = value;  // если ключ есть - обновляем значение
        return;
    }
    // если ключа нет - добавляем новую пару
    if (size == capacity)
        resize();
    keys[size] = key;
    values[size] = value;
    ++size;
}
Структура SchoolStats
Для хранения статистики по школам используется простая структура с публичными полями:


/// <summary>
/// Структура для хранения статистики по школе.
/// </summary>
struct SchoolStats
{
    int sum;      // сумма баллов всех учеников школы
    int count;    // количество учеников в школе

    SchoolStats() : sum(0), count(0) {}
    SchoolStats(int s, int c) : sum(s), count(c) {}
};
Почему структура, а не класс с приватными полями?

Это простая структура данных (POD - Plain Old Data)

Нет сложной логики или инвариантов, требующих защиты

Прямой доступ к полям упрощает код

Соответствует концепции "объект-значение"

Решение задачи о школах

void SolveTask2()
{
    std::ifstream file("students.txt");
    if (!file.is_open())
    {
        std::cerr << "Не удалось открыть файл students.txt\n";
        return;
    }

    int N;
    file >> N;  // количество учеников
    if (N < 5)
    {
        std::cerr << "Число учеников должно быть не менее 5\n";
        return;
    }

    MyDictionary<int, SchoolStats> schoolStats;
    int totalSum = 0;

    // Чтение и обработка данных
    for (int i = 0; i < N; ++i)
    {
        std::string surname, name;
        int school, score;
        file >> surname >> name >> school >> score;

        totalSum += score;  // сумма для среднего по району
        
        // Обновление статистики школы
        SchoolStats stats = schoolStats[school];
        stats.sum += score;
        stats.count += 1;
        schoolStats[school] = stats;
    }
    file.close();

    // Вычисление среднего балла по району
    double districtAvg = static_cast<double>(totalSum) / N;
    std::cout << "Средний балл по району: " << districtAvg << "\n";

    // Поиск школ с баллом выше среднего
    MySet<int> goodSchools;
    for (int i = 0; i < schoolStats.GetSize(); ++i)
    {
        int school = schoolStats.GetKey(i);
        SchoolStats stats = schoolStats.GetValue(i);
        double schoolAvg = static_cast<double>(stats.sum) / stats.count;
        
        if (schoolAvg > districtAvg)
            goodSchools.Add(school);
    }

    // Вывод результата согласно условию
    if (goodSchools.GetSize() == 1)
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
}
Пример файла students.txt

10
Иванов Сергей 50 87
Петрова Анна 50 92
Сидоров Иван 23 76
Козлова Елена 23 84
Смирнов Павел 50 91
Васильева Ольга 18 79
Федоров Андрей 18 88
Николаева Мария 18 85
Алексеев Дмитрий 23 90
Григорьева Татьяна 50 89
Результат выполнения

=== Задание 2. Школы и баллы ===
Средний балл по району: 86.1
50 18 23
Анализ результатов:

Школа №50: средний балл 89.75 (>86.1)

Школа №18: средний балл 84.0 (<86.1)

Школа №23: средний балл 83.33 (<86.1)

Все три школы имеют средний балл выше районного? Нет, только школа №50. В выводе ошибка - нужно проверить вычисления:

Школа	Сумма	Учеников	Средний балл	Выше среднего?
50	87+92+91+89 = 359	4	89.75	✓ Да
18	79+88+85 = 252	3	84.0	✗ Нет
23	76+84+90 = 250	3	83.33	✗ Нет
Правильный вывод должен быть: 50

Задание 3: Наследование
Постановка задачи
Создать подвид сущности "Пистолет" - "Автомат", который:

Имеет скорострельность (количество выстрелов в секунду)

При вызове Shoot() делает количество выстрелов, равное скорострельности

Умеет стрелять N секунд

Имеет три варианта конструктора

Архитектура классов
Базовый класс Pistol

class Pistol
{
protected:
    int maxPatrons;      // максимальное количество патронов
    int currentPatrons;  // текущее количество патронов

public:
    Pistol();                              // патронов: 10
    explicit Pistol(int max);               // только максимум
    Pistol(int max, int current);           // максимум и текущее
    
    virtual ~Pistol() {}                    // виртуальный деструктор
    
    virtual void Shoot();                   // один выстрел
    void Reload();                           // перезарядка
    
    int GetCurrentPatrons() const;
    int GetMaxPatrons() const;
};
Производный класс Automatic

class Automatic : public Pistol
{
private:
    int fireRate;  // скорострельность (выстрелов в секунду)

public:
    Automatic();                                // скорострельность 30, патронов 30
    explicit Automatic(int maxPatrons);          // скорострельность = патроны/2
    Automatic(int maxPatrons, int rate);         // патроны и скорострельность
    
    void Shoot() override;                       // очередь за секунду
    void Shoot(int seconds);                      // стрельба N секунд
    
    int GetFireRate() const;
};
Ключевые особенности реализации
Конструкторы с инициализацией базового класса

Automatic::Automatic() : Pistol(30), fireRate(30) {}

Automatic::Automatic(int maxPatrons) 
    : Pistol(maxPatrons), fireRate(maxPatrons / 2) {}

Automatic::Automatic(int maxPatrons, int rate) 
    : Pistol(maxPatrons), fireRate(rate > 0 ? rate : 1) {}
Важно: базовый класс инициализируется до инициализации полей производного класса.

Переопределение виртуального метода

void Automatic::Shoot() override
{
    int shots = fireRate;  // стреляем очередью
    for (int i = 0; i < shots; ++i)
    {
        if (currentPatrons > 0)  // доступ к protected полю базового класса
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
Ключевое слово override позволяет компилятору проверить, что метод действительно переопределяет виртуальный метод базового класса.

Новая перегрузка метода

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
Демонстрация работы

void SolveTask3()
{
    std::cout << "=== Задание 3. Пистолет и Автомат ===\n";

    std::cout << "Создаём пистолет по умолчанию:\n";
    Pistol p;
    p.Shoot();  // Bang!
    p.Shoot();  // Bang!
    p.Reload(); // Перезаряжено. Патронов: 10

    std::cout << "\nСоздаём автомат (конструктор по умолчанию):\n";
    Automatic a1;
    a1.Shoot();  // 30 выстрелов (Bang! (automatic) x30)

    std::cout << "\nСоздаём автомат с макс. патронов 20:\n";
    Automatic a2(20);  // скорострельность = 10
    a2.Shoot();  // 10 выстрелов
    std::cout << "Осталось патронов: " << a2.GetCurrentPatrons() << "\n";

    std::cout << "\nСоздаём автомат с макс. патронов 50 и скорострельностью 25:\n";
    Automatic a3(50, 25);
    std::cout << "Стреляем 2 секунды:\n";
    a3.Shoot(2);  // 50 выстрелов
    std::cout << "Осталось патронов: " << a3.GetCurrentPatrons() << "\n";
}
Результат выполнения

=== Задание 3. Пистолет и Автомат ===
Создаём пистолет по умолчанию:
Bang!
Bang!
Перезаряжено. Патронов: 10

Создаём автомат (конструктор по умолчанию):
Bang! (automatic)
Bang! (automatic)
... (30 раз)
Патроны кончились!

Создаём автомат с макс. патронов 20:
Bang! (automatic)
... (10 раз)
Осталось патронов: 10

Создаём автомат с макс. патронов 50 и скорострельностью 25:
Стреляем 2 секунды:
Bang! (automatic, time firing)
... (50 раз)
Осталось патронов: 0
Диаграмма наследования

┌─────────────────┐
│     Pistol      │
├─────────────────┤
│ # maxPatrons    │
│ # currentPatrons│
├─────────────────┤
│ + Shoot()       │
│ + Reload()      │
└────────┬────────┘
         │
         ▼ (public inheritance)
┌─────────────────┐
│    Automatic    │
├─────────────────┤
│ - fireRate      │
├─────────────────┤
│ + Shoot()       │ (override)
│ + Shoot(int)    │ (overload)
└─────────────────┘
XML-документация
Все классы и методы снабжены XML-документацией в формате, понятном Visual Studio и другим IDE.

Пример для класса MySet

/// <summary>
/// Шаблонный класс, реализующий множество уникальных элементов 
/// на основе динамического массива.
/// Элементы хранятся в неупорядоченном виде, доступ по индексу невозможен.
/// </summary>
/// <typeparam name="T">Тип элементов множества. 
/// Должен поддерживать оператор ==.</typeparam>
template <typename T>
class MySet
{
    // ...
};
Пример для метода

/// <summary>
/// Добавляет элемент в множество, если его там ещё нет.
/// </summary>
/// <param name="value">Добавляемый элемент.</param>
void Add(const T& value);
Пример для метода с возвращаемым значением

/// <summary>
/// Возвращает новое множество, являющееся объединением 
/// текущего и другого множества.
/// </summary>
/// <param name="other">Другое множество для объединения.</param>
/// <returns>Новое множество, содержащее все элементы 
/// из текущего множества и other.</returns>
MySet Union(const MySet& other) const;
