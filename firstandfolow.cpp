#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
using namespace std;

// Production rules (hardcoded for this grammar)
map<char, vector<string>> productions = {
    {'S', {"ABC", "D"}},
    {'A', {"a", "#"}},   // # denotes epsilon
    {'B', {"b", "#"}},
    {'C', {"(S)", "c"}},
    {'D', {"AC"}}
};

map<char, set<char>> firstSet;
map<char, set<char>> followSet;

bool isNonTerminal(char symbol) {
    return symbol >= 'A' && symbol <= 'Z';
}

void computeFirst(char symbol);

// Compute FIRST set for a symbol
void computeFirst(char symbol) {
    // Already computed
    if (!firstSet[symbol].empty())
        return;

    for (string prod : productions[symbol]) {
        for (int i = 0; i < prod.size(); ++i) {
            char ch = prod[i];

            // Terminal
            if (!isNonTerminal(ch)) {
                firstSet[symbol].insert(ch);
                break;
            }

            // Non-terminal
            computeFirst(ch);
            bool epsilonFound = false;

            for (char f : firstSet[ch]) {
                if (f == '#') epsilonFound = true;
                else firstSet[symbol].insert(f);
            }

            if (!epsilonFound)
                break;

            // If ε and it's the last symbol, add ε to FIRST
            if (i == prod.size() - 1)
                firstSet[symbol].insert('#');
        }
    }
}

// Compute FOLLOW set for a non-terminal
void computeFollow(char symbol) {
    for (auto& rule : productions) {
        char lhs = rule.first;
        for (string prod : rule.second) {
            for (int i = 0; i < prod.size(); ++i) {
                if (prod[i] == symbol) {
                    // Case 1: next symbol exists
                    if (i + 1 < prod.size()) {
                        char next = prod[i + 1];
                        if (!isNonTerminal(next)) {
                            followSet[symbol].insert(next);
                        } else {
                            for (char f : firstSet[next]) {
                                if (f != '#') followSet[symbol].insert(f);
                            }
                            if (firstSet[next].count('#')) {
                                for (char f : followSet[lhs]) {
                                    followSet[symbol].insert(f);
                                }
                            }
                        }
                    } else {
                        // Case 2: at end, add FOLLOW of LHS
                        if (symbol != lhs) {
                            for (char f : followSet[lhs]) {
                                followSet[symbol].insert(f);
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Step 1: Compute FIRST sets
    for (auto& prod : productions) {
        computeFirst(prod.first);
    }

    // Step 2: Initialize FOLLOW(S) = $
    followSet['S'].insert('$');

    // Step 3: Compute FOLLOW sets
    for (int i = 0; i < 3; ++i) { // Iterate multiple times for stable FOLLOW
        for (auto& prod : productions) {
            computeFollow(prod.first);
        }
    }

    // Display FIRST sets
    cout << "First sets:\n";
    for (auto& p : firstSet) {
        cout << "First(" << p.first << ") = {";
        bool first = true;
        for (char c : p.second) {
            if (!first) cout << ", ";
            cout << c;
            first = false;
        }
        cout << "}\n";
    }

    // Display FOLLOW sets
    cout << "\nFollow sets:\n";
    for (auto& p : followSet) {
        cout << "Follow(" << p.first << ") = {";
        bool first = true;
        for (char c : p.second) {
            if (!first) cout << ", ";
            cout << c;
            first = false;
        }
        cout << "}\n";
    }

    return 0;
}
