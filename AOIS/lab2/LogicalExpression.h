#pragma once
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <unordered_set>
#include "TableTruth.h"

using namespace std;

class LogExpr {
private:
	vector<char> opersUnique;
	string rpnResult;
	string expression;
	TabTruth tableTruth;

	string expSKNF;
	string numFormSKNF;

	string expSDNF;
	string numFormSDNF;

	vector<bool> expIndex;
	int expIndexDecimal;

	TabTruth createTable();
	int priority(char operation);
	vector<char> getOperands();
	string toRpn();
	bool isOperand(string token);
	bool execOperation(bool operand1, bool operand2, char operation);
	void execExpression();

	string SKNF();
	string numSKNF();
	string SDNF();
	string numSDNF();
	vector<bool> indexForm();
	int indexFormDecimal();
public:
	LogExpr(string exp);
	void infoPrint();
};