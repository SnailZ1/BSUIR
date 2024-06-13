#include "LogicalExpression.h"
#include "OptimizedLogicalExpr.h"

int main() {
	// (a|b|!c|!d)&(!b|d)&(!b|c)&(!a|d)&(!a|c)
	//выражение для совершенных форм равно 0 или 1 но на одном наборе значений
	// (!a&b&c)|(a&!b&!c)|(a&!b&c)|(a&b&!c)|(a&b&c)
	LogicalExpr exp("(a|!b)&!c");
	OptimizedLogicalExpr min_exp(exp);
	exp.displayInfo();
	min_exp.displayInfo();
	cout << endl;
	return 0;
}