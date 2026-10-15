#define UNIT_TEST
#include "lab_5_5.cpp"
#include <sstream>

int main()
{
    struct Case { long long n, base; string result; int depth; };
    const Case cases[] = {{1, 2, "1", 1}, {13, 2, "1101", 4},
        {64, 8, "100", 3}, {255, 16, "FF", 2},
        {79, 40, "1[39]", 2}, {7, 100, "7", 1}};
    int failed = 0;
    for (const auto& v : cases)
    {
        int depth = 0;
        ostringstream trace;
        const string actual = inBase(v.n, v.base, 1, depth, trace);
        bool ok = actual == v.result && depth == v.depth;
        const string log = trace.str();
        ok = ok && count(log.begin(), log.end(), '\n') == depth;
        if (v.base == 2)
        {
            depth = 0;
            ok = ok && binary(v.n, 1, depth, trace) == v.result
                    && depth == v.depth;
        }
        if (v.base == 8)
        {
            depth = 0;
            ok = ok && octal(v.n, 1, depth, trace) == v.result
                    && depth == v.depth;
        }
        cout << (ok ? "PASS" : "FAIL") << " n=" << v.n
             << " base=" << v.base << '\n';
        if (!ok) ++failed;
    }
    cout << "5.5: " << 6 - failed << "/6 passed\n";
    return failed ? 1 : 0;
}
