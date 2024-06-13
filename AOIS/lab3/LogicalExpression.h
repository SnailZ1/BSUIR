#pragma once

#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <unordered_set>
#include "TruthTable.h"
#include <bitset>

using namespace std;

class LogicalExpr {
private:
    friend class OptimizedLogicalExpr;
    vector<char> operands;
    string rpnResult;
    string expr;
    TruthTable truthTbl;

    string sknfExpr;
    string sdnfExpr;
    vector<bool> indexPattern;

    TruthTable generateTruthTable();
    int getPriority(char op);
    vector<char> extractUniqueOperands();
    string convertToRpn();
    bool checkIfOperand(string token);
    bool performOperation(bool op1, bool op2, char op);
    void evaluateExpr();

    string convertToSknf();
    string convertToSdnf();
    vector<bool> deriveIndexPattern();

public:
    LogicalExpr(string expression);
    void displayInfo();
};