#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <regex>
using namespace std;

struct Quadruple {
    string op, arg1, arg2, result;
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void applyOperation(stack<string> &operands, stack<char> &operators, vector<Quadruple> &quadruples, int &tempCounter) {
    char op = operators.top(); operators.pop();
    string right = operands.top(); operands.pop();
    string left = operands.top(); operands.pop();
    string tempVar = "t" + to_string(tempCounter++);
    quadruples.push_back({string(1, op), left, right, tempVar});
    operands.push(tempVar);
}

string optimizeExpression(string expression) {
    regex tokenPattern("\\d+|[a-zA-Z]+|[+\\-*/()]");
    sregex_iterator iter(expression.begin(), expression.end(), tokenPattern);
    sregex_iterator end;
    vector<string> tokens;
    
    while (iter != end) {
        tokens.push_back(iter->str());
        ++iter;
    }

    stack<string> tempStack;
    for (const auto& token : tokens) {
        if (isdigit(token[0])) {
            tempStack.push(token);
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            while (tempStack.size() >= 2 && isdigit(tempStack.top()[0])) {
                string b = tempStack.top(); tempStack.pop();
                string a = tempStack.top(); tempStack.pop();
                int result = stoi(a) + stoi(b); // Simplified for demonstration
                tempStack.push(to_string(result));
            }
            tempStack.push(token);
        } else {
            tempStack.push(token);
        }
    }
    
    string optimizedExpr;
    while (!tempStack.empty()) {
        optimizedExpr = tempStack.top() + optimizedExpr;
        tempStack.pop();
    }
    return optimizedExpr;
}

vector<Quadruple> generateQuadruples(const string &expression) {
    vector<Quadruple> quadruples;
    stack<string> operands;
    stack<char> operators;
    istringstream ss(expression);
    string token;
    int tempCounter = 1;

    while (ss >> token) {
        if (isdigit(token[0]) || isalpha(token[0])) {
            operands.push(token);
        } else if (token == "(") {
            operators.push('(');
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != '(') {
                applyOperation(operands, operators, quadruples, tempCounter);
            }
            operators.pop();
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
                applyOperation(operands, operators, quadruples, tempCounter);
            }
            operators.push(token[0]);
        }
    }

    while (!operators.empty()) {
        applyOperation(operands, operators, quadruples, tempCounter);
    }

    return quadruples;
}

void displayQuadruples(const vector<Quadruple>& quadruples) {
    cout << "\nQuadruple Representation:" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "| Operator | Operand1 | Operand2 | Result  |" << endl;
    cout << "-------------------------------------------------" << endl;
    for (const auto &quad : quadruples) {
        cout << "| " << quad.op << "\t | " << quad.arg1 << "\t | " << quad.arg2 << "\t | " << quad.result << "\t |" << endl;
    }
    cout << "-------------------------------------------------" << endl;
}

int main() {
    string expression = "5 + x - 3 * 2";
    cout << "Original Expression: " << expression << endl;
    string optimizedExpression = optimizeExpression(expression);
    cout << "Optimized Expression: " << optimizedExpression << endl;
    vector<Quadruple> quadruples = generateQuadruples(optimizedExpression);
    displayQuadruples(quadruples);
    return 0;
}