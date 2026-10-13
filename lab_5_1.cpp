#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

// f(a,b,c) = sin^2(a*b*c) / (a^2+b^2+c^2).
double f(double a, double b, double c)
{
    const double s = sin(a * b * c);
    return s * s / (a * a + b * b + c * c);
}

#ifndef UNIT_TEST
int main()
{
    double s, t;
    cout << "s t: ";
    if (!(cin >> s >> t) || !isfinite(s) || !isfinite(t))
        return 1;
    const double d = f(1, t * s, 1);
    const double y = (f(1, t * t, s) + f(t, s * s, 1))
                     / (1 + d * d);
    if (!isfinite(y))
    {
        cerr << "Numbers are too large.\n";
        return 1;
    }
    cout << fixed << setprecision(10) << "y = " << y << '\n';
    return 0;
}
#endif
