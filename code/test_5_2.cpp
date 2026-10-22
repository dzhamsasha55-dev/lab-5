// Unit-тести функцій taylorSum і nextTerm із завдання 5.2.
#define UNIT_TEST       // вимикаємо main() у файлі програми
#include "lab_5_2.cpp"  // підключаємо функції

int main()
{
    int failed = 0;                                  // лічильник невдалих тестів
    const double xs[] = {-1, -0.5, 0, 0.5, 1};       // тестові аргументи
    for (double x : xs)                              // перебір аргументів
    {
        const double eps = abs(x) == 1 ? 1e-5 : 1e-10; // точність для x
        int count;                                   // кількість доданків
        const double actual = taylorSum(x, eps, count);       // сума ряду
        const double expected = acos(-1.0) / 2 - atan(x);     // еталон arcctg(x)
        const bool ok = abs(actual - expected) < eps + 1e-14  // перевірка точності
                        && count >= 1 && (x != 0 || count == 1);
        cout << (ok ? "PASS" : "FAIL") << " x=" << x
             << " terms=" << count << '\n';          // результат тесту
        if (!ok) ++failed;                           // рахуємо помилку
    }
    const bool termOk = abs(nextTerm(0.5, 1, -0.5)   // a_1 для x = 0.5
                           - 1.0 / 24) < 1e-15;      // має дорівнювати 1/24
    cout << (termOk ? "PASS" : "FAIL") << " nextTerm\n"; // результат тесту
    if (!termOk) ++failed;                           // рахуємо помилку
    cout << "5.2: " << 6 - failed << "/6 passed\n";  // підсумок
    return failed ? 1 : 0;                           // код завершення для CTest
}
