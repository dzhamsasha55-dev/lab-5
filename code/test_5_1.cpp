// Unit-тести функції f із завдання 5.1.
#define UNIT_TEST       // вимикаємо main() у файлі програми
#include "lab_5_1.cpp"  // підключаємо функцію f

int main()
{
    const double pi = acos(-1.0);          // число pi
    const double data[][4] = {             // a, b, c, очікуване значення
        {0, 0, 1, 0}, {1, 0, 2, 0},
        {1, 1, 1, 0.236024472757856},
        {-1, 1, 1, 0.236024472757856},
        {pi / 2, 1, 1, 1 / (pi * pi / 4 + 2)}
    };
    int failed = 0;                        // лічильник невдалих тестів
    for (const auto& v : data)             // перебір тестових наборів
    {
        const double actual = f(v[0], v[1], v[2]);  // фактичне значення
        const bool ok = abs(actual - v[3]) < 1e-12; // порівняння з еталоном
        cout << (ok ? "PASS" : "FAIL") << " f("
             << v[0] << ',' << v[1] << ',' << v[2] << ")\n"; // результат тесту
        if (!ok) ++failed;                 // рахуємо помилку
    }
    cout << "5.1: " << 5 - failed << "/5 passed\n"; // підсумок
    return failed ? 1 : 0;                 // код завершення для CTest
}
