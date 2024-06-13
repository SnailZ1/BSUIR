#include "LogicalExpression.h"

LogExpr::LogExpr(string exp) {
    this->expression = exp;
    this->rpnResult = toRpn();
    this->opersUnique = getOperands();
    this->tableTruth = createTable();
    execExpression();
    this->expSDNF = SDNF();
    this->numFormSDNF = numSDNF();
    this->expSKNF = SKNF();
    this->numFormSKNF = numSKNF();
    this->expIndex = indexForm();
    this->expIndexDecimal = indexFormDecimal();
}

string LogExpr::toRpn() {
    stack<char> stack;
    string result = "";
    int openParent = 0;
    int closeParent = 0;
    for (char c : expression) {
        if (isalpha(c) || isdigit(c)) {
            result += c;
        }
        else if (c == '(') {
            stack.push(c);
            openParent++;
        }
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                result += stack.top();
                stack.pop();
            }
            stack.pop();
            closeParent++;
        }
        else {
            while (!stack.empty() && priority(stack.top()) >= priority(c)) {
                result += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.empty()) {
        result += stack.top();
        stack.pop();
    }
    return result;
}

vector<char> LogExpr::getOperands() {
    unordered_set<char> opSet;

    for (char c : rpnResult) {
        if (isalpha(c) || isdigit(c)) {
            opSet.insert(c);
        }
    }

    vector<char> result;
    for (char op : opSet) {
        result.push_back(op);
    }
    return result;
}

void LogExpr::infoPrint() {
    cout << "Truth table:\n" << tableTruth.getStringTable();

    cout << "\nSKNF expression: " << expSKNF;
    cout << "\nSKNF num form: " << numFormSKNF;
    cout << "\nSDNF expression: " << expSDNF;
    cout << "\nSDNF num form: " << numFormSDNF;
    cout << "\nIndex form: ";
    for (const auto& element : expIndex) cout << element << " ";
    cout << "\nIndex form in decimal: " << expIndexDecimal << endl;
}

TabTruth LogExpr::createTable() {
    int opCount = opersUnique.size();
    int rows = pow(2, opCount);
    TabTruth table(rows);

    for (char op : opersUnique) {
        string colName(1, op);
        table.addColumn(colName);
    }

    for (int i = 0; i < rows; i++) {
        string binary = std::bitset<32>(i).to_string().substr(32 - opCount);
        vector<bool> rowValues;
        for (char c : binary) {
            rowValues.push_back(c == '1');
        }
        for (int j = 0; j < rowValues.size(); j++) {
            table.setValue(string(1, opersUnique[j]), i, rowValues[j]);
        }
    }
    return table;
}

int LogExpr::priority(char operation) {
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

bool LogExpr::isOperand(string token) {
    return token != "!" && token != "&" && token != "|" && token != ">" && token != "~";
}

bool LogExpr::execOperation(bool op1, bool op2, char operation) {
    switch (operation) {
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

void LogExpr::execExpression() {
    stack<string> stack;
    vector<char> tokens;

    for (char c : rpnResult) {
        tokens.push_back(c);
    }

    for (auto token : tokens) {
        string tokenStr(1, token);
        if (isOperand(tokenStr)) {
            stack.push(tokenStr);
        }
        else {
            string op1, op2;
            if (token == '!') {
                op1 = stack.top();
                stack.pop();
                string resCol = "(!" + op1 + ")";
                tableTruth.addColumn(resCol);
                for (int i = 0; i < tableTruth.rows; i++) {
                    bool val = !tableTruth.getColumnValue(op1, i);
                    tableTruth.setValue(resCol, i, val);
                }
                stack.push(resCol);
            }
            else {
                op2 = stack.top();
                stack.pop();
                op1 = stack.top();
                stack.pop();
                string resCol = "(" + op1 + token + op2 + ")";
                tableTruth.addColumn(resCol);
                for (int i = 0; i < tableTruth.rows; i++) {
                    bool val1 = tableTruth.getColumnValue(op1, i);
                    bool val2 = tableTruth.getColumnValue(op2, i);
                    bool res = execOperation(val1, val2, token);
                    tableTruth.setValue(resCol, i, res);
                }
                stack.push(resCol);
            }
        }
    }
}

string LogExpr::SKNF() {
    vector<string> cnfClauses;
    int lastIndex = tableTruth.colsName.size() - 1;

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

    for (int i = 0; i < tableTruth.rows; i++) {
        if (!tableTruth.colsName[lastIndex].cols[i]) {
            vector<string> disjunction;
            for (size_t j = 0; j < opersUnique.size(); j++) {
                char op = opersUnique[j];
                bool opValue = tableTruth.colsName[tableTruth.indexName[string(1, op)]].cols[i];
                if (opValue) {
                    disjunction.push_back("!" + string(1, op));
                }
                else {
                    disjunction.push_back(string(1, op));
                }
            }
            cnfClauses.push_back("(" + stringJoin(disjunction, "|") + ")");
        }
    }

    return stringJoin(cnfClauses, "&");
}

string LogExpr::numSDNF() {
    string result = "(";
    int lastIndex = tableTruth.colsName.size() - 1;

    for (int i = 0; i < tableTruth.rows; i++) {
        if (tableTruth.colsName[lastIndex].cols[i]) {
            result = result + to_string(i) + ",";
        }
    }
    result.pop_back();
    result = result + ") |";

    return result;
}

string LogExpr::SDNF() {
    vector<string> cnfClauses;
    int lastIndex = tableTruth.colsName.size() - 1;

    auto stringJoin = [](const vector<string>& vec, const string& delimiter) {
        string result;
        for (size_t i = 0; i < vec.size(); i++) {
            result += vec[i];
            if (i != vec.size() - 1) {
                result += delimiter
            }
        }
        return result;
    };

    for (int i = 0; i < tableTruth.rows; i++) {
        if (tableTruth.colsName[lastIndex].cols[i]) {
            vector<string> conjunction;
            for (size_t j = 0; j < opersUnique.size(); j++) {
                char op = opersUnique[j];
                bool opValue = tableTruth.colsName[tableTruth.indexName[string(1, op)]].cols[i];
                if (!opValue) {
                    conjunction.push_back("!" + string(1, op));
                }
                else {
                    conjunction.push_back(string(1, op));
                }
            }
            cnfClauses.push_back("(" + stringJoin(conjunction, "&") + ")");
        }
    }

    return stringJoin(cnfClauses, "|");
}

string LogExpr::numSKNF() {
    string result = "(";
    int lastIndex = tableTruth.colsName.size() - 1;

    for (int i = 0; i < tableTruth.rows; i++) {
        if (!tableTruth.colsName[lastIndex].cols[i]) {
            result = result + to_string(i) + ",";
        }
    }
    result.pop_back();
    result = result + ") &";

    return result;
}

vector<bool> LogExpr::indexForm() {
    vector<bool> result;
    int lastIndex = tableTruth.colsName.size() - 1;

    for (int i = 0; i < tableTruth.rows; i++) {
        result.push_back(tableTruth.colsName[lastIndex].cols[i]);
    }
    return result;
}

int LogExpr::indexFormDecimal() {
    int decimal = 0;
    int base = 1;
    for (int i = expIndex.size() - 1; i >= 0; i--) {
        if (expIndex[i]) {
            decimal += base;
        }
        base *= 2;
    }
    return decimal;
}