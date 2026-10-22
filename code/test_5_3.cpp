// Unit-тести функції k із завдання 5.3.
#include <algorithm>    // max
#include <cmath>        // pow, exp, sin, cos
#include <iomanip>      // setw, setprecision
#include <iostream>     // cout

#define UNIT_TEST       // вимикаємо main() у файлі програми
#include "lab_5_3.cpp"  // підключаємо функцію k

int main()
{
    // Незалежний еталон: явний многочлен, без рекурентної формули.
    const double xs[] = {-2, -1, -0.999999, -0.5, 0,
                         0.5, 0.999999, 1, 2};   // обидві гілки та межі
    int failed = 0;                              // лічильник невдалих тестів
    for (double x : xs)                          // перебір аргументів
    {
        double expected;                         // очікуване значення
        if (std::abs(x) >= 1)                    // перша гілка
            expected = (std::exp(x) + std::sin(x)) /
                       (1 + std::pow(std::cos(x), 2));
        else                                     // друга гілка
            expected = (1 + x + std::pow(x, 2) / 2 +
                        std::pow(x, 3) / 6 + std::pow(x, 4) / 24 +
                        std::pow(x, 5) / 120) / std::exp(x);

        const double actual = k(x);              // фактичне значення
        const bool ok = std::isfinite(actual) && // порівняння з допуском
            std::abs(actual - expected) <=
            1e-12 * std::max(1.0, std::abs(expected));
        std::cout << (ok ? "PASS" : "FAIL")
                  << " x=" << std::setw(10) << x
                  << " k(x)=" << std::setprecision(12)
                  << actual << '\n';             // результат тесту
        if (!ok)
            ++failed;                            // рахуємо помилку
    }
    std::cout << "Tests: 9, passed: " << 9 - failed
              << ", failed: " << failed << '\n'; // підсумок
    return failed == 0 ? 0 : 1;                  // код завершення для CTest
}
