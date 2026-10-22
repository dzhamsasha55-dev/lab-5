// Лабораторна робота 5.1, варіант 7. Джамалов О. О., РІ-11.
// Обчислити y = (f(1, t^2, s) + f(t, s^2, 1)) / (1 + f^2(1, t*s, 1)),
// де f(a, b, c) = sin^2(a*b*c) / (a^2 + b^2 + c^2).
#include <cmath>    // sin, isfinite
#include <iomanip>  // setw, setprecision, fixed
#include <iostream> // cin, cout, cerr
using namespace std;

// Допоміжна функція: f(a, b, c) = sin^2(a*b*c) / (a^2 + b^2 + c^2).
double f(double a, double b, double c)
{
    const double s = sin(a * b * c);        // синус добутку аргументів
    return s * s / (a * a + b * b + c * c); // квадрат синуса / сума квадратів
}

#ifndef UNIT_TEST
int main()
{
    double s, t;                        // вхідні дійсні числа s і t
    cout << "s t: ";                    // запрошення до введення
    if (!(cin >> s >> t) || !isfinite(s) || !isfinite(t)) // перевірка введення
    {
        cerr << "Error: enter two real numbers.\n"; // повідомлення про помилку
        return 1;                       // завершення з кодом помилки
    }

    const double p = f(1, t * t, s);    // перший доданок чисельника
    const double q = f(t, s * s, 1);    // другий доданок чисельника
    const double d = f(1, t * s, 1);    // значення f у знаменнику
    const double y = (p + q) / (1 + d * d); // значення виразу

    const char* line = "+----------------+--------------------+\n"; // межа таблиці
    cout << "Lab 5.1 / Variant 7\n" << line;                       // заголовок і верхня межа
    cout << "| Value          |             Result |\n" << line;  // шапка таблиці
    cout << fixed << setprecision(10);                             // формат чисел
    cout << "| s              | " << setw(18) << s << " |\n";      // рядок: s
    cout << "| t              | " << setw(18) << t << " |\n";      // рядок: t
    cout << "| f(1, t^2, s)   | " << setw(18) << p << " |\n";      // рядок: p
    cout << "| f(t, s^2, 1)   | " << setw(18) << q << " |\n";      // рядок: q
    cout << "| f(1, t*s, 1)   | " << setw(18) << d << " |\n";      // рядок: d
    if (isfinite(y))                                               // чи y скінченне?
        cout << "| y              | " << setw(18) << y << " |\n";  // рядок: y
    else
        cout << "| y              | " << setw(18) << "out of range" << " |\n"; // переповнення
    cout << line;                                                  // нижня межа таблиці
    return 0;                                                      // успішне завершення
}
#endif
