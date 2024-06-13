#include "IntNum.h"

int IntNum::getBitsCount() {
	return bitsCount;
}
void IntNum::setBitsCount(int value) {
	bitsCount = value;
	IntNum p(num);
	directCode = p.directCode;
	invertCode = p.invertCode;
	additionalCode = p.additionalCode;
}

IntNum::IntNum(int num) {
	int buff = num;
	this->num = num;
	while (abs(buff) > 0) {
		int value = abs(buff) % 2;
		directCode.push_back(value);
		buff /= 2;
	}
	int size = directCode.size();
	for (int i = 0; i < bitsCount - size - 1; i++) {
		directCode.push_back(0);
	}
	if (num >= 0) {
		directCode.push_back(0);
	}
	else {
		directCode.push_back(1);
	}
	reverse(directCode.begin(), directCode.end());
	if (num >= 0) {
		invertCode = directCode;
		additionalCode = directCode;
	}
	else {
		invertCode = directCode;
		for (int i = 1; i < directCode.size(); i++) {
			invertCode[i] = invertCode[i] - 1;
		}
		additionalCode = invertCode;
		for (int i = additionalCode.size() - 1; i != 0; i--) {
			if (additionalCode[i] == 0) {
				additionalCode[i] = 1;
				break;
			}
			else {
				additionalCode[i] = 0;
			}
		}
	}

}

void IntNum::printValue() {
	cout << "\nIntNum: " << num << endl;
	cout << "\nBynaryNum: " << endl;
	cout << "Direct code: ";
	for (int i = 0; i < directCode.size(); i++) {
		cout << directCode[i] << " ";
	}
	cout << "\nReturn code: ";
	for (int i = 0; i < invertCode.size(); i++) {
		cout << invertCode[i] << " ";
	}
	cout << "\nAdded  code: ";
	for (int i = 0; i < additionalCode.size(); i++) {
		cout << additionalCode[i] << " ";
	}
	cout << endl;
}

bool IntNum::compareBinary(string first, string second) {
	return abs(binaryToDecimal(first)) > abs(binaryToDecimal(second));
}

int IntNum::binaryToDecimal(string directCode) {
	char symbol = directCode[0];
	directCode.erase(0, 1);
	int result = 0;
	reverse(directCode.begin(), directCode.end());
	for (int i = 0; i <= directCode.size() - 1; i++)
		result += (directCode[i] - '0') * pow(2, i);
	result = symbol == '0' ? result : (-1 * result);
	return result;
}

string IntNum::decimalToBinary(int num) {
	string result = "0";
	int dividual = num < 0 ? (-1 * num) : num, remain;
	while (dividual != 1 && dividual != 0)
	{
		remain = dividual % 2;
		result += remain + '0';
		dividual /= 2;
	}
	result += dividual + '0';
	result.erase(0, 1);
	remain = num < 0 ? 1 : 0;
	result += remain + '0';
	reverse(result.begin(), result.end());
	return result;
}

IntNum& IntNum::operator =(const IntNum& a) {
	if (bitsCount != a.bitsCount) {
		throw runtime_error("Bites count error");
	}
	this->directCode = a.directCode;
	this->invertCode = a.invertCode;
	this->additionalCode = a.additionalCode;
	num = a.num;
	return *this;
}

IntNum IntNum::operator +(const IntNum& a) {
	if (bitsCount != a.bitsCount) {
		throw runtime_error("Bites count error");
	}
	IntNum sum(0);

	int carry;
	if (!(num >= 0 && a.num >= 0)) carry = 1;
	else { carry = 0; }

	for (int i = additionalCode.size() - 1; i >= 0; i--) {
		int bit1 = additionalCode[i];
		int bit2 = a.additionalCode[i];

		int sumBit = bit1 + bit2 + carry;
		if (sumBit % 2 == 0) {
			sum.additionalCode[i] = 0;
		}
		else {
			sum.additionalCode[i] = 1;
		}
		carry = sumBit / 2;
	}
	if (num + a.num == -1) {
		sum.additionalCode[0] = 1;
	}
	if (!(num >= 0 && a.num >= 0)) {
		for (int i = sum.additionalCode.size() - 1; i > 0; i--) {
			if (sum.additionalCode[i] == 1) {
				sum.additionalCode[i] = 0;
				break;
			}
			else {
				sum.additionalCode[i] = 1;
			}
		}
	}

	if (sum.additionalCode[0] == 0) {
		sum.directCode = sum.additionalCode;
		sum.invertCode = sum.additionalCode;
	}
	else {
		sum.invertCode = sum.additionalCode;
		for (int i = sum.invertCode.size() - 1; i > 0; i--) {
			if (sum.invertCode[i] == 1) {
				sum.invertCode[i] = 0;
				break;
			}
			else {
				sum.invertCode[i] = 1;
			}
		}
		sum.directCode = sum.invertCode;
		for (int i = 1; i < sum.directCode.size(); i++) {
			sum.directCode[i] = sum.directCode[i] - 1;
		}
	}

	int base = 1;
	      
	for (int i = sum.directCode.size() - 1; i > 0; --i) {
		if (sum.directCode[i]) {
			sum.num += base;
		}
		base *= 2;
	}
	if (sum.directCode[0] == 1) {
		sum.num = -sum.num;
	}
	return sum;
}

IntNum IntNum::operator *(const IntNum& a) {

	if (bitsCount != a.bitsCount) {
		throw runtime_error("Bites count error");
	}
	IntNum mult(0);

	for (int i = bitsCount / 2 - 1; i >= 0; i--) {
		int carry = 0;

		for (int j = bitsCount / 2 - 1; j >= 0; j--) {
			int pos = i + j + 1;
			int product = mult.directCode[pos] + directCode[i + bitsCount / 2] * a.directCode[j + bitsCount / 2] + carry;
			mult.directCode[pos] = product % 2;
			carry = product / 2;
		}

		mult.directCode[i] = carry;
	}
	if (a.num * num < 0) {
		mult.directCode[0] = 1;
		mult.invertCode = mult.directCode;
		for (int i = 1; i < mult.directCode.size(); i++) {
			mult.invertCode[i] = mult.invertCode[i] - 1;
		}
		mult.additionalCode = mult.invertCode;
		for (int i = mult.additionalCode.size() - 1; i != 0; i--) {
			if (mult.additionalCode[i] == 0) {
				mult.additionalCode[i] = 1;
				break;
			}
			else {
				mult.additionalCode[i] = 0;
			}
		}
	}
	else {
		mult.invertCode = mult.directCode;
		mult.additionalCode = mult.directCode;
	}
	int base = 1;
	for (int i = mult.directCode.size() - 1; i > 0; --i) {
		if (mult.directCode[i]) {
			mult.num += base;
		}
		base *= 2;
	}
	if (mult.directCode[0] == 1) {
		mult.num = -mult.num;
	}
	return mult;
}

FixedPoint IntNum::operator/(const IntNum& a) {
	if (bitsCount != a.bitsCount) {
		throw runtime_error("Error in bites");
	}
	FixedPoint div;

	int size = 0;
	for (int i = 1; i < bitsCount; i++) {
		if (directCode[i] == 1) {
			break;
		}
		size++;
	}
	vector<bool> num1;
	if (num > 0) {
		num1.push_back(0);
	}
	else if (num < 0) {
		num1.push_back(1);
	}

	for (int i = 1 + size; i < bitsCount; i++) {
		num1.push_back(directCode[i]);
	}

	size = 0;
	for (int i = 1; i < bitsCount; i++) {
		if (a.directCode[i] == 1) {
			break;
		}
		size++;
	}
	vector<bool> num2;
	if (a.num > 0) {
		num2.push_back(0);
	}
	else if (a.num < 0) {
		num2.push_back(1);
	}

	for (int i = 1 + size; i < bitsCount; i++) {
		num2.push_back(a.directCode[i]);
	}
	if (num1.empty()) {
		num1.push_back(0);
	}
	if (num2.empty()) {
		num2.push_back(0);
	}

	if (num == 0 && a.num != 0) {
		div.integ.push_back(0);
		div.remain.push_back(0);
		return div;
	}
	if (a.num == 0) {
		throw runtime_error("Error in division by zero");
	}

	string dividualNum;
	for (bool num : num1) {
		dividualNum += num ? '1' : '0';
	}
	string divisorNum;
	for (bool num : num2) {
		divisorNum += num ? '1' : '0';
	}

	string divisionResInt, divisionResFloat, toDivision;
	char symbol_result = dividualNum[0] == divisorNum[0] ? '0' : '1', element;
	divisionResInt.insert(0, 1, symbol_result);

	dividualNum.erase(0, 1);
	divisorNum.erase(0, 1);
	toDivision = dividualNum.substr(0, divisorNum.size() - 1);
	for (int i = divisorNum.size() - 1; i < dividualNum.size(); i++)
	{
		toDivision += dividualNum[i];
		element = compareBinary(toDivision.insert(0, 1, '0'), divisorNum.insert(0, 1, '0')) ? '1' :
			abs(binaryToDecimal(toDivision.insert(0, 1, '0'))) == abs(binaryToDecimal(divisorNum.insert(0, 1, '0'))) ? '1' : '0';
		divisionResInt += element;
		if (element == '1')
		{
			toDivision = decimalToBinary(binaryToDecimal(toDivision.insert(0, 1, '0')) - binaryToDecimal(divisorNum.insert(0, 1, '0')));
			toDivision.erase(0, 1);
		}
	}
	if (binaryToDecimal(toDivision.insert(0, 1, '0')) != 0)
	{
		divisionResFloat = "0";
		while (binaryToDecimal(toDivision.insert(0, 1, '0')) != 0 && divisionResFloat.size() <= 5)
		{
			toDivision += '0';
			element = compareBinary(toDivision.insert(0, 1, '0'), divisorNum.insert(0, 1, '0')) ? '1' :
				abs(binaryToDecimal(toDivision.insert(0, 1, '0'))) == abs(binaryToDecimal(divisorNum.insert(0, 1, '0'))) ? '1' : '0';
			divisionResFloat += element;
			if (element == '1')
			{
				toDivision = decimalToBinary(binaryToDecimal(toDivision.insert(0, 1, '0')) - binaryToDecimal(divisorNum.insert(0, 1, '0')));
				toDivision.erase(0, 1);
			}
		}
		divisionResFloat.erase(0, 1);
	}
	else {
		divisionResFloat = "0";
	}

	for (char bit : divisionResInt) {
		div.integ.push_back(bit == '1');
	}

	for (char bit : divisionResFloat) {
		div.remain.push_back(bit == '1');
	}
	return div;
}