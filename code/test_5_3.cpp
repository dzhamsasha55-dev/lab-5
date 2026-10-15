#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

#define UNIT_TEST
#include "lab_5_3.cpp"

int main()
{
    // Independent reference: explicit polynomial, no recurrence.
    const double xs[] = {-2, -1, -0.999999, -0.5, 0,
                         0.5, 0.999999, 1, 2};
    int failed = 0;
    for (double x : xs)
    {
        double expected;
        if (std::abs(x) >= 1)
            expected = (std::exp(x) + std::sin(x)) /
                       (1 + std::pow(std::cos(x), 2));
        else
            expected = (1 + x + std::pow(x, 2) / 2 +
                        std::pow(x, 3) / 6 + std::pow(x, 4) / 24 +
                        std::pow(x, 5) / 120) / std::exp(x);

        const double actual = k(x);
        const bool ok = std::isfinite(actual) &&
            std::abs(actual - expected) <=
            1e-12 * std::max(1.0, std::abs(expected));
        std::cout << (ok ? "PASS" : "FAIL")
                  << " x=" << std::setw(10) << x
                  << " k(x)=" << std::setprecision(12)
                  << actual << '\n';
        if (!ok)
            ++failed;
    }
    std::cout << "Tests: 9, passed: " << 9 - failed
              << ", failed: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
