#include <iostream>
using namespace std;

int main() {
    int *a = new int;
    *a = 10;
    int b = 10;
    int c = 10;
    int *d = new int;
    *d = 10;
    cout << "A: " << a << endl;
    cout << "B: " << &b << endl;
    cout << "C: " << &c << endl;
    cout << "D: " << d << endl;
    if (&b > &c)    cout << "B > C\n";
    else	    cout << "C > B\n";
    if (a > d)    cout << "A > D\n";
    else          cout << "D > A\n";
    if (a > &b)   cout << "A > B\n";
    else    cout << "B > A\n";
    return 0;
 
}
