// Unit-тести рекурсивних функцій переведення із завдання 5.5.
#define UNIT_TEST       // вимикаємо main() у файлі програми
#include "lab_5_5.cpp"  // підключаємо функції
#include <sstream>      // ostringstream для трасування

int main()
{
    struct Case { long long n, base; string result; int depth; }; // тестовий набір
    const Case cases[] = {{1, 2, "1", 1}, {13, 2, "1101", 4},
        {64, 8, "100", 3}, {255, 16, "FF", 2},
        {79, 40, "1[39]", 2}, {7, 100, "7", 1}};
    int failed = 0;                                   // лічильник невдалих тестів
    for (const auto& v : cases)                       // перебір наборів
    {
        int depth = 0;                                // глибина рекурсії
        ostringstream trace;                          // трасування в пам'ять
        const string actual = inBase(v.n, v.base, 1, depth, trace); // результат
        bool ok = actual == v.result && depth == v.depth;    // перевірка
        const string log = trace.str();               // текст трасування
        ok = ok && count(log.begin(), log.end(), '\n') == depth; // рядок на виклик
        if (v.base == 2)                              // окремо функція binary
        {
            depth = 0;
            ok = ok && binary(v.n, 1, depth, trace) == v.result
                    && depth == v.depth;
        }
        if (v.base == 8)                              // окремо функція octal
        {
            depth = 0;
            ok = ok && octal(v.n, 1, depth, trace) == v.result
                    && depth == v.depth;
        }
        cout << (ok ? "PASS" : "FAIL") << " n=" << v.n
             << " base=" << v.base << '\n';           // результат тесту
        if (!ok) ++failed;                            // рахуємо помилку
    }
    cout << "5.5: " << 6 - failed << "/6 passed\n";   // підсумок
    return failed ? 1 : 0;                            // код завершення для CTest
}
