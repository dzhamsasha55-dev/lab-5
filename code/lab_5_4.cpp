// Лабораторна робота 5.4, варіант 7. Джамалов О. О., РІ-11.
// S = sum_{k=1..N} 1 / (2k + 1)^2 п'ятьма способами.
#include <iomanip>  // setw, setprecision, fixed
#include <iostream> // cin, cout, cerr
using namespace std;

// Доданок суми a(k) = 1 / (2k + 1)^2.
double term(int k)
{
    const double d = 2.0 * k + 1; // знаменник без квадрата
    return 1 / (d * d);           // значення доданка
}

// 5.4.1: обчислення на рекурсивному спуску, параметр спадає (k = N ... 1).
double downDown(int k, double sum)
{
    if (k == 0)                     // базовий випадок: усі доданки враховано
        return sum;                 // повертаємо накопичену суму
    sum += term(k);                 // додаємо доданок до виклику
    return downDown(k - 1, sum);    // рекурсивний виклик з меншим k
}

// 5.4.2: обчислення на рекурсивному спуску, параметр зростає (k = 1 ... N).
double downUp(int k, int n, double sum)
{
    if (k > n)                      // базовий випадок: k вийшло за N
        return sum;                 // повертаємо накопичену суму
    sum += term(k);                 // додаємо доданок до виклику
    return downUp(k + 1, n, sum);   // рекурсивний виклик з більшим k
}

// 5.4.3: обчислення на рекурсивному підйомі, параметр спадає (k = N ... 1).
double upDown(int k)
{
    if (k == 0)                     // базовий випадок: порожня сума
        return 0;                   // сума нуля доданків
    const double rest = upDown(k - 1); // спочатку рекурсивний виклик
    return rest + term(k);          // додавання після повернення
}

// 5.4.4: обчислення на рекурсивному підйомі, параметр зростає (k = 1 ... N).
double upUp(int k, int n)
{
    if (k > n)                      // базовий випадок: k вийшло за N
        return 0;                   // сума нуля доданків
    const double rest = upUp(k + 1, n); // спочатку рекурсивний виклик
    return rest + term(k);          // додавання після повернення
}

// 5.4.5: ітераційний спосіб для контролю.
double iterative(int n)
{
    double sum = 0;                 // початкове значення суми
    for (int k = 1; k <= n; ++k)    // перебір k = 1 ... N
        sum += term(k);             // додаємо доданок
    return sum;                     // повертаємо суму
}

#ifndef UNIT_TEST
int main()
{
    int n;                                   // кількість доданків N
    cout << "N (1..1000): ";                 // запрошення до введення
    if (!(cin >> n) || n < 1 || n > 1000)    // перевірка введення
    {
        cerr << "Error: 1 <= N <= 1000.\n";  // повідомлення про помилку
        return 1;                            // завершення з кодом помилки
    }

    const double s1 = downDown(n, 0);        // 5.4.1
    const double s2 = downUp(1, n, 0);       // 5.4.2
    const double s3 = upDown(n);             // 5.4.3
    const double s4 = upUp(1, n);            // 5.4.4
    const double s5 = iterative(n);          // 5.4.5
    const char* line = "+-------+------------------------------+-----------------+\n";
    cout << "Lab 5.4 / Variant 7, N = " << n << '\n' << line; // заголовок і верхня межа
    cout << "|   #   | Method                       |       Sum       |\n" << line;
    cout << fixed << setprecision(12);       // формат чисел
    cout << "| 5.4.1 | descent, k decreases         | " << setw(15) << s1 << " |\n";
    cout << "| 5.4.2 | descent, k increases         | " << setw(15) << s2 << " |\n";
    cout << "| 5.4.3 | ascent, k decreases          | " << setw(15) << s3 << " |\n";
    cout << "| 5.4.4 | ascent, k increases          | " << setw(15) << s4 << " |\n";
    cout << "| 5.4.5 | iterative (check)            | " << setw(15) << s5 << " |\n";
    cout << line;                            // нижня межа таблиці
    return 0;                                // успішне завершення
}
#endif
