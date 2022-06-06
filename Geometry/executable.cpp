#include "library.h"

#include <iostream>
using namespace std;

int main() {
    Point a(0, 0);
    Point b(0.1, 0);
    Point c(0.1, 0.1);
    Point d(0, 0.1);
    Line line1({a, b, c, d});
    LockedLine line({a, b, c, d});
    cout << line1.perimeter() << endl;
    cout << line.perimeter() << endl;
    Polygon abe(LockedLine({a, b, c, d}));
    Polygon abc(line);
    cout << abc.perimeter() << endl;
    cout << abe.area() << endl;
}