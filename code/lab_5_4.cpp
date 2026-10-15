#include <iomanip>
#include <iostream>
using namespace std;

double term(int k)
{
    const double d = 2.0 * k + 1;
    return 1 / (d * d);
}

// 5.4.1: recursive ascent, decreasing parameter.
double upDown(int k)
{
    if (k == 0)
        return 0;
    const double rest = upDown(k - 1);
    return rest + term(k);
}

// 5.4.2: recursive ascent, increasing parameter.
double upUp(int k, int n)
{
    if (k > n)
        return 0;
    const double rest = upUp(k + 1, n);
    return rest + term(k);
}

// 5.4.3: recursive descent, decreasing parameter.
double downDown(int k, double sum)
{
    if (k == 0)
        return sum;
    sum += term(k);
    return downDown(k - 1, sum);
}

// 5.4.4: recursive descent, increasing parameter.
double downUp(int k, int n, double sum)
{
    if (k > n)
        return sum;
    sum += term(k);
    return downUp(k + 1, n, sum);
}

// Iterative reference.
double iterative(int n)
{
    double sum = 0;
    for (int k = 1; k <= n; ++k)
        sum += term(k);
    return sum;
}

#ifndef UNIT_TEST
int main()
{
    int n;
    cout << "N (1..1000): ";
    if (!(cin >> n) || n < 1 || n > 1000)
        return 1;
    cout << fixed << setprecision(12)
         << "5.4.1 = " << upDown(n) << '\n'
         << "5.4.2 = " << upUp(1, n) << '\n'
         << "5.4.3 = " << downDown(n, 0) << '\n'
         << "5.4.4 = " << downUp(1, n, 0) << '\n'
         << "iter  = " << iterative(n) << '\n';
    return 0;
}
#endif
