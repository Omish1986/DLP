#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>

using namespace std;

void computeFirstSets(map<string, set<string>> &firstSets, const map<string, vector<string>> &productions)
{
    bool changed;
    do
    {
        changed = false;

        for (const auto &rule : productions)
        {
            string nonTerminal = rule.first;

            for (const string &production : rule.second)
            {
                for (char ch : production)
                {
                    string symbol(1, ch);

                    if (!isupper(ch))
                    {
                        if (firstSets[nonTerminal].find(symbol) == firstSets[nonTerminal].end())
                        {
                            firstSets[nonTerminal].insert(symbol);
                            changed = true;
                        }
                        break;
                    }

                    else
                    {

                        if (firstSets[symbol].find("ε") != firstSets[symbol].end())
                        {
                            if (firstSets[nonTerminal].find("ε") == firstSets[nonTerminal].end())
                            {
                                firstSets[nonTerminal].insert("ε");
                                changed = true;
                            }
                            continue;
                        }
                        else
                        {
                            for (const string &terminal : firstSets[symbol])
                            {
                                if (firstSets[nonTerminal].find(terminal) == firstSets[nonTerminal].end())
                                {
                                    firstSets[nonTerminal].insert(terminal);
                                    changed = true;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    } while (changed);
}

void computeFollowSets(map<string, set<string>> &followSets, const map<string, vector<string>> &productions, const map<string, set<string>> &firstSets)
{
    bool changed;
    followSets["S"].insert("$");

    do
    {
        changed = false;

        for (const auto &rule : productions)
        {
            string nonTerminal = rule.first;

            for (const string &production : rule.second)
            {
                set<string> nextFollow;

                for (int i = production.size() - 1; i >= 0; --i)
                {
                    string symbol(1, production[i]);

                    if (isupper(symbol[0]))
                    {

                        for (const string &terminal : nextFollow)
                        {
                            if (followSets[symbol].find(terminal) == followSets[symbol].end())
                            {
                                followSets[symbol].insert(terminal);
                                changed = true;
                            }
                        }

                        if (firstSets.at(symbol).find("ε") != firstSets.at(symbol).end())
                        {
                            nextFollow.insert(followSets[nonTerminal].begin(), followSets[nonTerminal].end());
                        }
                        else
                        {
                            nextFollow.clear();
                            nextFollow.insert(firstSets.at(symbol).begin(), firstSets.at(symbol).end());
                        }
                    }
                    else
                    {

                        nextFollow.clear();
                        nextFollow.insert(symbol);
                    }
                }
            }
        }
    } while (changed);
}

int main()
{
    map<string, vector<string>> productions = {
        {"S", {"A B C", "D"}},
        {"A", {"a", "ε"}},
        {"B", {"b", "ε"}},
        {"C", {"( S )", "c"}},
        {"D", {"A C"}}};

    map<string, set<string>> firstSets;
    map<string, set<string>> followSets;

    for (const auto &rule : productions)
    {
        firstSets[rule.first];
    }

    computeFirstSets(firstSets, productions);
    computeFollowSets(followSets, productions, firstSets);

    cout << "First Sets:" << endl;
    for (const auto &pair : firstSets)
    {
        cout << "First(" << pair.first << ") = { ";
        for (const string &terminal : pair.second)
        {
            cout << terminal << " ";
        }
        cout << "}" << endl;
    }

    cout << "\nFollow Sets:" << endl;
    for (const auto &pair : followSets)
    {
        cout << "Follow(" << pair.first << ") = { ";
        for (const string &terminal : pair.second)
        {
            cout << terminal << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}
