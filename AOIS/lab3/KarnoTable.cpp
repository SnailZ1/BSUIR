#include "LogicalExpression.h"

LogicalExpr::LogicalExpr(string exp) {
    this->expr = exp;
    this->rpnResult = convertToRpn();
    this->operands = extractUniqueOperands();
    this->truthTbl = generateTruthTable();
    evaluateExpr();

    this->sdnfExpr = convertToSdnf();
    this->sknfExpr = convertToSknf();
    this->indexPattern = deriveIndexPattern();
}

void LogicalExpr::displayInfo() {
    cout << "Truth Table:\n" << truthTbl.convertTableToString() << endl;
    cout << "\nSDNF Expression: " << sdnfExpr << endl;
    cout << "SKNF Expression: " << sknfExpr << endl << endl;
}

TruthTable LogicalExpr::generateTruthTable() {
    int numOperands = operands.size();
    int numRows = pow(2, numOperands);
    TruthTable tbl(numRows);

    for (char operand : operands) {
        string colName(1, operand);
        tbl.addColumn(colName);
    }

    for (int i = 0; i < numRows; i++) {
        string bin = bitset<32>(i).to_string().substr(32 - numOperands);
        vector<bool> rowVals;
        for (char c : bin) {
            rowVals.push_back(c == '1');
        }
        for (int j = 0; j < rowVals.size(); j++) {
            tbl.setValue(string(1, operands[j]), i, rowVals[j]);
        }
    }
    return tbl;
}

vector<char> LogicalExpr::extractUniqueOperands() {
    unordered_set<char> operandSet;

    for (char c : rpnResult) {
        if (isalpha(c) || isdigit(c)) {
            operandSet.insert(c);
        }
    }

    vector<char> result;
    for (char operand : operandSet) {
        result.push_back(operand);
    }
    return result;
}

string LogicalExpr::convertToRpn() {
    stack<char> opStack;
    string result = "";
    int openCount = 0;
    int closeCount = 0;

    for (char symbol : expr) {
        if (isalpha(symbol) || isdigit(symbol)) {
            result += symbol;
        }
        else if (symbol == '(') {
            opStack.push(symbol);
            openCount++;
        }
        else if (symbol == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                result += opStack.top();
                opStack.pop();
            }
            opStack.pop();
            closeCount++;
        }
        else {
            while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(symbol)) {
                result += opStack.top();
                opStack.pop();
            }
            opStack.push(symbol);
        }
    }

    while (!opStack.empty()) {
        result += opStack.top();
        opStack.pop();
    }
    return result;
}

int LogicalExpr::getPriority(char op) {
    switch (op) {
    case '!':
        return 5;
    case '&':
        return 4;
    case '|':
        return 3;
    case '>':
        return 2;
    case '~':
        return 1;
    default:
        return 0;
    }
}

bool LogicalExpr::checkIfOperand(string token) {
    return token != "!" && token != "&" && token != "|" && token != ">" && token != "~";
}

bool LogicalExpr::performOperation(bool op1, bool op2, char op) {
    switch (op) {
    case '&':
        return op1 && op2;
    case '|':
        return op1 || op2;
    case '>':
        return !op1 || op2;
    case '~':
        return op1 == op2;
    }
}

void LogicalExpr::evaluateExpr() {
    stack<string> opStack;
    vector<char> tokens(rpnResult.begin(), rpnResult.end());

    for (auto token : tokens) {
        string tokenStr(1, token);
        if (checkIfOperand(tokenStr)) {
            opStack.push(tokenStr);
        }
        else {
            string op1, op2;
            if (token == '!') {
                op1 = opStack.top();
                opStack.pop();
                string resultCol = "(!" + op1 + ")";
                truthTbl.addColumn(resultCol);
                for (int i = 0; i < truthTbl.rows; i++) {
                    bool val = !truthTbl.getColumnValue(op1, i);
                    truthTbl.setValue(resultCol, i, val);
                }
                opStack.push(resultCol);
            }
            else {
                op2 = opStack.top();
                opStack.pop();
                op1 = opStack.top();
                opStack.pop();
                string resultCol = "(" + op1 + token + op2 + ")";
                truthTbl.addColumn(resultCol);
                for (int i = 0; i < truthTbl.rows; i++) {
                    bool val1 = truthTbl.getColumnValue(op1, i);
                    bool val2 = truthTbl.getColumnValue(op2, i);
                    bool result = performOperation(val1, val2, token);
                    truthTbl.setValue(resultCol, i, result);
                }
                opStack.push(resultCol);
            }
        }
    }
}

string LogicalExpr::convertToSknf() {
    vector<string> cnfClauses;
    int lastIndex = truthTbl.columns.size() - 1;

    auto joinStrings = [](const vector<string>& vec, const string& delimiter) {
        string result;
        for (size_t i = 0; i < vec.size(); i++) {
            result += vec[i];
            if (i != vec.size() - 1) {
                result += delimiter;
            }
        }
        return result;
    };

    for (int i = 0; i < truthTbl.rows; i++) {
        if (!truthTbl.columns[lastIndex].values[i]) {
            vector<string> disjunction;
            for (size_t j = 0; j < operands.size(); j++) {
                char operand = operands[j];
                bool opValue = truthTbl.columns[truthTbl.columnIndex[string(1, operand)]].values[i];

                if (opValue) {
                    disjunction.push_back("!" + string(1, operand));
                }
                else {
                    disjunction.push_back(string(1, operand));
                }
            }
            cnfClauses.push_back("(" + joinStrings(disjunction, "|") + ")");
        }
    }

    string result = joinStrings(cnfClauses, "&");
    return result;
}

string LogicalExpr::convertToSdnf() {
    vector<string> dnfClauses;
    int lastIndex = truthTbl.columns.size() - 1;

    auto joinStrings = [](const vector<string>& vec, const string& delimiter) {
        string result;
        for (size_t i = 0; i < vec.size(); i++) {
            result += vec[i];
            if (i != vec.size() - 1) {
                result += delimiter;
            }
        }
        return result;
    };

    for (int i = 0; i < truthTbl.rows; i++) {
        if (truthTbl.columns[lastIndex].values[i]) {
            vector<string> conjunction;
            for (size_t j = 0; j < operands.size(); j++) {
                char operand = operands[j];
                bool opValue = truthTbl.columns[truthTbl.columnIndex[string(1, operand)]].values[i];

                if (!opValue) {
                    conjunction.push_back("!" + string(1, operand));
                }
                else {
                    conjunction.push_back(string(1, operand));
                }
            }
            dnfClauses.push_back("(" + joinStrings(conjunction, "&") + ")");
        }
    }

    string result = joinStrings(dnfClauses, "|");
    return result;
}

vector<bool> LogicalExpr::deriveIndexPattern() {
    vector<bool> result;
    int lastIndex = truthTbl.columns.size() - 1;

    for (int i = 0; i < truthTbl.rows; i++) {
        result.push_back(truthTbl.columns[lastIndex].values[i]);
    }
    return result;
}
