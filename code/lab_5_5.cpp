// Лабораторна робота 5.5, варіант 7. Джамалов О. О., РІ-11.
// Рекурсивне зображення натурального числа в системах з основами 2, 8 і N > 1;
// виведення рівня кожного виклику та глибини рекурсії.
#include <algorithm> // max
#include <iomanip>   // setw
#include <iostream>  // cin, cout, cerr
#include <string>    // string, to_string
using namespace std;

// Рядок трасування: рівень рекурсії, поточне число, цифра (остача).
void traceRow(ostream& trace, int level, long long n, const string& digit)
{
    trace << "| " << setw(5) << level << " | " << setw(20) << n
          << " | " << setw(6) << digit << " |\n"; // один рядок на один виклик
}

// Двійкова система: старші цифри - рекурсивно, остання - n % 2.
string binary(long long n, int level, int& depth, ostream& trace)
{
    depth = max(depth, level);                  // оновлюємо глибину
    const string digit = to_string(n % 2);      // остання двійкова цифра
    traceRow(trace, level, n, digit);           // виводимо рівень і число
    if (n < 2)                                  // базовий випадок: одна цифра
        return digit;
    return binary(n / 2, level + 1, depth, trace) + digit; // рекурсія + цифра
}

// Вісімкова система: старші цифри - рекурсивно, остання - n % 8.
string octal(long long n, int level, int& depth, ostream& trace)
{
    depth = max(depth, level);                  // оновлюємо глибину
    const string digit = to_string(n % 8);      // остання вісімкова цифра
    traceRow(trace, level, n, digit);           // виводимо рівень і число
    if (n < 8)                                  // базовий випадок: одна цифра
        return digit;
    return octal(n / 8, level + 1, depth, trace) + digit; // рекурсія + цифра
}

// Довільна основа N > 1; цифри 10..35 - A..Z, цифри >= 36 - [значення].
string inBase(long long n, long long base, int level, int& depth, ostream& trace)
{
    depth = max(depth, level);                  // оновлюємо глибину
    const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // алфавіт цифр
    const long long r = n % base;               // остання цифра (остача)
    const string digit = r < 36 ? string(1, digits[r])
                                : "[" + to_string(r) + "]"; // запис цифри
    traceRow(trace, level, n, digit);           // виводимо рівень і число
    if (n < base)                               // базовий випадок: одна цифра
        return digit;
    return inBase(n / base, base, level + 1, depth, trace) + digit; // рекурсія + цифра
}

#ifndef UNIT_TEST
int main()
{
    long long n, base;                          // число та основа N
    cout << "n N (n >= 1, N > 1): ";            // запрошення до введення
    if (!(cin >> n >> base) || n < 1 || base < 2) // перевірка введення
    {
        cerr << "Error: n >= 1, N > 1.\n";      // повідомлення про помилку
        return 1;                               // завершення з кодом помилки
    }

    const char* tline = "+-------+----------------------+--------+\n"; // межа трасування
    const char* thead = "| level |          n           | digit  |\n"; // шапка трасування
    int d2 = 0, d8 = 0, dN = 0;                 // глибини рекурсії

    cout << "Base 2 (recursion trace):\n" << tline << thead << tline;
    const string r2 = binary(n, 1, d2, cout);   // двійковий запис
    cout << tline;                              // нижня межа
    cout << "Base 8 (recursion trace):\n" << tline << thead << tline;
    const string r8 = octal(n, 1, d8, cout);    // вісімковий запис
    cout << tline;                              // нижня межа
    cout << "Base " << base << " (recursion trace):\n" << tline << thead << tline;
    const string rN = inBase(n, base, 1, dN, cout); // запис з основою N
    cout << tline;                              // нижня межа

    const char* line = "+--------+------------------------------------------+-------+\n";
    cout << "Results for n = " << n << '\n' << line; // підсумкова таблиця
    cout << "|  base  | representation                           | depth |\n" << line;
    cout << "| " << setw(6) << 2 << " | " << left << setw(40) << r2 << right
         << " | " << setw(5) << d2 << " |\n";   // рядок для основи 2
    cout << "| " << setw(6) << 8 << " | " << left << setw(40) << r8 << right
         << " | " << setw(5) << d8 << " |\n";   // рядок для основи 8
    cout << "| " << setw(6) << base << " | " << left << setw(40) << rN << right
         << " | " << setw(5) << dN << " |\n";   // рядок для основи N
    cout << line;                               // нижня межа таблиці
    return 0;                                   // успішне завершення
}
#endif
