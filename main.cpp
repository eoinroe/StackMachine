#include <iostream>
#include <stack>
#include <unordered_map>
#include <set>

// Writing out all the key value pairs in the map by hand means there is
// a bit more code, however, it also makes it very easy to understand.
const std::unordered_map<char, unsigned short> digits = {
        {'0', 0},
        {'1', 1},
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9}
};

int solution(std::string& str)
/*
 * A stack machine is a simple system that performs arithmetic
 * operations on an input string of numbers and operators.
 */
{
    // Check that the string only contains the following characters.
    const std::set<char> characters = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '*'};

    for (auto& ch : str) {
        // set::find returns an iterator to the element, if val is found...
        auto it = characters.find(ch);

        // or set::end otherwise.
        if (it == characters.end()) {
            std::cout << "The string contains an invalid character." << std::endl;
            return -1;
        }
    }

    // It contains a stack that can store an arbitrary number of
    // 12-bit unsigned integers. In C++ the closest type to a 12
    // -bit unsigned integer is an unsigned short (16 bits).
    std::stack<unsigned short> stack;

    /*

    std::unordered_map<char, unsigned short> numbers;

    // https://en.cppreference.com/w/cpp/language/ascii
    for (char c{'0'}; c <= '9'; c++) {
        // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
        unsigned short n = c - '0';
        numbers[c] = n;
    }

     */

    // The characters are processed one by one.
    for (auto& ch : str) {
        // If the current character is a digit ('0'-'9') the machine
        // pushes the value of that digit onto its stack.
        if (digits.count(ch)) {
            // Could also use map::find and check the iterator != map.end().
            // stack.push(digits[ch]);

            // Need to use map::at if the map is const.
            stack.push(digits.at(ch));

            // If a digit has been found skip the remaining
            // portion of the range-for loop.
            continue;
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
    // Initialize const map using lambda.
    const std::unordered_map<char, unsigned short> map = []() {
        std::unordered_map<char, unsigned short> temp;

        for (char c{'0'}; c <= '9'; c++) {
            temp.emplace(c, c - '0');
        }

        return temp;
    }();

    for (auto& [key, value] : map)
        std::cout << key << std::endl;

    std::string characters = "13+62*7+*";
    // std::string characters = "11++";

    // TODO: Add unit tests
    auto result = solution(characters);
    std::cout << "Result: " << result;

    return 0;
}
