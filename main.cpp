#include <iostream>
#include <stack>
#include <unordered_map>

int solution(std::string& str)
/*
 * A stack machine is a simple system that performs arithmetic
 * operations on an input string of numbers and operators.
 */
{
    // TODO: Include check that makes sure the string only contains the following characters.
    // char characters [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '*'};

    // It contains a stack that can store an arbitrary number of
    // 12-bit unsigned integers. In C++ the closest type to a 12
    // -bit unsigned integer is an unsigned short (16 bits).
    std::stack<unsigned short> stack;

    std::unordered_map<char, unsigned short> numbers;

    unsigned short n = 0;
    for (char c{'0'}; c <= '9'; c++) {
        numbers[c] = n++;
    }

    /*
     * https://en.cppreference.com/w/cpp/language/ascii
    for (char c{'0'}; c <= '9'; c++) {
        std::cout << numbers[c] << std::endl;
    }
     */

    // The characters are processed one by one.
    for (auto& ch : str) {
        // If the current character is a digit ('0'-'9') the machine
        // pushes the value of that digit onto its stack.
        if (numbers.count(ch)) {
            // Could also use map::find and check the iterator != map.end().
            stack.push(numbers[ch]);
        }

        // Can only perform addition or multiplication if the size of
        // the stack is larger than 1 (i.e. there must be two numbers
        // in the stack that you can add or multiply together).
        if (stack.size() <= 1 && (ch == '+' || ch == '*'))
            return -1;

        // If the current character is '+'...
        if (ch == '+') {
            // the machine pops the two topmost values from the stack...
            unsigned short a = stack.top();
            stack.pop();

            unsigned short b = stack.top();
            stack.pop();

            // adds them and pushes the result onto the stack.
            stack.push(a + b);
        }

        if (ch == '*') {
            unsigned short a = stack.top();
            stack.pop();

            unsigned short b = stack.top();
            stack.pop();

            stack.push(a * b);
        }

        // if (ch == '+' || ch == '*') {
        //     if (stack.size() <= 1)
        //         return -1;
        //
        //     unsigned short a = stack.top();
        //     stack.pop();
        //
        //     unsigned short b = stack.top();
        //     stack.pop();
        //
        //     if (ch == '+') {
        //         stack.push(a + b);
        //     }
        //
        //     if (ch == '*') {
        //         stack.push(a * b);
        //     }
        // }
    }

    return stack.top();
}

int main() {
    // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
    char ch = '7';
    unsigned short i = ch - '0';

    std::cout << "Converted char: " << i << std::endl;

    std::string characters = "13+62*7+*";
    // std::string characters = "11++";

    // TODO: Add unit tests
    std::cout << "Result: " << solution(characters);

    return 0;
}
