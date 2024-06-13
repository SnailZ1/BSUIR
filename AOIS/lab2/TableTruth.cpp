#include "TableTruth.h"

TabTruth::TabTruth(int rows) {
    this->rows = rows;
}

void TabTruth::addColumn(string colName) {
    if (indexName.find(colName) == indexName.end()) {
        colsName.push_back(Column{ colName, vector<bool>(rows, false) });
        indexName[colName] = indexName.size();
    }
}

void TabTruth::setValue(string colName, int rowIndex, bool value) {
    if (rowIndex >= 0 && rowIndex < rows) {
        for (auto& column : colsName) {
            if (column.name == colName && rowIndex < column.cols.size()) {
                column.cols[rowIndex] = value;
                return;
            }
        }
    }
    else {
        for (auto& column : colsName) {
            if (column.cols.size() < rows) {
                column.cols.resize(rows, false);
            }
        }
        for (auto& column : colsName) {
            if (column.name == colName && rowIndex < column.cols.size()) {
                column.cols[rowIndex] = value;
                return;
            }
        }
    }
}

bool TabTruth::getColumnValue(const string& colName, int rowIndex) const {
    for (const auto& column : colsName) {
        if (column.name == colName && rowIndex < column.cols.size()) {
            return column.cols[rowIndex];
        }
    }
    return false;
}

string TabTruth::getStringTable() {
    ostringstream tableString;
    map<string, int> colWidths;
    vector<string> colOrder;
    for (const auto& column : colsName) {
        int maxColWidth = column.name.length();
        for (const auto& value : column.cols) {
            int valueLen = value ? 1 : 0;
            string valueStr = value ? "1" : "0";
            if (valueStr.length() > maxColWidth)
                maxColWidth = valueStr.length();
        }
        colWidths[column.name] = maxColWidth;
        colOrder.push_back(column.name);
    }

    for (const auto& colName : colOrder) {
        tableString << " |  " << std::setw(colWidths[colName]) << colName;
    }
    tableString << '\n';

    for (int i = 0; i < rows; i++) {
        for (const auto& colName : colOrder) {
            string valueStr = colsName[indexName[colName]].cols[i] ? "1" : "0";
            tableString << " |  " << std::left << std::setw(colWidths[colName]) << valueStr;
        }
        tableString << '\n';
    }

    return tableString.str();
}