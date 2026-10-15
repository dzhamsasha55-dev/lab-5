#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
using namespace std;

// a_i = a_(i-1) * [-x^2 * (2i-1)/(2i+1)], i >= 1.
double nextTerm(double x, int i, double a)
{
    return -a * x * x * (2.0 * i - 1) / (2.0 * i + 1);
}

// Count includes a_0 = -x; pi/2 is not a series term.
double taylorSum(double x, double eps, int& count)
{
    double a = -x;
    double sum = a;
    count = 1;
    while (abs(a) >= eps)
    {
        if (count == 10000000)
            throw runtime_error("Too many terms; increase eps.");
        a = nextTerm(x, count, a);
        sum += a;
        ++count;
    }
    return acos(-1.0) / 2 + sum;
}

#ifndef UNIT_TEST
int main()
{
    double xp, xk, dx, eps;
    cout << "x_begin x_end dx eps: ";
    if (!(cin >> xp >> xk >> dx >> eps) ||
        !isfinite(xp) || !isfinite(xk) ||
        !isfinite(dx) || !isfinite(eps) ||
        xp < -1 || xk > 1 || xp > xk || dx <= 0 || eps <= 0)
        return 1;
    const double steps = (xk - xp) / dx;
    if (!isfinite(steps) || steps > 1000000)
    {
        cerr << "Too many rows; increase dx.\n";
        return 1;
    }
    const int rows = static_cast<int>(floor(steps + 1e-12));
    cout << "Lab 5.2 / Variant 7\n" << setw(12) << "x"
         << setw(16) << "arcctg(x)" << setw(16) << "sum"
         << setw(12) << "terms" << '\n';
    try
    {
        for (int i = 0; i <= rows; ++i)
        {
            const double x = min(xk, xp + i * dx);
            int count;
            const double sum = taylorSum(x, eps, count);
            const double exact = acos(-1.0) / 2 - atan(x);
            cout << fixed << setprecision(8) << setw(12) << x
                 << setw(16) << exact << setw(16) << sum
                 << setw(12) << count << '\n';
        }
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
#endif
