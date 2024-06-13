#include "TruthTable.h"

TruthTable::TruthTable(int rows) : rows(rows) {}

void TruthTable::addColumn(string colName) {
    if (columnIndex.find(colName) == columnIndex.end()) {
        columns.push_back(TableColumn(colName, vector<bool>(rows, false)));
        columnIndex[colName] = columns.size() - 1;
    }
}

void TruthTable::setValue(string colName, int rowIndex, bool val) {
    if (rowIndex >= 0 && rowIndex < rows) {
        if (columnIndex.find(colName) != columnIndex.end()) {
            columns[columnIndex[colName]].values[rowIndex] = val;
        }
    }
}

bool TruthTable::getColumnValue(const string& colName, int rowIndex) const {
    if (rowIndex >= 0 && rowIndex < rows) {
        if (columnIndex.find(colName) != columnIndex.end()) {
            return columns[columnIndex.at(colName)].values[rowIndex];
        }
    }
    return false;
}

string TruthTable::convertTableToString() {
    ostringstream tableString;
    map<string, int> columnWidths;
    vector<string> columnOrder;

    for (const auto& column : columns) {
        int maxColumnWidth = column.name.length();

        for (const auto& value : column.values) {
            string valueString = value ? "1" : "0";
            if (valueString.length() > maxColumnWidth)
                maxColumnWidth = valueString.length();
        }

        columnWidths[column.name] = maxColumnWidth;
        columnOrder.push_back(column.name);
    }

    for (const auto& columnName : columnOrder) {
        tableString << " |  " << setw(columnWidths.at(columnName)) << columnName;
    }
    tableString << '\n';

    for (int i = 0; i < rows; i++) {
        for (const auto& columnName : columnOrder) {
            string valueString = columns[columnIndex.at(columnName)].values[i] ? "1" : "0";
            tableString << " |  " << left << setw(columnWidths.at(columnName)) << valueString;
        }
        tableString << '\n';
    }

    return tableString.str();
}