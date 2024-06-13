#include "header.h"

int main() {
    int n1, n2;
    cout << "Enter the first num: ";
    cin >> n1;
    IntNum num1(n1);

    num1.printValue();
    cout << "\nEnter the second num: ";
    cin >> n2;
    IntNum num2(n2);
    num2.printValue();

    IntNum num3(0);

    cout << "\nsum:" << endl;
    num3 = num1 + num2;
    num3.printValue();

    cout << "\nmultiplication:" << endl;
    num3 = num1 * num2;
    num3.printValue();

    cout << "\ndivision:" << endl;
    FixedPoint num = num1 / num2;
    num.print();

    float n4;
    cout << "\nEnter the floating point number1:  ";
    cin >> n4;
    FloatingPoint num4(n4);
    float n5;
    cout << "Enter the floating point number2:  ";
    cin >> n5;
    cout << endl;
    FloatingPoint num5(n5);
    num4.printValue();
    num5.printValue();
    cout << "\nsum:\n";
    FloatingPoint num6 = num4 + num5;
    num6.printValue();

    return 0;
}