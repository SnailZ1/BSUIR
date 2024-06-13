#include "OptimizedLogicalExpr.h"

OptimizedLogicalExpr::OptimizedLogicalExpr(LogicalExpr logicExpr) {
    expr = logicExpr.expr;
    sdnfString = logicExpr.sdnfString;
    sknfString = logicExpr.sknfString;
    operands = logicExpr.operands;
    indexPattern = logicExpr.indexPattern;

    sdnf = exprToVector(sdnfString, "|");
    sknf = exprToVector(sknfString, "&");

    sdnfMerged = mergePatterns(sdnf);
    sknfMerged = mergePatterns(sknf);

    sdnfAbsorbed = absorbPatterns(sdnfMerged);
    sknfAbsorbed = absorbPatterns(sknfMerged);

    sdnfQuineTable = createQuineTable(sdnf, sdnfMerged);
    sknfQuineTable = createQuineTable(sknf, sknfMerged);

    sdnfQuineAbsorbed = performQuineAbsorption(sdnfMerged, sdnfQuineTable);
    sknfQuineAbsorbed = performQuineAbsorption(sknfMerged, sknfQuineTable);

    karnGrid = createKarnoGrid(indexPattern);

    sdnfTabular = minimizeWithKarnoGrid(karnGrid, true);
    sknfTabular = minimizeWithKarnoGrid(karnGrid, false);

    sdnfMergedStr = exprToString(sdnfMerged, true);
    sknfMergedStr = exprToString(sknfMerged, false);

    sdnfAbsorbedStr = exprToString(sdnfAbsorbed, true);
    sknfAbsorbedStr = exprToString(sknfAbsorbed, false);

    sdnfQuineAbsorbedStr = exprToString(sdnfQuineAbsorbed, true);
    sknfQuineAbsorbedStr = exprToString(sknfQuineAbsorbed, false);

    sdnfTabularStr = exprToString(sdnfTabular, true);
    sknfTabularStr = exprToString(sknfTabular, false);
}

void OptimizedLogicalExpr::displayInfo() {
    cout << "Expression:\n\n";
    cout << expr << endl;
    for (auto element : indexPattern) {
        cout << element << " ";
    }
    cout << endl;

    cout << "\nPerfect forms of expression:\n";
    cout << "\nSDNF expression: " << sdnfString << endl;
    cout << "SKNF expression: " << sknfString << endl;

    cout << "\nThe first stage of the calculation method:\n";
    cout << "\nSDNF_after_merging: " << sdnfMergedStr << endl;
    cout << "SKNF_after_merging: " << sknfMergedStr << endl;

    cout << "\nThe second stage of the calculation method:\n";
    cout << "\nSDNF_after_absorption: " << sdnfAbsorbedStr << endl;
    cout << "SKNF_after_absorption: " << sknfAbsorbedStr << endl;

    cout << "\nThe second stage of the calculation-tabular method:\n";
    cout << "\nSDNF_Quine_table:\n";
    displayTable(sdnfQuineTable);
    cout << "\nSDNF_after_Quine_absorption: " << sdnfQuineAbsorbedStr << endl;

    cout << "\nSKNF_Quine_table:\n";
    displayTable(sknfQuineTable);
    cout << "\nSKNF_after_Quine_absorption: " << sknfQuineAbsorbedStr << endl;

    cout << "\nThe tabular method:\n";
    cout << "\nKarno_table:\n";
    karnGrid->printGrid();
    cout << "\nSDNF_after_tabular_method: " << sdnfTabularStr << endl;
    cout << "SKNF_after_tabular_method: " << sknfTabularStr << endl;
}

vector<vector<int>> OptimizedLogicalExpr::exprToVector(string exp, string delimiter) {
    vector<vector<int>> result;
    if (exp.empty()) {
        return result;
    }
    vector<string> elements;

    int openBracketCount = 0;
    string currentElement;

    istringstream iss(exp);
    string token;

    while (getline(iss, token, delimiter[0])) {
        for (char c : token) {
            if (c == '(') {
                openBracketCount++;
            }
            else if (c == ')') {
                openBracketCount--;
            }
        }

        if (openBracketCount == 0 && !token.empty()) {
            elements.push_back(token);
        }
        else {
            currentElement += token + delimiter;
        }
    }

    if (!currentElement.empty()) {
        currentElement.pop_back();
        elements.push_back(currentElement);
    }

    result.resize(elements.size());
    for (int i = 0; i < elements.size(); i++) {
        for (int j = 0; j < elements[i].size(); j++) {
            if (elements[i][j] == '!') {
                result[i].push_back(-(elements[i][j + 1] - 'A' + 1));
                j++;
            }
            else if (elements[i][j] >= 'A' && elements[i][j] <= 'Z') {
                result[i].push_back(elements[i][j] - 'A' + 1);
            }
        }
    }

    return result;
}

string OptimizedLogicalExpr::exprToString(vector<vector<int>> mergedExpr, bool isSdnf) {
    string result = "";
    string index = "";
    char s1, s2;
    if (isSdnf) {
        s1 = '&';
        s2 = '|';
    }
    else {
        s1 = '|';
        s2 = '&';
    }
    for (int i = 0; i < mergedExpr.size(); i++) {
        result += "(";
        for (int j = 0; j < mergedExpr[i].size(); j++) {
            if (mergedExpr[i][j] > 0) {
                index = string(1, operands[abs(mergedExpr[i][j]) - 1]);
            }
            else {
                index = "!" + string(1, operands[abs(mergedExpr[i][j]) - 1]);
            }
            if (j == mergedExpr[i].size() - 1) {
                result += index;
            }
            else {
                result += index + s1;
            }
        }
        if (i == mergedExpr.size() - 1) {
            result += ")";
        }
        else {
            result += ")" + string(1, s2);
        }
    }
    return result;
}

vector<vector<int>> OptimizedLogicalExpr::mergePatterns(vector<vector<int>> patterns) {
    vector<vector<int>> merging_result;
    for (int i = 0; i < patterns.size(); i++) {
        int j = 0;
        for (; j < merging_result.size(); j++) {
            vector<int> temp;
            set_union(merging_result[j].begin(), merging_result[j].end(),
                patterns[i].begin(), patterns[i].end(), back_inserter(temp));
            if (temp == merging_result[j]) {
                break;
            }
        }
        if (j == merging_result.size()) {
            merging_result.push_back(patterns[i]);
        }
    }
    sort(merging_result.begin(), merging_result.end());
    return merging_result;
}

vector<vector<int>> OptimizedLogicalExpr::absorbPatterns(vector<vector<int>> patterns) {
    vector<vector<int>> absorbed_result = patterns;
    for (int i = 0; i < absorbed_result.size(); i++) {
        for (int j = i + 1; j < absorbed_result.size(); j++) {
            vector<int> temp;
            set_difference(absorbed_result[i].begin(), absorbed_result[i].end(),
                absorbed_result[j].begin(), absorbed_result[j].end(),
                back_inserter(temp));
            if (temp.empty()) {
                absorbed_result.erase(absorbed_result.begin() + j);
                j--;
            }
        }
    }
    sort(absorbed_result.begin(), absorbed_result.end());
    return absorbed_result;
}

vector<vector<int>> OptimizedLogicalExpr::createQuineTable(vector<vector<int>> elements, vector<vector<int>> mergedElements) {
    vector<vector<int>> tables_result;
    tables_result.resize(elements.size());
    for (int i = 0; i < elements.size(); i++) {
        for (int j = 0; j < mergedElements.size(); j++) {
            vector<int> temp;
            set_difference(elements[i].begin(), elements[i].end(),
                mergedElements[j].begin(), mergedElements[j].end(),
                back_inserter(temp));
            if (temp.empty()) {
                tables_result[i].push_back(j);
            }
        }
    }
    return tables_result;
}

void OptimizedLogicalExpr::displayTable(vector<vector<int>> quineTable) {
    for (int i = 0; i < quineTable.size(); i++) {
        for (int j = 0; j < quineTable[i].size(); j++) {
            cout << quineTable[i][j] << " ";
        }
        cout << endl;
    }
}

KarnoGrid* OptimizedLogicalExpr::createKarnoGrid(vector<bool> indexPattern) {
    KarnoGrid* grid = new KarnoGrid();
    grid->indexPattern = indexPattern;
    return grid;
}

vector<vector<int>> OptimizedLogicalExpr::minimizeWithKarnoGrid(KarnoGrid* karnGrid, bool isSdnf) {
    if (isSdnf) {
        return karnGrid->tabularSdnf;
    }
    else {
        return karnGrid->tabularSknf;
    }
}

vector<vector<int>> OptimizedLogicalExpr::minimizeWithKarnoGrid2(KarnoGrid* karnGrid, bool isSdnf) {
    if (isSdnf) {
        return karnGrid->tabularSdnf;
    }
    else {
        return karnGrid->tabularSknf;
    }
}

vector<vector<int>> OptimizedLogicalExpr::minimizeWithKarnoGrid3(KarnoGrid* karnGrid, bool isSdnf) {
    if (isSdnf) {
        return karnGrid->tabularSdnf;
    }
    else {
        return karnGrid->tabularSknf;
    }
}