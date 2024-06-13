#include "LogicalExpression.h"

int main() {
    string str; // (a|!b)>(b&!c)
    cout << "Enter expression: ";
    cin >> str;
    LogExpr exp(str);
    exp.infoPrint();
    return 0;
}