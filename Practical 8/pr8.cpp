#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <stack>

using namespace std;


set<char> getFirstOfProduction(const string& production, map<char, set<char>>& firstSets) {
    set<char> first;
    for (char symbol : production) {
        if (firstSets.find(symbol) != firstSets.end()) {
            first.insert(firstSets[symbol].begin(), firstSets[symbol].end());
            first.erase('ε');
            if (firstSets[symbol].find('ε') == firstSets[symbol].end()) {
                break;
            }
        } else {
            first.insert(symbol);
            break;
        }
    }
    return first;
}


map<char, map<char, string>> constructParsingTable(map<char, vector<string>>& grammar, map<char, set<char>>& firstSets, map<char, set<char>>& followSets, bool &isLL1) {
    map<char, map<char, string>> parsingTable;
    isLL1 = true;
    
    for (const auto& rule : grammar) {
        char nonTerminal = rule.first;
        for (const string& production : rule.second) {
            set<char> firstSet = getFirstOfProduction(production, firstSets);
            for (char terminal : firstSet) {
                if (terminal != 'ε') {
                    if (!parsingTable[nonTerminal][terminal].empty()) {
                        isLL1 = false;
                    }
                    parsingTable[nonTerminal][terminal] = production;
                }
            }
            if (firstSet.find('ε') != firstSet.end()) {
                for (char terminal : followSets[nonTerminal]) {
                    if (!parsingTable[nonTerminal][terminal].empty()) {
                        isLL1 = false;
                    }
                    parsingTable[nonTerminal][terminal] = "ε";
                }
            }
        }
    }
    return parsingTable;
}


string parseString(map<char, map<char, string>>& parsingTable, char startSymbol, const string& input) {
    stack<char> parseStack;
    parseStack.push('$');
    parseStack.push(startSymbol);
    string augmentedInput = input + "$";
    size_t index = 0;
    
    while (!parseStack.empty()) {
        char top = parseStack.top();
        parseStack.pop();
        if (top == augmentedInput[index]) {
            index++;
        } else if (parsingTable.count(top) && parsingTable[top].count(augmentedInput[index])) {
            string production = parsingTable[top][augmentedInput[index]];
            if (production != "ε") {
                for (auto it = production.rbegin(); it != production.rend(); ++it) {
                    parseStack.push(*it);
                }
            }
        } else {
            return "Invalid string";
        }
    }
    return (index == augmentedInput.length()) ? "Valid string" : "Invalid string";
}

int main() {
   
    map<char, vector<string>> grammar = {
        {'S', {"abc", "ac", "(abc)", "c", "(ac)"}},
        {'A', {"a", "()", "(ab)", "abcabc", "b"}}
    };
    
  
    map<char, set<char>> firstSets = {
        {'S', {'a', '(', 'c'}},
        {'A', {'a', '(', 'b'}}
    };
    
   
    map<char, set<char>> followSets = {
        {'S', {'$', ')'}},
        {'A', {'$', ')'}}
    };
    
    bool isLL1;
    map<char, map<char, string>> parsingTable = constructParsingTable(grammar, firstSets, followSets, isLL1);
    
    
    cout << "Predictive Parsing Table:\n";
    for (const auto& row : parsingTable) {
        cout << row.first << " : ";
        for (const auto& col : row.second) {
            cout << "(" << col.first << " -> " << col.second << ") ";
        }
        cout << endl;
    }
    
    cout << "\nGrammar is " << (isLL1 ? "LL(1)" : "NOT LL(1)") << "\n";
    
    
    string inputString = "ac";
    cout << "\nValidation Result: " << parseString(parsingTable, 'S', inputString) << endl;
    
    return 0;
}