//
// Created by kil4g on 18.05.2022.
//

#include "Cube.h"

#ifndef LAB4_SOLVER_H
#define LAB4_SOLVER_H

class Solver {
public:
    static bool solveX(Cube& cube);
    static bool solveBottomCorners(Cube& cube);
    static bool solveMiddleEdges(Cube &cube);
    static bool solveTopX(Cube &cube);
    static bool solveTopEdges(Cube &cube);
    static bool solveTopCorners(Cube &cube);
    static void pifPaf(Cube &cube);
private:
    static bool checkEdge(char& side1, char& side2, char& expect1, char& expect2);
    static bool checkCorner(char &side1, char &side2, char &side3, char &expect1, char &expect2, char &expect3);
};
#endif //LAB4_SOLVER_H
