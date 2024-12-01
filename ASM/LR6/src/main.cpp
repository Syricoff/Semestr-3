// #include <conio.h>
#include <iostream>
#include <limits.h>

using namespace std;
inline int test(long int a)
{
    return ((a >> 15) + 1) & ~1;
}

int primC(int a, const int b, const int c, const int d)
{
    double z = (2.0 * a + 1.0 * b * c) / (d - a);
    if (z > SHRT_MIN && z < SHRT_MAX)
    {
        return z;
    }
    else
    {
        cout << "\n !!!!!Limits of int value !!!!!!!\n x =" << z << endl;
        return SHRT_MIN; //-32768
    }
}
extern "C"
{
    void prim(void);
}
int X, a;
// внешняя функция, которая будет написана на
//  Ассемблере
// глобальные переменные
int main(void)
{
    int ch;
    const int b = -333;
    const int c = 1000;
    const int d = -10;
    long int a1;
    do
    {
        X = 0;
        cout << "\n x = (2 * a + b * c) / (d - a); int x, a, b = -333, c = 1000, d = -10;" << endl;
        do
        {
            cout << "\n Enter a[-32768…32767], a !=" << d << "== == >";
            cin >> a1;
        } while (test(a1) || d - a1 == 0 || test(d - a1));
        a = a1;
        X = primC(a, b, c, d);
        if (X != SHRT_MIN)
        {
            cout << "Result(C++) x = " << X << endl;
            X = 0;
            prim();
            cout << " Result(ASM) x = " << X << endl;
        }
        cout << "\n\nExit ? – (y / n)\n";
        cin >> ch;
    } while (!(ch == 0));
}