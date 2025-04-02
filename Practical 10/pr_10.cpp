#include <iostream>
#include <sstream>
#include <stack>
#include <cmath>
#include <map>
#include <vector>
#include <cctype>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

double evaluateExpression(const string& expression) {
    stack<double> values;
    stack<char> operators;
    istringstream ss(expression);
    string token;
    
    while (ss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
            values.push(stod(token));
        } else if (token == "(") {
            operators.push('(');
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperation(a, b, op));
            }
            operators.pop(); 
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperation(a, b, op));
            }
            operators.push(token[0]);
        }
    }
    
    while (!operators.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperation(a, b, op));
    }
    
    return values.top();
}

int main() {
    vector<string> expressions = {
        "( 3 + 5 ) * 2 ^ 3",
        "3 + 5 * 2",
        "3 + 5 * 2 ^ 2",
        "3 + ( 5 * 2 )",
        "3 + 5 ^ 2 * 2",
        "3 * ( 5 + 2 )",
        "( 3 + 5 ) ^ 2",
        "3 ^ 2 * 3",
        "3 ^ 2 + 5 * 2",
        "( 3 + 5 * 2 ^ 2 - 8 ) / 4 ^ 2 + 6"
    };
    
    for (const string& expr : expressions) {
        cout << "Expression: " << expr << " -> Result: " << evaluateExpression(expr) << endl;
    }
    return 0;
}
