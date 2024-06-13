#include "Matrix.h"

Matrix::Matrix(vector<vector<bool>> data) : data(data) {}

void Matrix::setElement(int row, int col, bool value) {
    if (row >= 0 && row < data.size() && col >= 0 && col < data[row].size()) {
        data[row][col] = value;
    }
}

vector<bool> Matrix::getWord(int index) {
    vector<bool> column;
    column.push_back(data[index][index]);
    for (int i = 1, j = index + 1; i < data[0].size(); i++, j++) {
        if (j > data.size()-1) j = 0;
        column.push_back(data[j][index]);
    }
	return column;
}

vector<bool> Matrix::getAdres(int index) {
    vector<bool> adres;
    adres.push_back(data[index][0]);
    for (int i = 1, j = index + 1; i < data[0].size(); i++, j++) {
        if (j > data.size() - 1) j = 0;
        adres.push_back(data[j][i]);
    }
	return adres;
}

void Matrix::printWord(vector<bool> word) {
	cout << "Word: ";
	for (bool val : word) {
		cout << val ? 0 : 1;
	}
    cout << endl;
}

void Matrix::printAdres(vector<bool> adres) {
	cout << "Adres: ";
	for (bool val : adres) {
		cout << val ? 0 : 1;
	}
    cout << endl;
}

vector<vector<bool>> Matrix::replaceWord(int num1, int num2, int num3, string function) {
	vector<bool> word1 = getWord(num1);
	vector<bool> word2 = getWord(num2);
	vector<bool> word3;
	if (function == "f7") { // дизъюнкция
		for (int i = 0; i < data[0].size(); i++) {
			if (word1[i] == word2[i] && word1[i] == 0) {
				word3.push_back(0);
			}
			else {
				word3.push_back(1);
			}
		}
	}
	else if (function == "f8") { // операция Пирса
		for (int i = 0; i < data[0].size(); i++) {
			if (word1[i] == word2[i] && word1[i] == 0) {
				word3.push_back(1);
			}
			else {
				word3.push_back(0);
			}
		}
	}
	else if (function == "f2") { // запрет первого аргумета 
		for (int i = 0; i < data[0].size(); i++) {
			if (word1[i] == 1 && word2[i] == 0) {
				word3.push_back(1);
			}
			else {
				word3.push_back(0);
			}
		}
	}
	else if (function == "f13") { // импликация от 1-го аргумента ко 2-му
		for (int i = 0; i < data[0].size(); i++) {
			if (word1[i] == 1 && word2[i] == 0) {
				word3.push_back(0);
			}
			else {
				word3.push_back(1);
			}
		}
	}
	else {
		return data;
	}
	for (int i = num3, count = num3; count < num3 + data[0].size(); i++, count++) {

		data[i][num3] = word3[count - num3];
		if (i == data[0].size() - 1) i = -1;
	}
	cout << "word1: ";
	printWord(word1);
	cout << "word2: ";
	printWord(word2);
	cout << "word3: ";
	printWord(word3);

	return data;
}

vector<vector<bool>> Matrix::summFields(vector<bool> v) {
	vector<bool> buff;
	vector<bool> a;
	vector<bool> b;
	vector<bool> s(5, 0);  // S должен иметь размер 5 бит

	for (int i = 0; i < data.size(); i++) {
		buff = getWord(i);
		// Проверяем, совпадают ли первые 3 бита слова с ключом V
		if (buff.size() < 11 || vector<bool>(buff.begin(), buff.begin() + 3) != v) {
			continue;
		}

		// Извлекаем поля A и B
		a.assign(buff.begin() + 3, buff.begin() + 7);
		b.assign(buff.begin() + 7, buff.begin() + 11);

		cout << "A: ";
		for (bool bit : a) cout << bit;
		cout << endl;

		cout << "B: ";
		for (bool bit : b) cout << bit;
		cout << endl;

		// Складываем A и B, результат записываем в S
		int carry = 0;
		for (int j = 3; j >= 0; j--) {
			int sum = a[j] + b[j] + carry;
			s[j + 1] = sum % 2;  // Записываем бит суммы
			carry = sum / 2;   // Переносим оставшийся бит
		}
		s[0] = carry;  // Записываем последний перенос

		cout << "S: ";
		for (bool bit : s) cout << bit;
		cout << endl;

		// Обновляем соответствующие 5 бит слова в матрице
		for (int l = 0; l < s.size(); l++) {
			data[i][(i + 4 - l) % data.size()] = s[l];
		}
		print();
	}
	return data;
}

int Matrix::binaryToDecimal(vector<bool> binary) {
	int decimal = 0;
	int size = binary.size();
	for (int i = 0; i < size; ++i) {
		if (binary[i]) {
			decimal += pow(2, size - 1 - i);
		}
	}
	return decimal;
}

vector<int> Matrix::searchInterval(int first, int second) {
	vector<int> interval;
	for (int i = 0; i < data.size(); i++) {
		int buff = binaryToDecimal(getWord(i));
		if (buff > first && buff < second) {
			interval.push_back(i);
		}
	}
	return interval;
}

void Matrix::print() {
	cout << "Matrix:" << endl;
	for (const auto& row : data) {
		for (bool val : row) {
			cout << (val ? 1 : 0) << " ";
		}
		cout << endl;
	}
	cout << endl;
}