#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

double k(double x);

#ifndef UNIT_TEST
int main()
{
    double zp, zk;
    int n;
    cout << "z_begin z_end n: ";
    if (!(cin >> zp >> zk >> n) || !isfinite(zp) ||
        !isfinite(zk) || zp > zk || n <= 0)
    {
        cerr << "Invalid input: z_begin <= z_end, n > 0.\n";
        return 1;
    }

    const double dz = (zk - zp) / n;
    if (!isfinite(dz))
    {
        cerr << "Interval is too large.\n";
        return 1;
    }

    cout << "Lab 5.3 / Variant 7\n"
         << "F(z) = k(z*z+1) - k(z*z-1) + 2*k(z)\n"
         << setw(16) << "z" << setw(22) << "F(z)" << '\n';
    cout << fixed << setprecision(8);

    // n intervals have n + 1 nodes, including both endpoints.
    for (int i = 0; ; ++i)
    {
        const double z = (i == n) ? zk : zp + i * dz;
        const double y = k(z * z + 1) - k(z * z - 1) + 2 * k(z);
        cout << setw(16) << z;
        if (isfinite(y))
            cout << setw(22) << y << '\n';
        else
            cout << setw(22) << "out of range" << '\n';
        if (i == n)
            break;
    }
    return 0;
}
#endif

// Auxiliary function from the assignment.
double k(double x)
{
    if (abs(x) >= 1)
        return (exp(x) + sin(x)) / (cos(x) * cos(x) + 1);

    double a = 1; // a_0 = x^0 / 0! = 1
    double sum = a;
    for (int i = 1; i <= 5; ++i)
    {
        a *= x / i; // a_i = a_(i-1) * x / i
        sum += a;
    }
    return sum / exp(x);
}
