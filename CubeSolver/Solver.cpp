//
// Created by kil4g on 18.05.2022.
//

#include "Solver.h"


void Solver::pifPaf(Cube &cube) {
    cube.R().U().invR().invU();
}
bool Solver::checkEdge(char& side1, char& side2, char& expect1, char& expect2) {
    return (side1 == expect1 && side2 == expect2) || (side2 == expect1 && side1 == expect2);
}
bool Solver::checkCorner(char& side1, char& side2, char& side3, char& expect1, char& expect2, char& expect3) {
    return (side1 == expect1 || side2 == expect1 || side3 == expect1) &&
           (side1 == expect2 || side2 == expect2 || side3 == expect2) &&
           (side1 == expect3 || side2 == expect3 || side3 == expect3);
}
bool Solver::solveX(Cube& cube) {
    char color = *(cube.down + 4);
    for (int i = 0; i < 4; i++) {

        char front_color = *(cube.front + 4);

        if (checkEdge(*(cube.back + 7), *(cube.down + 7), front_color, color)) {
            cube.B().B();
        } else if (checkEdge(*(cube.back + 3), *(cube.right + 5), front_color, color)) {
            cube.B().U().invB().invU();
        } else if (checkEdge(*(cube.back + 5), *(cube.left + 3), front_color, color)) {
            cube.invB().invU().B().U();
        }
        if (checkEdge(*(cube.back + 1), *(cube.up + 1), front_color, color)) {
            cube.U();
        } else if (checkEdge(*(cube.right + 7), *(cube.down + 5), front_color, color)) {
            cube.R().R();
        }
        if (checkEdge(*(cube.left + 7), *(cube.down + 3), front_color, color)) {
            cube.L().L();
        }
        if (checkEdge(*(cube.left + 1), *(cube.up + 3), front_color, color)) {
            cube.invU();
        }
        if (checkEdge(*(cube.right + 1), *(cube.up + 5), front_color, color)) {
            cube.U();
        }
        if (checkEdge(*(cube.front + 3), *(cube.left + 5), front_color, color)) {
            cube.F();
        }
        if (checkEdge(*(cube.front + 1), *(cube.up + 7), front_color, color)) {
            cube.F();
        }
        if (checkEdge(*(cube.front + 5), *(cube.right + 3), front_color, color)) {
            cube.F();
        }

        if (checkEdge(*(cube.front + 7), *(cube.down + 1), front_color, color)) {
            if (*(cube.front+7) != front_color) {
                cube.F().F().U().invF().L().invF().invL();
            }
            cube.rotateCubeLeft();
        } else {
            return false;
        }
    }
    return true;
}
bool Solver::solveBottomCorners(Cube& cube) {
    for (int j = 0; j < 4; j++) {
        char f_color = *(cube.front + 4);
        char d_color = *(cube.down + 4);
        char r_color = *(cube.right + 4);
        for (int i = 0; i < 4; i++) {
            cube.rotateCubeLeft();
            if (checkCorner(*(cube.front+8), *(cube.right+6), *(cube.down+2),
                            f_color, d_color, r_color)) {
                pifPaf(cube);
            }
        }
        for (int i = 0; i < 4; i++) {
            if (checkCorner(*(cube.front+2), *(cube.right+0), *(cube.up+8),
                            f_color, d_color, r_color)) {
                pifPaf(cube);
            }
            cube.U();
        }
        if (checkCorner(*(cube.front+8), *(cube.right+6), *(cube.down+2),
                        f_color, d_color, r_color)) {
            while (*(cube.front+8) != f_color) {
                pifPaf(cube);
                pifPaf(cube);
            }
        } else {
            return false;
        }
        cube.rotateCubeLeft();
    }
    return true;
}
bool Solver::solveMiddleEdges(Cube &cube) {
    for (int j = 0; j < 4; j++) {
        char f_color = *(cube.front+4);
        char r_color = *(cube.right+4);
        for (int i = 0; i < 4; i++) {
            cube.rotateCubeLeft();
            if (checkEdge(*(cube.front+5), *(cube.right+3),
                          f_color, r_color)) {
                cube.F().U().F().U().F().invU().invF().invU().invF();
            }
        }
        for (int i = 0; i < 4; i++) {
            if (checkEdge(*(cube.front+1), *(cube.up+7),
                          f_color, r_color)) {
                if (*(cube.front+1) == f_color) {
                    cube.F().U().F().U().F().invU().invF().invU().invF();
                } else {
                    cube.invU().invR().invU().invR().invU().invR().U().R().U().R();
                }
                break;
            }
            cube.U();
        }
        cube.rotateCubeRight();
    }
    return true;
}
bool Solver::solveTopX(Cube &cube) {
    char u_color = *(cube.up+4);
    for (int i = 0; i < 4; i++) {
        cube.F();
        for (int j = 0; j < 3; j++) {
            if (*(cube.right+3) == u_color) {
                break;
            }
            pifPaf(cube);
        }
        cube.invF();
        cube.invU();
    }
    return *(cube.up + 1) == u_color && *(cube.up + 3) == u_color && *(cube.up + 5) == u_color && *(cube.up + 7) == u_color;
}
bool Solver::solveTopEdges(Cube &cube) {
    char f, l, r, b;
    for (int i = 0; i < 4; i++) {
        f = *(cube.front + 4);
        l = *(cube.left + 4);
        r = *(cube.right + 4);
        b = *(cube.back + 4);
        for (int j = 0; j < 4; j++) {
            if (*(cube.front+1) == f) {
                break;
            }
            cube.U();
        }
        if (*(cube.back+1) == b) {
            cube.R().U().invR().U().R().U().U().invR();
            cube.invU();
            cube.R().U().invR().U().R().U().U().invR();
            cube.U().U();
            return true;
        }
        if (*(cube.left+1) != l && *(cube.right+1) != r) {
            cube.R().U().invR().U().R().U().U().invR();
            if (*(cube.left+1) != l && *(cube.right+1) != r) {
                cube.R().U().invR().U().R().U().U().invR();
            }
            return true;
        }
        cube.rotateCubeLeft();
    }
    return false;

}

bool Solver::solveTopCorners(Cube &cube) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (checkCorner(*(cube.up+8), *(cube.front+2), *(cube.right+0),
                        *(cube.up+7), *(cube.front+1), *(cube.right+1))) {
            count++;
        }
        cube.U();
    }
    if (count == 0) {
        cube.U().R().invU().invL().U().invR().invU().L();
        count++;
    }
    if (count == 1) {
        for (int i = 0; i < 4; i++) {
            if (checkCorner(*(cube.up+8), *(cube.front+2), *(cube.right+0),
                            *(cube.up+7), *(cube.front+1), *(cube.right+1))) {
                break;
            }
            cube.U();
        }
        cube.U().R().invU().invL().U().invR().invU().L();
        cube.U();
        if (!checkCorner(*(cube.up+8), *(cube.front+2), *(cube.right+0),
                         *(cube.up+7), *(cube.front+1), *(cube.right+1))) {
            cube.R().invU().invL().U().invR().invU().L();
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (*(cube.front + 2) == *(cube.front + 1)) {
                break;
            }
            cube.D().F().invD().invF();
            cube.D().F().invD().invF();
        }
        cube.U();
    }
    return true;
}