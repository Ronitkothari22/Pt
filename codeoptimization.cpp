#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <cmath>
#include <vector>
#include <string>
#include <map>
using namespace std;

// Function to determine operator precedence
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Check if string is a number
bool isNumber(const string& s) {
    for (char ch : s)
        if (!isdigit(ch) && ch != '.') return false;
    return !s.empty();
}

// Apply operation to two values
string applyOp(string a, string b, char op) {
    double val1 = stod(a);
    double val2 = stod(b);
    double result;

    switch (op) {
        case '+': result = val1 + val2; break;
        case '-': result = val1 - val2; break;
        case '*': result = val1 * val2; break;
        case '/': result = val1 / val2; break;
        case '^': result = pow(val1, val2); break;
        default: return a + op + b;
    }

    // Convert back to string
    ostringstream oss;
    oss << result;
    return oss.str();
}

// Convert infix to postfix
vector<string> infixToPostfix(const string& expr) {
    vector<string> output;
    stack<char> operators;
    string token;

    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];
        if (isspace(ch)) continue;

        if (isdigit(ch) || isalpha(ch) || ch == '.') {
            token += ch;
        } else {
            if (!token.empty()) {
                output.push_back(token);
                token.clear();
            }

            if (ch == '(') {
                operators.push(ch);
            } else if (ch == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    output.push_back(string(1, operators.top()));
                    operators.pop();
                }
                if (!operators.empty()) operators.pop();
            } else {
                while (!operators.empty() &&
                       precedence(operators.top()) >= precedence(ch)) {
                    output.push_back(string(1, operators.top()));
                    operators.pop();
                }
                operators.push(ch);
            }
        }
    }

    if (!token.empty()) output.push_back(token);
    while (!operators.empty()) {
        output.push_back(string(1, operators.top()));
        operators.pop();
    }

    return output;
}

// Optimize expression using constant folding
string constantFolding(const string& expr) {
    vector<string> postfix = infixToPostfix(expr);
    stack<string> s;

    for (const string& token : postfix) {
        if (isNumber(token)) {
            s.push(token);
        } else if (isalpha(token[0])) {
            s.push(token);
        } else {
            string b = s.top(); s.pop();
            string a = s.top(); s.pop();

            if (isNumber(a) && isNumber(b)) {
                s.push(applyOp(a, b, token[0]));
            } else {
                s.push(a + " " + b + " " + token);
            }
        }
    }

    return s.top();
}

// ---------- MAIN -------------
int main() {
    string input;
    cout << "Enter expression: ";
    getline(cin, input);

    string optimized = constantFolding(input);
    cout << "Optimized expression: " << optimized << endl;

    return 0;
}
