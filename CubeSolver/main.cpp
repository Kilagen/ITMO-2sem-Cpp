#include <iostream>
#include "Cube.h"

Cube test1() {
    return Cube("Tests/solved.txt").U().U().U().U();
}
Cube test2() {
    return Cube("Tests/solved.txt").invD().invU().invF().D().invD().R().L().R().L().D().invF().L().invU().R().invR(
            ).invU().invF().invL().D().invD().R().invF().invR().invL().invD().invF().invB().invL().D().invF();
}
Cube test3() {
    return Cube("Tests/solved.txt").invR().invL().U().invF().invL().invF().invF().invU().invL().invR().invF().U(
            ).B().invU().invF().F().L().F().invB().invU().invB().B().F().R().B().L().F().invU().invU().invR();
}
Cube test4() {
    return Cube("Tests/solved.txt").B().invB().B().R().B().F().invR().invD().invU().invD().invU().F().D().R().B(
            ).U().invF().invD().invB().F().invR().invF().R().invF().invU().invD().U().invD().L().L();
}
Cube test5() {
    return Cube("Tests/solved.txt").invD().B().F().D().R().invD().B().invF().invF().invF().R().invR().U().L().U(
            ).invL().invF().F().U().F().invD().D().invL().B().B().B().F().invL().invF().F();
}
Cube test6() {
    return Cube("Tests/solved.txt").D().F().L().U().B().invF().F().invL().L().D().invD().invD().invL().invU().U(
            ).invB().R().invD().D().D().F().B().invL().L().U().invB().L().invU().invU().invF();
}
Cube test7() {
    return Cube("Tests/solved.txt").F().L().invL().invF().U().U().invR().invD().L().F().invL().D().invL().invU(
            ).invL().D().L().invF().invL().U().invL().D().invB().invU().invD().F().invF().R().invB().D();
}



int main() {
    // Cube c = test1();
    // c.control();
    // c.write("Tests/my_cube.txt");
    for (Cube cube: {test1(), test2(), test3(), test4(), test5(), test6(), test7()}) {
        std::cout << std::endl << "Test:" << std::endl;
        std::cout << cube << std::endl;
        Solver::solve(cube);
        std::cout << "Solved:" << std::endl;
        std::cout << cube << std::endl;
        std::cout << "Moves: " << cube.getMoves() << std::endl;
    }
    return 0;
}
