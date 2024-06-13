#include "FloatingPoint.h"

void FloatingData::displayValue() {
    cout << "[" << sign << "] ";
    for (int i = 0; i < 8; i++) {
        cout << exponentBits[i] << " ";
    }
    cout << "| ";
    for (int i = 0; i < 23; i++) {
        cout << mantissa[i] << " ";
    }
    cout << " - num: " << value;
    cout << endl;
}

FloatingData::FloatingData(float num) {
    value = num;
    if (num == 0) {
        sign = 0;
        for (int i = 0; i < 8; i++) {
            exponentBits.push_back(0);
        }
        for (int i = 0; i < 23; i++) {
            mantissa.push_back(0);
        }
        exponent = 0;
        return;
    }
    if (num < 0) {
        num = -num;
    }
    int bitRemain = 1000;
    int integralNum = num;
    float remainderNum = num - integralNum;

    vector<bool> integral;
    vector<bool> remainder;

    if (num < 1) {
        integral.push_back(0);
    }
    int buffer = integralNum;
    while (abs(buffer) > 0) {
        int value = abs(buffer) % 2;
        integral.push_back(value);
        buffer /= 2;
    }
    reverse(integral.begin(), integral.end());

    for (int i = 0; i < bitRemain; ++i) {
        remainderNum *= 2;
        if (remainderNum >= 1) {
            remainder.push_back(1);
            remainderNum -= 1;
        }
        else {
            remainder.push_back(0);
        }
    }

    int n;
    if (abs(value) < 1 && abs(value) > 0) {
        if (value < 0) {
            sign = 1;
        }
        else {
            sign = 0;
        }
        n = -1;
        for (int i = 0; i < remainder.size() && remainder[i] != 1; i++) {
            n--;
        }
    }
    else if (value < 0) {
        n = integral.size() - 1;
        sign = 1;
    }
    else {
        n = integral.size() - 1;
        sign = 0;
    }
    if (n >= 0) {

        for (int i = 1; i < integral.size() && mantissa.size() < 23; i++) {
            mantissa.push_back(integral[i]);
        }
        for (int i = 0; i < remainder.size() - 1 && mantissa.size() < 23; i++) {
            mantissa.push_back(remainder[i]);
        }

    }

    else {
        for (int i = -n; i < bitRemain; i++) {
            mantissa.push_back(remainder[i]);
        }

    }
    exponent = 127 + n;
    buffer = exponent;
    while (abs(buffer) > 0) {
        int value = abs(buffer) % 2;
        exponentBits.push_back(value);
        buffer /= 2;
    }
    int size = exponentBits.size();
    for (int i = 0; i < 8 - size; i++) {
        exponentBits.push_back(0);
    }
    reverse(exponentBits.begin(), exponentBits.end());

}

FloatingData& FloatingData::operator =(const FloatingData& a) {
    value = a.value;
    sign = a.sign;
    exponent = a.exponent;
    mantissa = a.mantissa;
    exponentBits = a.exponentBits;
    return *this;
}

FloatingData FloatingData::operator +(const FloatingData& a) {

    FloatingData sum(0);
    if (sum.mantissa == mantissa && sum.exponentBits == exponentBits) {
        return a;
    }
    if (sum.mantissa == a.mantissa && sum.exponentBits == a.exponentBits) {
        return *this;

    }
    sum = a;
    vector<bool> mantissaLessNumber = a.mantissa;
    if (exponent > a.exponent) {
        sum = *this;
        mantissaLessNumber = a.mantissa;
    }
    else if (exponent == a.exponent) {
        for (int i = 0; i < 23; i++) {
            if (mantissa[i] == a.mantissa[i]) {
            }
            else if (mantissa[i] > a.mantissa[i]) {
                sum = *this;
                mantissaLessNumber = a.mantissa;
                break;
            }
            else {
                sum = a;
                mantissaLessNumber = mantissa;
                break;
            }
        }
    }
    else {
        sum = a;
        mantissaLessNumber = mantissa;
    }

    int n = abs(exponent - a.exponent);

    auto iter = sum.mantissa.cbegin();
    sum.mantissa.insert(iter, 1);
    iter = sum.mantissa.cbegin();
    sum.mantissa.insert(iter, 0);
    iter = mantissaLessNumber.cbegin();
    mantissaLessNumber.insert(iter, 1);

    iter = mantissaLessNumber.cbegin();

    mantissaLessNumber.insert(iter, n + 1, 0);

    int carry = 0;
    vector<bool> buffer = sum.mantissa;


    for (int i = 0; i < sum.mantissa.size(); i++) {

        if (i < mantissaLessNumber.size()) {
            if (mantissaLessNumber[i] + sum.mantissa[i] + carry == 0) {
                sum.mantissa[i] = 0;
                carry = 0;
            }
            else if (mantissaLessNumber[i] + sum.mantissa[i] + carry == 1) {
                sum.mantissa[i] = 1;
                carry = 0;
            }
            else if (mantissaLessNumber[i] + sum.mantissa[i] + carry == 2) {
                sum.mantissa[i] = 0;
                carry = 1;
            }
            else {
                sum.mantissa[i] = 1;
                carry = 1;
            }

        }
        else if (carry + sum.mantissa[i] == 0) {
            sum.mantissa[i] = 0;
            carry = 0;
        }
        else if (carry + sum.mantissa[i] == 1) {
            sum.mantissa[i] = 1;
            carry = 0;
        }
        else if (carry + sum.mantissa[i] == 2) {
            sum.mantissa[i] = 0;
            carry = 1;
        }
        else {
            sum.mantissa[i] = 1;
            carry = 1;
        }
    }
    carry = 0;

    for (int i = sum.mantissa.size() - 1; i >= 0; i--) {
        if (carry + sum.mantissa[i] == 0) {
            carry = 0;
        }
        else if (carry + sum.mantissa[i] == 1) {
            sum.mantissa[i] = 1;
            carry = 0;
        }
        else if (carry + sum.mantissa[i] == 2) {
            sum.mantissa[i] = 0;
            carry = 1;
        }
        else {
            sum.mantissa[i] = 1;
            carry = 1;
        }
    }

    n = 0;

    if (sum.mantissa[0] != 1) {
        if (carry == 1) {
            n = sum.exponent + 1;
        }
        else {
            n = sum.exponent;
        }
    }

    else {

        int s = sum.exponent;
        n = sum.exponent - 1;

        sum.sign = 0;

    }

    while (abs(n) > 0) {
        int value = abs(n) % 2;
        sum.exponentBits.push_back(value);
        n /= 2;
    }

    sum.exponent = 0;

    for (int i = 0; i < 8 - sum.exponentBits.size(); i++) {
        sum.exponentBits.push_back(0);
    }

    reverse(sum.exponentBits.begin(), sum.exponentBits.end());

    return sum;
}
