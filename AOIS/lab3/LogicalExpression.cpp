#include "LogicalExpression.h"
#include <iostream>

LogicalExpr::LogicalExpr(string expression) : expr(expression) {
    rpnResult = convertToRpn();
    operands = extractUniqueOperands();
    truthTbl = generateTruthTable();
    evaluateExpr();
    sdnfExpr = convertToSdnf();
    sknfExpr = convertToSknf();
    indexPattern = deriveIndexPattern();
}

void LogicalExpr::displayInfo() {
    cout << "Truth table:\n" << truthTbl.getTruthTableString() << endl;
    cout << "\nSDNF expression: " << sdnfExpr << endl;
    cout << "SKNF expression: " << sknfExpr << endl << endl;
}

TruthTable LogicalExpr::generateTruthTable() {
    int operandCount = operands.size();
    int rows = pow(2, operandCount);
    TruthTable table(rows);

    for (char operand : operands) {
        string columnName(1, operand);
        table.addColumn(columnName);
    }

    for (int i = 0; i < rows; i++) {
        string binary = std::bitset<32>(i).to_string().substr(32 - operandCount);
        vector<bool> rowValues;
        for (char c : binary) {
            rowValues.push_back(c == '1');
        }
        for (int j = 0; j < rowValues.size(); j++) {
            table.setValue(string(1, operands[j]), i, rowValues[j]);
        }
    }
    return table;
}

vector<char> LogicalExpr::extractUniqueOperands() {
    unordered_set<char> unique;
    for (char c : rpnResult) {
        if (isalpha(c) || isdigit(c)) {
            unique.insert(c);
        }
    }
    return vector<char>(unique.begin(), unique.end());
}

string LogicalExpr::convertToRpn() {
    stack<char> stack;
    string result = "";
    for (char symbol : expr) {
        if (isalpha(symbol) || isdigit(symbol)) {
            result += symbol;
        }
        else if (symbol == '(') {
            stack.push(symbol);
        }
        else if (symbol == ')') {
            while (!stack.empty() && stack.top() != '(') {
                result += stack.top();
                stack.pop();
            }
            stack.pop(); // убирает "(" из стека
        }
        else {
            while (!stack.empty() && getPriority(stack.top()) >= getPriority(symbol)) {
                result += stack.top();
                stack.pop();
            }
            stack.push(symbol);
        }
    }
    while (!stack.empty()) {
        result += stack.top();
        stack.pop();
    }
    return result;
}

int LogicalExpr::getPriority(char operation) {
    switch (operation) {
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

bool LogicalExpr::performOperation(bool operand1, bool operand2, char operation) {
    switch (operation) {
    case '&':
        return operand1 && operand2;
    case '|':
        return operand1 || operand2;
    case '>':
        return !operand1 || operand2;
    case '~':
        return operand1 == operand2;
    default:
        return false;
    }
}

void LogicalExpr::evaluateExpr() {
    stack<string> stack;
    vector<char> tokens(rpnResult.begin(), rpnResult.end());

    for (char token : tokens) {
        string tokenString(1, token);
        if (checkIfOperand(tokenString)) {
            stack.push(tokenString);
        }
        else {
            string operand1, operand2;
            if (token == '!') {
                operand1 = stack.top();
                stack.pop();
                string resultColumn = "(!" + operand1 + ")";
                truthTbl.addColumn(resultColumn);
                for (int i = 0; i < truthTbl.rows; i++) {
                    bool val = !truthTbl.getColumnValue(operand1, i);
                    truthTbl.setValue(resultColumn, i, val);
                }
                stack.push(resultColumn);
            }
            else {
                operand2 = stack.top();
                stack.pop();
                operand1 = stack.top();
                stack.pop();
                string resultColumn = "(" + operand1 + token + operand2 + ")";
                truthTbl.addColumn(resultColumn);
                for (int i = 0; i < truthTbl.rows; i++) {
                    bool val1 = truthTbl.getColumnValue(operand1, i);
                    bool val2 = truthTbl.getColumnValue(operand2, i);
                    bool result = performOperation(val1, val2, token);
                    truthTbl.setValue(resultColumn, i, result);
                }
                stack.push(resultColumn);
            }
        }
    }
}

string LogicalExpr::convertToSknf() {
    vector<string> cnfClauses;
    int lastIndex = truthTbl.columns.size() - 1;

    auto stringJoin = [](const vector<string>& vec, const string& delimiter) {
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
                bool operandValue = truthTbl.columns[truthTbl.columnIndex[string(1, operand)]].values[i];
                if (operandValue) {
                    disjunction.push_back("!" + string(1, operand));
                }
                else {
                    disjunction.push_back(string(1, operand));
                }
            }
            cnfClauses.push_back("(" + stringJoin(disjunction, "|") + ")");
        }
    }

    return stringJoin(cnfClauses, "&");
}

string LogicalExpr::convertToSdnf() {
    vector<string> dnfClauses;
    int lastIndex = truthTbl.columns.size() - 1;

    auto stringJoin = [](const vector<string>& vec, const string& delimiter) {
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
                bool operandValue = truthTbl.columns[truthTbl.columnIndex[string(1, operand)]].values[i];
                if (!operandValue) {
                    conjunction.push_back("!" + string(1, operand));
                }
                else {
                    conjunction.push_back(string(1, operand));
                }
            }
            dnfClauses.push_back("(" + stringJoin(conjunction, "&") + ")");
        }
    }

    return stringJoin(dnfClauses, "|");
}

vector<bool> LogicalExpr::deriveIndexPattern() {
    vector<bool> pattern;
    int lastIndex = truthTbl.columns.size() - 1;

    for (int i = 0; i < truthTbl.rows; i++) {
        pattern.push_back(truthTbl.columns[lastIndex].values[i]);
    }

    return pattern;
}
