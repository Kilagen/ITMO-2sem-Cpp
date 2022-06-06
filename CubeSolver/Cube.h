//
// Created by kil4g on 14.05.2022.
//
#include <string>
#include <vector>
#include <map>

#ifndef LAB5_CUBE_H
#define LAB5_CUBE_H

class Cube {
public:
    Cube();
    explicit Cube(const std::string& path);
    Cube(Cube& other);
    Cube(const Cube& other);
    ~Cube();
    Cube& operator=(const Cube& other);
    void write(const std::string& path);
    friend std::ostream& operator<< (std::ostream& ostream, const Cube& cube);
    friend class Solver;
    [[nodiscard]] std::string getMoves() const;
    Cube& clearMoves();
    Cube& U();
    Cube& D();
    Cube& L();
    Cube& R();
    Cube& F();
    Cube& B();
    Cube& invU();
    Cube& invD();
    Cube& invL();
    Cube& invR();
    Cube& invF();
    Cube& invB();
    void control();
private:
    std::string actions;
    Cube& L_();
    Cube& U_();
    Cube& D_();
    char moves[4] = {'L', 'F', 'R', 'B'};
    int orientation = 0;
    char* sides;
    char* front;
    char* left;
    char* right;
    char* back;
    char* up;
    char* down;
    void rotateCubeLeft();
    void rotateCubeRight();
    static void rotateClockwise(char* side);
    static void rotateCounterclockwise(char* side);
};

class Solver {
public:
    static bool solveX(Cube& cube);
    static bool solveBottomCorners(Cube& cube);
    static bool solveMiddleEdges(Cube &cube);
    static bool solveTopX(Cube &cube);
    static bool solveTopEdges(Cube &cube);
    static bool solveTopCorners(Cube &cube);
    static bool solve(Cube &cube);
    static bool check(Cube cube);
    static void pifPaf(Cube &cube);
private:
    static bool checkEdge(char& side1, char& side2, char& expect1, char& expect2);
    static bool checkCorner(char &side1, char &side2, char &side3, char &expect1, char &expect2, char &expect3);
};
#endif //LAB5_CUBE_H
