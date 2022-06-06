//
// Created by kil4g on 14.05.2022.
//

#include <fstream>
#include <iostream>
#include "Cube.h"

Cube::Cube(const std::string& path) {
    sides = new char[6*3*3];
    std::ifstream idata(path);
    for (int side = 0; side < 6; side++) {
        for (int h = 0; h < 3; ++h) {
            for (int d = 0; d < 3; ++d) {
                idata >> sides[side*9 + h*3 + d];
            }
        }
    }
    front = &sides[0];
    left = &sides[9];
    back = &sides[18];
    right = &sides[27];
    up = &sides[36];
    down = &sides[45];
}
Cube::Cube() {
    sides = new char[6*3*3];
    char side_char[6] = {'R', 'B', 'O', 'G', 'Y', 'W'};
    for (int side = 0; side < 6; side++) {
        for (int h = 0; h < 3; ++h) {
            for (int d = 0; d < 3; ++d) {
                sides[side*9 + h*3 + d] = side_char[side];
            }
        }
    }
    front = &sides[0];
    left = &sides[9];
    back = &sides[18];
    right = &sides[27];
    up = &sides[36];
    down = &sides[45];
}
Cube::Cube(Cube& other)
{
    sides = new char[3*3*6];
    for (int i = 0; i < 6*3*3; i++) {
        *(sides+i) = *(other.sides+i);
    }
    front = sides + (other.front - other.sides);
    left = sides + (other.left - other.sides);
    back = sides + (other.back - other.sides);
    right = sides + (other.right - other.sides);
    up = sides + (other.up - other.sides);
    down = sides + (other.down - other.sides);
}
Cube::Cube(const Cube& other)
{
    sides = new char[3*3*6];
    for (int i = 0; i < 6*3*3; i++) {
        *(sides+i) = *(other.sides+i);
    }
    front = sides + (other.front - other.sides);
    left = sides + (other.left - other.sides);
    back = sides + (other.back - other.sides);
    right = sides + (other.right - other.sides);
    up = sides + (other.up - other.sides);
    down = sides + (other.down - other.sides);
}
std::ostream &operator<<(std::ostream& stream, const Cube& cube) {
    for (int h = 0; h < 3; h++) { // better change the order
        stream << "   ";
        for (int d = 0; d < 3; d++) {
            stream << *(cube.up + h*3 + d);
        }
        stream << std::endl;
    }
    for (int h = 0; h < 3; h++) {
        for (const char* side: {cube.left, cube.front, cube.right, cube.back}) {
            for (int d = 0; d < 3; d++) {
                stream << *(side + 3*h + d);
            }
        }
        stream << std::endl;
    }
    for (int h = 0; h < 3; h++) {
        stream << "   ";
        for (int d = 0; d < 3; d++) {
            stream << *(cube.down + 3*h + d);
        }
        stream << std::endl;
    }
    return stream;
}
Cube& Cube::L_() {
    char tmp[3] = {*front, *(front+3), *(front+6)};
    *(front) = *(up);
    *(front+3) = *(up+3);
    *(front+6) = *(up+6);
    *(up) = *(back+8);
    *(up+3) = *(back+5);
    *(up+6) = *(back+2);
    *(back+8) = *(down);
    *(back+5) = *(down+3);
    *(back+2) = *(down+6);
    *(down) = *(tmp);
    *(down+3) = *(tmp+1);
    *(down+6) = *(tmp+2);
    rotateClockwise(left);
    return *this;
}
Cube& Cube::U_() {
    char tmp[3] = {*right, *(right+1), *(right+2)};
    *(right) = *(back);
    *(right+1) = *(back+1);
    *(right+2) = *(back+2);
    *(back) = *(left);
    *(back+1) = *(left+1);
    *(back+2) = *(left+2);
    *(left) = *(front);
    *(left+1) = *(front+1);
    *(left+2) = *(front+2);
    *(front) = *(tmp);
    *(front+1) = *(tmp+1);
    *(front+2) = *(tmp+2);
    rotateClockwise(up);
    return *this;
}
Cube& Cube::U() {
    actions.push_back('U');
    return U_();
}
Cube& Cube::invU() {
    actions.push_back('\'');
    return U_().U_().U();
}
Cube& Cube::D_() {
    char tmp[3] = {*(right+6), *(right+7), *(right+8)};
    *(right+6) = *(front+6);
    *(right+7) = *(front+7);
    *(right+8) = *(front+8);
    *(front+6) = *(left+6);
    *(front+7) = *(left+7);
    *(front+8) = *(left+8);
    *(left+6) = *(back+6);
    *(left+7) = *(back+7);
    *(left+8) = *(back+8);
    *(back+6) = *(tmp);
    *(back+7) = *(tmp+1);
    *(back+8) = *(tmp+2);
    rotateClockwise(down);
    return *this;
}
Cube& Cube::D() {
    actions.push_back('D');
    return D_();
}
Cube& Cube::invD() {
    actions.push_back('\'');
    return D_().D_().D();
}
Cube& Cube::L() {
    actions.push_back(moves[orientation]);
    return L_();
}
Cube& Cube::invL() {
    actions.push_back('\'');
    return L_().L_().L();
}
Cube& Cube::R() {
    rotateCubeLeft();
    rotateCubeLeft();
    L();
    rotateCubeLeft();
    rotateCubeLeft();

    return *this;
}
Cube& Cube::F() {
    rotateCubeRight();
    L();
    rotateCubeLeft();
    return *this;
}
Cube& Cube::B() {
    rotateCubeLeft();
    L();
    rotateCubeRight();
    return *this;
}
Cube& Cube::invR() {
    rotateCubeLeft();
    rotateCubeLeft();
    invL();
    rotateCubeLeft();
    rotateCubeLeft();
    return *this;
}
Cube& Cube::invF() {
    rotateCubeRight();
    invL();
    rotateCubeLeft();
    return *this;
}
Cube& Cube::invB() {
    rotateCubeLeft();
    invL();
    rotateCubeRight();
    return *this;
}
void Cube::rotateClockwise(char* side) {
    char tmp[9];
    for (int i = 0; i < 9; i++) {
        tmp[i] = *(side + i);
    }
    for (int h = 0; h < 3; h++) {
        for (int d = 0; d < 3; d++) {
            *(side + 3*d + 2-h) = *(tmp + 3 * h + d);
        }
    }
}
void Cube::rotateCounterclockwise(char* side) {
    char tmp[9];
    for (int i = 0; i < 9; i++) {
        tmp[i] = *(side+i);
    }
    for (int h = 0; h < 3; h++) {
        for (int d = 0; d < 3; d++) {
            *(side + 3*h + d) = *(tmp + 3*d + 2-h);
        }
    }
}
void Cube::rotateCubeRight() {
    char* tmp = front;
    front = right;
    right = back;
    back = left;
    left = tmp;
    orientation = (orientation + 1) % 4;
    rotateClockwise(up);
    rotateCounterclockwise(down);
}
void Cube::rotateCubeLeft() {
    char* tmp = front;
    front = left;
    left = back;
    back = right;
    right = tmp;
    orientation = (orientation + 3) % 4;
    rotateClockwise(down);
    rotateCounterclockwise(up);
}
Cube& Cube::operator=(const Cube& other) {
    for (int i = 0; i < 6*3*3; i++) {
        *(sides+i) = *(other.sides+i);
    }
    front = sides + (other.front - other.sides);
    left = sides + (other.left - other.sides);
    back = sides + (other.back - other.sides);
    right = sides + (other.right - other.sides);
    up = sides + (other.up - other.sides);
    down = sides + (other.down - other.sides);
    return *this;
}
Cube::~Cube() {
    delete [] sides;
}
std::string Cube::getMoves() const {
    return actions;
}
Cube& Cube::clearMoves() {
    actions = std::string();
    return *this;
}
void Cube::control() {
    char move = '~';
    while (true) {
        std::cout << *this << std::endl;
        std::cin >> move;
        switch (move) {
            case 'r':
                invR();
                break;
            case 'R':
                R();
                break;
            case 'f':
                invF();
                break;
            case 'F':
                F();
                break;
            case 'b':
                invB();
                break;
            case 'B':
                R();
                break;
            case 'l':
                invL();
                break;
            case 'L':
                L();
                break;
            case 'u':
                invU();
                break;
            case 'U':
                U();
                break;
            case 'd':
                invD();
                break;
            case 'D':
                D();
                break;
            default:
                return ;
        }
    }
}
void Cube::write(const std::string &path) {
    std::ofstream odata(path);
    for (auto side: {front, left, back, right, up, down}) {
        for (int h = 0; h < 3; ++h) {
            for (int d = 0; d < 3; ++d) {
                odata << *(side+h*3 + d);
            }
            odata << std::endl;
        }
        odata << std::endl;
    }
}

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
        if (checkEdge(*(cube.front + 7), *(cube.down + 1), front_color, color)) {
            cube.rotateCubeLeft();
            continue;
        }

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
        cube.rotateCubeLeft();
        char f_color = *(cube.front + 4);
        char d_color = *(cube.down + 4);
        char r_color = *(cube.right + 4);
        if (checkCorner(*(cube.front+8), *(cube.right+6), *(cube.down+2),
                        f_color, d_color, r_color)) {
            while (*(cube.front+8) != f_color) {
                pifPaf(cube);
                pifPaf(cube);
            }
            continue;
        }
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
    }
    return true;
}
bool Solver::solveMiddleEdges(Cube &cube) {
    for (int j = 0; j < 4; j++) {
        cube.rotateCubeRight();
        char f_color = *(cube.front+4);
        char r_color = *(cube.right+4);
        if (*(cube.front+5) == f_color && *(cube.right+3) == r_color) {
            continue;
        }
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
    }
    return true;
}
bool Solver::solveTopX(Cube &cube) {
    char u_color = *(cube.up+4);
    for (int i = 0; i < 4; i++) {
        if (*(cube.up+7) != u_color) {
            cube.F();
            for (int j = 0; j < 3; j++) {
                if (*(cube.right + 3) == u_color) {
                    break;
                }
                pifPaf(cube);
            }
            cube.invF();
        }
        cube.rotateCubeLeft();
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
        if (*(cube.left+1) == l && *(cube.back+1) == b && *(cube.right+1) == r) {
            return true;
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
    for (int i = 0; i < 4; i++) {
        if (*(cube.front+1) == *(cube.front+4)) {
            break;
        }
        cube.U();
    }
    for (int i = 0; i < 4; i++) {
        if (*(cube.front+0) != *(cube.front+1) ||
        *(cube.front+1) != *(cube.front+2) ||
        *(cube.front+2) != *(cube.front+4)) {
            return false;
        }
        cube.rotateCubeLeft();
    }
    return true;
}
bool Solver::solve(Cube &cube) {
    if (!Solver::solveX(cube) || !Solver::solveBottomCorners(cube) || !Solver::solveMiddleEdges(cube) ||
            !Solver::solveTopX(cube) || !Solver::solveTopEdges(cube) || !Solver::solveTopCorners(cube)) {
        std::cout << "Cube is unsolvable" << std::endl;
        return false;
    }
    return true;
}
bool Solver::check(Cube cube) {
    return solve(cube);
}
