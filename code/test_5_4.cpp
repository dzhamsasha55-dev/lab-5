#define UNIT_TEST
#include "lab_5_4.cpp"
#include <cmath>

int main()
{
    int failed = 0;
    for (int n : {1, 2, 5, 20, 100, 1000})
    {
        long double expected = 0;
        for (int j = 1; j <= n; ++j)
            expected += 1.0L / ((2.0L * j + 1) * (2.0L * j + 1));
        const double results[] = {upDown(n), upUp(1, n),
            downDown(n, 0), downUp(1, n, 0), iterative(n)};
        bool ok = true;
        for (double value : results)
            ok = ok && std::abs(value - expected) < 1e-12;
        cout << (ok ? "PASS" : "FAIL") << " N=" << n
             << " (all five methods)\n";
        if (!ok) ++failed;
    }
    cout << "5.4: " << 6 - failed << "/6 passed\n";
    return failed ? 1 : 0;
}
