#include <iostream>
#include <string>

using namespace std;

bool isPolyndrome(const string & str) {
    if (str.size() > 1) {
        int size = str.size() - 2;
        string newStr = str.substr(1, size);
        cout << "newStr = " << newStr << endl;
        return (str[0] == str[str.size()-1]) && isPolyndrome(newStr);
    }
    return true;
}

int fibonacci(int num) {
    if (num == 0) {
        return 0;
    } else if (num == 1) {
        return 1;
    }
    int f1 = fibonacci(num-1);
    int f2 = fibonacci(num-2);
    int f = f1 + f2;
    return f;
}

int fibonacciNum(int num) {
    if (num == 0) return 0;
    int fibprevprev = 0;
    int fibprev = 1;
    for (int i = 2; i < num; ++i) {
        int t = fibprev + fibprevprev;
        fibprevprev = fibprev;
        fibprev = t;
    }
    return fibprev + fibprevprev;
}

int factorialRec(int n) {
    if (n > 1)
        return n * factorialRec(n-1);
    return 1;
}

int factorialIt(int n) {
    int f = 1;
    for (int i = 2; i <= n; ++i) {
        f *= i;
    }
    return f;
}

int main()
{
//    const string polyndrome1 = "aabbaa";
//    const string polyndrome2 = "aabaa";
//    const string emptyString = "";
//    const string singleCharString = "a";
//    const string notPolyndrome1 = "abcdefg";
//    const string notPolyndrome2 = "abcdba";
//    cout << polyndrome1 << " polyndrome: " << isPolyndrome(polyndrome1) << endl;
//    cout << polyndrome2 << " polyndrome: " << isPolyndrome(polyndrome2) << endl;
//    cout << notPolyndrome1 << " polyndrome: " << isPolyndrome(notPolyndrome1) << endl;
//    cout << notPolyndrome2 << " polyndrome: " << isPolyndrome(notPolyndrome2) << endl;
//    cout << emptyString << " polyndrome: " << isPolyndrome(emptyString) << endl;
//    cout << singleCharString << " polyndrome: " << isPolyndrome(singleCharString) << endl;

    const int f1 = 0;
    const int f2 = 1;
    const int f3 = 2;
    const int f4 = 6;

    cout << "fibonacci of " << f1 << ": " << fibonacciNum(f1) << endl;
    cout << "fibonacci of " << f2 << ": " << fibonacciNum(f2) << endl;
    cout << "fibonacci of " << f3 << ": " << fibonacciNum(f3) << endl;
    cout << "fibonacci of " << f4 << ": " << fibonacciNum(f4) << endl;

//    const int f1 = 0;
//    const int f2 = 1;
//    const int f3 = 2;
//    const int f4 = 10;

//    cout << "factorial of " << f1 << ": " << factorialIt(f1) << endl;
//    cout << "factorial of " << f2 << ": " << factorialIt(f2) << endl;
//    cout << "factorial of " << f3 << ": " << factorialIt(f3) << endl;
//    cout << "factorial of " << f4 << ": " << factorialIt(f4) << endl;

    return 0;
}
