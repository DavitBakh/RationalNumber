# ➗ RationalNumber — C++ Templated Rational Arithmetic Class

![C++20](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg)
![Type](https://img.shields.io/badge/Type-Value%20Type%20%7C%20Template-green.svg)
![Coursework](https://img.shields.io/badge/University-Data%20Structures%20Course-orange.svg)
![Tests](https://img.shields.io/badge/Tests-TDD%20(9%20Suites)-brightgreen.svg)

Университетский курсовой проект по дисциплине **«Структуры данных и алгоритмы»**. Проект представляет собой шаблонный класс рационального числа (`RationalNumber<T>`), обеспечивающий точные вычисления с обыкновенными дробями без потери точности, свойственной числам с плавающей точкой (`float` / `double`).

Класс спроектирован в строгом соответствии с идиомами современного C++ (C++20), принципами ООП и перегрузки операторов стандартной библиотеки C++.

---

## 📌 Основные возможности

- 📐 **Шаблонизация по типу данных**: `template <typename T> class RationalNumber` поддерживает любые целочисленные типы (`int`, `long long`, `short`, `int64_t` и др.).
- 🔄 **Автоматическая канонизация и сокращение**:
  - Сокращение дроби на наибольший общий делитель через `std::gcd`.
  - Приведение к общему знаменателю при сложении и вычитании через наименьшее общее кратное `std::lcm`.
  - Нормализация знака: знаменатель всегда строго положителен (`_denom > 0`), знак дроби переносится в числитель.
- 🛡️ **Контроль корректности и исключения**:
  - При попытке создания дроби с нулевым знаменателем (`denom == 0`) выбрасывается `std::invalid_argument`.
- ➕ **Полный спектр арифметических операций**:
  - Бинарные операторы: `+`, `-`, `*`, `/`.
  - Составное присваивание: `+=`, `-=`, `*=`, `/=`.
  - Унарные операторы: `+`, `-`.
  - Инкремент и декремент (префиксные и постфиксные): `++`, `--`.
- ⚖️ **Операторы сравнения**:
  - `==`, `!=`, `<`, `<=`, `>`, `>=`.
  - Сравнение выполняется через перекрёстное умножение `(a * d < c * b)` без потери точности и без деления с остатком.
- 🔁 **Операторы приведения типов**:
  - `operator int()` — усечение до целого.
  - `operator float()` и `operator double()` — вычисление точного вещественного значения.
  - `operator bool()` — проверка на неравенство нулю (`num != 0`).
- ✍️ **Пользовательские литералы (User-Defined Literals)**:
  - Пространство имён `yourname::literals` предоставляет литерал `_r`, позволяющий создавать рациональные числа вида `42_r` или `0_r`.
- 🖨️ **Потоковый вывод**:
  - Перегрузка `operator<<` для `std::ostream` в формате `числитель/знаменатель` (например, `3/4` или `-1/2`).

---

## 📁 Структура проекта

```text
RationalNumber/
├── RationalNumber.sln               # Решение Visual Studio 2022
├── .gitignore                       # Исключения сборщика и IDE
│
└── RationalNumber/
    ├── RationalNumber.h             # Заголовочный файл: объявление и реализация шаблона класса
    ├── main.cpp                     # Точка входа для запуска набора тестов
    ├── RationalNumber.vcxproj       # Файл проекта MSVC
    │
    └── Tests/                       # Модульные тесты (TDD)
        ├── Test0.h                  # Базовые конструкторы и инициализация
        ├── Test1.h                  # Сложение, вычитание и составное присваивание
        ├── Test2.h                  # Умножение, деление и сокращение дробей
        ├── Test3.h                  # Унарные операторы, префиксный и постфиксный инкремент/декремент
        ├── Test4.h                  # Операторы сравнения (==, !=, <, <=, >, >=)
        ├── Test5.h                  # Проверка исключения при делении на 0 (std::invalid_argument)
        ├── Test6.h                  # Преобразования типов (int, float, double, bool)
        ├── Test7.h                  # Пользовательский литерал _r (User-Defined Literal)
        ├── Test8.h                  # Стресс-тесты и краевые случаи
        └── Utils/                   # Кастомные утверждения (CustomAsserts)
```

---

## 💡 Интерфейс класса

```cpp
namespace yourname {

    template <typename T>
    class RationalNumber {
    public:
        // Конструктор по умолчанию и с параметрами
        RationalNumber(T num = 0, T denom = 1);

        // Составное присваивание
        RationalNumber& operator+=(const RationalNumber& other);
        RationalNumber& operator-=(const RationalNumber& other);
        RationalNumber& operator*=(const RationalNumber& other);
        RationalNumber& operator/=(const RationalNumber& other);

        // Инкремент и декремент
        RationalNumber& operator++();       // ++r
        RationalNumber operator++(int);     // r++
        RationalNumber& operator--();       // --r
        RationalNumber operator--(int);     // r--

        // Унарные операторы
        RationalNumber operator+() const;
        RationalNumber operator-() const;

        // Преобразования типов
        explicit operator int() const;
        explicit operator float() const;
        explicit operator double() const;
        explicit operator bool() const;

        // Ввод/вывод и сравнение
        friend std::ostream& operator<<(std::ostream& os, const RationalNumber<T>& source);
        friend bool operator<(const RationalNumber<T>& lhs, const RationalNumber<T>& rhs);
        friend bool operator==(const RationalNumber<T>& lhs, const RationalNumber<T>& rhs);
    };

    namespace literals {
        RationalNumber<unsigned long long> operator""_r(unsigned long long value);
    }
}
```

---

## 🧪 Модульное тестирование (TDD)

Разработка велась по методологии **Test-Driven Development (TDD)**:
1. `Test0`: Проверка создания дробей, знака в числителе и автоматического сокращения дроби.
2. `Test1`: Арифметика сложения и вычитания дробей с разными знаменателями через `std::lcm`.
3. `Test2`: Умножение, деление и взаимное сокращение множителей.
4. `Test3`: Префиксные и постфиксные формы `++` и `--`, унарный минус.
5. `Test4`: Все 6 операторов сравнения на положительных, отрицательных и равных дробях.
6. `Test5`: Проверка выброса `std::invalid_argument` при знаменателе `0`.
7. `Test6`: Корректность приведения дробей к `bool`, `int`, `float`, `double`.
8. `Test7`: Корректность работы литерала `123_r`.
9. `Test8`: Комплексные выражения и проверка сохранения инварианта дроби.

---

## ⚙️ Сборка и запуск

### Требования
- **ОС**: Windows 10 / 11
- **IDE**: Visual Studio 2022 (v143 toolset)
- **Стандарт C++**: C++20 или C++17

### Инструкция
1. Откройте `RationalNumber.sln` в Visual Studio 2022.
2. Выберите конфигурацию **Debug** или **Release** (x64).
3. Соберите проект (`Ctrl + Shift + B`) и запустите (`Ctrl + F5`).
4. При успешном выполнении всех тестов в консоль выводится:
   ```text
   All tests passed!
   ```

---

## 👨‍💻 Автор

- **Давид Бахшян ([DavitBakh](https://github.com/DavitBakh))**
