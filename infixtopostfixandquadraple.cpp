#include <iostream>
#include <stack>
#include <vector>
#include <cctype>
#include <sstream>
#include <iomanip>

using namespace std;

struct Quadruple {
    string op, arg1, arg2, result;
};

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

vector<string> infixToPostfix(const string& expr) {
    vector<string> output;
    stack<char> operators;
    string number;

    for (size_t i = 0; i < expr.size(); ++i) {
        char ch = expr[i];
        if (isspace(ch)) continue;

        if (isdigit(ch)) {
            number += ch;
        } else {
            if (!number.empty()) {
                output.push_back(number);
                number.clear();
            }

            if (ch == '(') {
                operators.push(ch);
            } else if (ch == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    output.push_back(string(1, operators.top()));
                    operators.pop();
                }
                if (!operators.empty()) operators.pop(); // remove '('
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

    if (!number.empty()) output.push_back(number);

    while (!operators.empty()) {
        output.push_back(string(1, operators.top()));
        operators.pop();
    }

    return output;
}

vector<Quadruple> generateQuadruples(const vector<string>& postfix) {
    vector<Quadruple> quads;
    stack<string> st;
    int tempCount = 1;

    for (const string& token : postfix) {
        if (isdigit(token[0])) {
            st.push(token);
        } else {
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();
            string temp = "t" + to_string(tempCount++);

            quads.push_back({token, a, b, temp});
            st.push(temp);
        }
    }

    return quads;
}

void printQuadruples(const vector<Quadruple>& quads) {
    cout << left << setw(10) << "Operator" 
         << setw(10) << "Operand 1" 
         << setw(10) << "Operand 2" 
         << setw(10) << "Result" << endl;

    for (const auto& q : quads) {
        cout << left << setw(10) << q.op 
             << setw(10) << q.arg1 
             << setw(10) << q.arg2 
             << setw(10) << q.result << endl;
    }
}

int main() {
    string expr;
    cout << "Enter arithmetic expression: ";
    getline(cin, expr);

    try {
        vector<string> postfix = infixToPostfix(expr);
        vector<Quadruple> quads = generateQuadruples(postfix);
        printQuadruples(quads);
    } catch (const exception& e) {
        cout << "Invalid expression: " << e.what() << endl;
    }

    return 0;
}
