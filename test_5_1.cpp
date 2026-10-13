#define UNIT_TEST
#include "lab_5_1.cpp"

int main()
{
    const double pi = acos(-1.0);
    const double data[][4] = {
        {0, 0, 1, 0}, {1, 0, 2, 0},
        {1, 1, 1, 0.236024472757856},
        {-1, 1, 1, 0.236024472757856},
        {pi / 2, 1, 1, 1 / (pi * pi / 4 + 2)}
    };
    int failed = 0;
    for (const auto& v : data)
    {
        const double actual = f(v[0], v[1], v[2]);
        const bool ok = abs(actual - v[3]) < 1e-12;
        cout << (ok ? "PASS" : "FAIL") << " f("
             << v[0] << ',' << v[1] << ',' << v[2] << ")\n";
        if (!ok) ++failed;
    }
    cout << "5.1: " << 5 - failed << "/5 passed\n";
    return failed ? 1 : 0;
}
