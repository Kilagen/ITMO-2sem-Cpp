#include <iostream>
#include "Poly.h"

using namespace std;

void sumSubTest(const Poly& p1, const Poly& p2) {
    cout << "Sum and Sub test" << endl;
    cout << "p1 + p2 = " << p1 + p2 << endl;
    cout << "p1 - p2 = " << p1 - p2 << endl;
    cout << "p1 + p1 = " << p1 + p1 << endl;
}

void mulTest(const Poly& p1, const Poly& p2, long long val) {
    cout << "Mul test" << endl;
    cout << "p1 * p2 = " << p1 * p2 << endl;
    cout << "p2 * p1 = " << p2 * p1 << endl;
    cout << "p1 * p1 = " << p1 * p1 << endl;
    cout << "p1 * p1 * p1 = " << p1 * p1 * p1 << endl;
    cout << "p1 * val = " << p1 * val << endl;
    cout << "p2 * val * p2 = " << p2 * val * p2 << endl;
}

void divTest(const Poly& p, long long val) {
    cout << "Division test" << endl;
    cout << "p / val = " << p / val << endl;
    cout << "p / val^2 = " << p / val / val << endl;
}


int main() {
    Poly p1({{0, 1}, {1, 1}});
    Poly p2({{1, 1}, {2, 2}});
    Poly p({{1, 123213}, {4, 232322}});
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    sumSubTest(p1, p2);
    mulTest(p1, p2, 15);
    divTest(p, 12);

    return 0;
}
