#define UNIT_TEST
#include "lab_5_2.cpp"

int main()
{
    int failed = 0;
    const double xs[] = {-1, -0.5, 0, 0.5, 1};
    for (double x : xs)
    {
        const double eps = abs(x) == 1 ? 1e-5 : 1e-10;
        int count;
        const double actual = taylorSum(x, eps, count);
        const double expected = acos(-1.0) / 2 - atan(x);
        const bool ok = abs(actual - expected) < eps + 1e-14
                        && count >= 1 && (x != 0 || count == 1);
        cout << (ok ? "PASS" : "FAIL") << " x=" << x
             << " terms=" << count << '\n';
        if (!ok) ++failed;
    }
    const bool termOk = abs(nextTerm(0.5, 1, -0.5)
                           - 1.0 / 24) < 1e-15;
    cout << (termOk ? "PASS" : "FAIL") << " nextTerm\n";
    if (!termOk) ++failed;
    cout << "5.2: " << 6 - failed << "/6 passed\n";
    return failed ? 1 : 0;
}
