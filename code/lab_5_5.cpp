#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string binary(long long n, int level, int& depth, ostream& trace)
{
    depth = max(depth, level);
    trace << "level=" << level << " n=" << n << '\n';
    if (n < 2)
        return to_string(n);
    return binary(n / 2, level + 1, depth, trace)
           + to_string(n % 2);
}

string octal(long long n, int level, int& depth, ostream& trace)
{
    depth = max(depth, level);
    trace << "level=" << level << " n=" << n << '\n';
    if (n < 8)
        return to_string(n);
    return octal(n / 8, level + 1, depth, trace)
           + to_string(n % 8);
}

// Digits >= 36 use [value], e.g. 79 in base 40 is 1[39].
string inBase(long long n, long long base, int level,
              int& depth, ostream& trace)
{
    depth = max(depth, level);
    trace << "level=" << level << " n=" << n << '\n';
    const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const long long r = n % base;
    const string digit = r < 36 ? string(1, digits[r])
                               : "[" + to_string(r) + "]";
    if (n < base)
        return digit;
    return inBase(n / base, base, level + 1, depth, trace)
           + digit;
}

#ifndef UNIT_TEST
int main()
{
    long long n, base;
    cout << "Natural number, base (>1): ";
    if (!(cin >> n >> base) || n < 1 || base < 2)
        return 1;
    int depth = 0;
    cout << "Binary:\n";
    string result = binary(n, 1, depth, cout);
    cout << "result=" << result << " depth=" << depth << '\n';
    depth = 0;
    cout << "Octal:\n";
    result = octal(n, 1, depth, cout);
    cout << "result=" << result << " depth=" << depth << '\n';
    depth = 0;
    cout << "Base " << base << ":\n";
    result = inBase(n, base, 1, depth, cout);
    cout << "result=" << result << " depth=" << depth << '\n';
    return 0;
}
#endif
