// Unit-тести п'яти способів обчислення суми із завдання 5.4.
#define UNIT_TEST       // вимикаємо main() у файлі програми
#include "lab_5_4.cpp"  // підключаємо функції
#include <cmath>        // abs

int main()
{
    int failed = 0;                                    // лічильник невдалих тестів
    for (int n : {1, 2, 5, 20, 100, 1000})             // тестові значення N
    {
        long double expected = 0;                      // еталон з long double
        for (int j = 1; j <= n; ++j)
            expected += 1.0L / ((2.0L * j + 1) * (2.0L * j + 1));
        const double results[] = {downDown(n, 0), downUp(1, n, 0),
            upDown(n), upUp(1, n), iterative(n)};      // усі п'ять способів
        bool ok = true;                                // ознака успіху
        for (double value : results)                   // порівняння кожного
            ok = ok && std::abs(value - expected) < 1e-12;
        cout << (ok ? "PASS" : "FAIL") << " N=" << n
             << " (all five methods)\n";               // результат тесту
        if (!ok) ++failed;                             // рахуємо помилку
    }
    cout << "5.4: " << 6 - failed << "/6 passed\n";    // підсумок
    return failed ? 1 : 0;                             // код завершення для CTest
}
