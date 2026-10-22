// Лабораторна робота 5.2, варіант 7. Джамалов О. О., РІ-11.
// arcctg(x) = pi/2 + sum_{n>=0} (-1)^(n+1) x^(2n+1) / (2n+1),  |x| <= 1.
#include <algorithm> // min
#include <cmath>     // abs, acos, atan, floor, isfinite
#include <iomanip>   // setw, setprecision, fixed
#include <iostream>  // cin, cout, cerr
using namespace std;

const int MAX_TERMS = 10000000;  // захист від нескінченного циклу
const double MAX_ROWS = 1000000; // найбільша кількість рядків таблиці

// Доданок за рекурентною формулою:
// a_i = a_(i-1) * (-x^2 * (2i-1) / (2i+1)), i >= 1.
double nextTerm(double x, int i, double a)
{
    return -a * x * x * (2.0 * i - 1) / (2.0 * i + 1); // новий доданок
}

// Сума ряду; count - кількість доданків (разом з a_0 = -x).
double taylorSum(double x, double eps, int& count)
{
    double a = -x;                           // перший доданок a_0
    double sum = a;                          // сума починається з a_0
    count = 1;                               // враховано один доданок
    while (abs(a) >= eps && count < MAX_TERMS) // поки доданок не менший за eps
    {
        a = nextTerm(x, count, a);           // наступний доданок
        sum += a;                            // додаємо його до суми
        ++count;                             // збільшуємо лічильник
    }
    return acos(-1.0) / 2 + sum;             // pi/2 + сума ряду
}

#ifndef UNIT_TEST
int main()
{
    double xp, xk, dx, eps;                  // межі, крок і точність
    cout << "x_begin x_end dx eps: ";        // запрошення до введення
    if (!(cin >> xp >> xk >> dx >> eps) ||   // перевірка введення
        !isfinite(xp) || !isfinite(xk) || !isfinite(dx) || !isfinite(eps) ||
        xp < -1 || xk > 1 || xp > xk || dx <= 0 || eps <= 0 ||
        (xk - xp) / dx > MAX_ROWS)
    {
        cerr << "Error: -1 <= x_begin <= x_end <= 1, dx > 0, eps > 0.\n"; // помилка
        return 1;                            // завершення з кодом помилки
    }

    const int rows = static_cast<int>(floor((xk - xp) / dx + 1e-12)); // номер останнього рядка
    const char* line =                       // межа таблиці
        "+-------------+-----------------+-----------------+----------+\n";
    cout << "Lab 5.2 / Variant 7\n" << line; // заголовок і верхня межа
    cout << "|      x      |    arcctg(x)    |       sum       |  terms   |\n"
         << line;                            // шапка таблиці
    cout << fixed << setprecision(8);        // формат чисел
    for (int i = 0; i <= rows; ++i)          // перебір точок інтервалу
    {
        const double x = min(xk, xp + i * dx);        // поточний аргумент
        int count;                                    // кількість доданків
        const double sum = taylorSum(x, eps, count);  // сума ряду
        const double exact = acos(-1.0) / 2 - atan(x); // точне значення
        cout << "| " << setw(11) << x << " | " << setw(15) << exact
             << " | " << setw(15) << sum << " | " << setw(8) << count
             << " |\n";                               // рядок таблиці
    }
    cout << line;                            // нижня межа таблиці
    return 0;                                // успішне завершення
}
#endif
