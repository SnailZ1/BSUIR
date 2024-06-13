#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Cell {
private:
    friend class OptimizedLogicalExpr;
    friend class KarnoGrid;
    string identifier;
    bool state;
};

class KarnoGrid {
private:
    friend class OptimizedLogicalExpr;

    vector<string> columns;
    vector<string> rows;
    vector<vector<Cell*>> grid;
    void displayGrid();
    vector<bool> populateVec2(vector<bool> indexPattern);
    vector<bool> populateVec3(vector<bool> indexPattern);
    vector<bool> populateVec4(vector<bool> indexPattern);
};