// Лабораторна робота 5.3, варіант 7. Джамалов О. О., РІ-11.
// F(z) = k(z^2 + 1) - k(z^2 - 1) + 2k(z) на [z_begin, z_end] з n відрізками.
#include <cmath>    // abs, exp, sin, cos, isfinite
#include <iomanip>  // setw, setprecision, fixed
#include <iostream> // cin, cout, cerr
using namespace std;

double k(double x); // оголошення допоміжної функції

#ifndef UNIT_TEST
int main()
{
    double zp, zk;                          // межі інтервалу
    int n;                                  // кількість відрізків розбиття
    cout << "z_begin z_end n: ";            // запрошення до введення
    if (!(cin >> zp >> zk >> n) || !isfinite(zp) || !isfinite(zk) ||
        !isfinite(zk - zp) || zp > zk || n <= 0) // перевірка введення
    {
        cerr << "Error: z_begin <= z_end, n > 0.\n"; // повідомлення про помилку
        return 1;                           // завершення з кодом помилки
    }

    const double dz = (zk - zp) / n;        // крок таблиці
    const char* line = "+-----------------+----------------------+\n"; // межа таблиці
    cout << "Lab 5.3 / Variant 7\n"         // заголовок
         << "F(z) = k(z*z+1) - k(z*z-1) + 2*k(z)\n" << line;
    cout << "|        z        |         F(z)         |\n" << line; // шапка таблиці
    cout << fixed << setprecision(8);       // формат чисел
    for (int i = 0; i <= n; ++i)            // n відрізків дають n + 1 точку
    {
        const double z = zp + i * dz;       // поточне значення z
        const double y = k(z * z + 1) - k(z * z - 1) + 2 * k(z); // значення F(z)
        if (isfinite(y))                    // чи результат скінченний?
            cout << "| " << setw(15) << z << " | " << setw(20) << y << " |\n";
        else                                // переповнення типу double
            cout << "| " << setw(15) << z << " | " << setw(20) << "out of range" << " |\n";
    }
    cout << line;                           // нижня межа таблиці
    return 0;                               // успішне завершення
}
#endif

// Допоміжна функція k(x):
// (e^x + sin x) / (cos^2 x + 1), якщо |x| >= 1;
// (1 / e^x) * sum_{i=0..5} x^i / i!, якщо |x| < 1.
double k(double x)
{
    if (abs(x) >= 1)                        // перша гілка
        return (exp(x) + sin(x)) / (cos(x) * cos(x) + 1);

    double a = 1;                           // a_0 = x^0 / 0! = 1
    double sum = a;                         // сума починається з a_0
    for (int i = 1; i <= 5; ++i)            // доданки a_1 ... a_5
    {
        a *= x / i;                         // a_i = a_(i-1) * x / i
        sum += a;                           // додаємо доданок до суми
    }
    return sum / exp(x);                    // ділимо суму на e^x
}
