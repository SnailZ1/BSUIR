#pragma once
#include "LogicalExpression.h"
#include "KarnoTable.h"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class OptimizedLogicalExpr {
private:
    string expr;
    string sdnfString;
    string sknfString;
    vector<char> operands;
    vector<bool> indexPattern;

    vector<vector<int>> sdnf;
    vector<vector<int>> sknf;

    vector<vector<int>> sdnfMerged;
    vector<vector<int>> sknfMerged;

    string sdnfMergedStr;
    string sknfMergedStr;

    vector<vector<int>> sdnfAbsorbed;
    vector<vector<int>> sknfAbsorbed;

    string sdnfAbsorbedStr;
    string sknfAbsorbedStr;

    vector<vector<int>> sdnfQuineTable;
    vector<vector<int>> sknfQuineTable;

    vector<vector<int>> sdnfQuineAbsorbed;
    vector<vector<int>> sknfQuineAbsorbed;

    string sdnfQuineAbsorbedStr;
    string sknfQuineAbsorbedStr;

    KarnoGrid* karnGrid;

    KarnoGrid* createKarnoGrid(vector<bool> indexPattern);
    vector<vector<int>> minimizeWithKarnoGrid(KarnoGrid* karnGrid, bool isSdnf);
    vector<vector<int>> minimizeWithKarnoGrid3(KarnoGrid* karnGrid, bool isSdnf);
    vector<vector<int>> minimizeWithKarnoGrid2(KarnoGrid* karnGrid, bool isSdnf);

    vector<vector<int>> sdnfTabular;
    vector<vector<int>> sknfTabular;

    string sdnfTabularStr = "";
    string sknfTabularStr = "";

    vector<vector<int>> exprToVector(string expr, string delimiter);
    string exprToString(vector<vector<int>> mergedExpr, bool isSdnf);

    vector<vector<int>> mergePatterns(vector<vector<int>> patterns);
    vector<vector<int>> absorbPatterns(vector<vector<int>> patterns);

    vector<vector<int>> createQuineTable(vector<vector<int>> elements, vector<vector<int>> mergedElements);
    void displayTable(vector<vector<int>> quineTable);
    vector<vector<int>> performQuineAbsorption(vector<vector<int>> mergedElements, vector<vector<int>> quineTable);

public:
    OptimizedLogicalExpr(LogicalExpr logicExpr);
    void displayInfo();
};