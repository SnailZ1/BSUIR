#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <map>

using namespace std;

class TableColumn {
private:
    friend class LogicalExpr;
    friend class TruthTable;
    string name;
    vector<bool> values;
    TableColumn(const string& name, const vector<bool>& values) : name(name), values(values) {}
};

class TruthTable {
private:
    friend class LogicalExpr;
    TruthTable(int rows);
    TruthTable() {}

    vector<TableColumn> columns;
    map<string, int> columnIndex;
    int rows;

    void addColumn(string colName);
    void setValue(string colName, int rowIndex, bool val);

    bool getColumnValue(const string& colName, int rowIndex) const;
    string convertTableToString();
};