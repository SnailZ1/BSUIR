#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <map>

using namespace std;

class Column {
private:
	friend class LogExpr;
	friend class TabTruth;
	string name;
	vector<bool> cols;
	Column(const std::string& colName, const vector<bool>& colData) : name(colName), cols(colData) {}
};

class TabTruth {
private:
	friend class LogExpr;
	TabTruth(int rows);

	vector<Column> colsName;
	map<string, int> indexName;
	int rows;

	void addColumn(string colName);
	void setValue(string colName, int rowIndex, bool value);

	bool getColumnValue(const string& colName, int rowIndex) const;
	string getStringTable();
};
