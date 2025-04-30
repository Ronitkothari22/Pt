#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> firstSet, followSet;
map<pair<char, char>, string> parsingTable;
set<char> terminals, nonTerminals;

void initializeGrammar() {
    grammar['S'] = {"ABC", "D"};
    grammar['A'] = {"a", "#"};
    grammar['B'] = {"b", "#"};
    grammar['C'] = {"(S)", "c"};
    grammar['D'] = {"AC"};

    nonTerminals = {'S', 'A', 'B', 'C', 'D'};
    terminals = {'a', 'b', '(', ')', 'c', '$'};
}

void initializeFirstFollow() {
    firstSet['A'] = {'a', '#'};
    firstSet['B'] = {'b', '#'};
    firstSet['C'] = {'(', 'c'};
    firstSet['D'] = {'a', '(', 'c'};
    firstSet['S'] = {'a', 'b', '(', 'c'};

    followSet['S'] = {')', '$'};
    followSet['A'] = {'b', '(', 'c'};
    followSet['B'] = {'(', 'c'};
    followSet['C'] = {')', '$'};
    followSet['D'] = {')', '$'};
}

set<char> getFirstOfString(string str) {
    set<char> result;
    bool allNullable = true;
    for (char sym : str) {
        if (terminals.count(sym)) {
            result.insert(sym);
            allNullable = false;
            break;
        }

        for (char ch : firstSet[sym]) {
            if (ch != '#') result.insert(ch);
        }

        if (firstSet[sym].count('#') == 0) {
            allNullable = false;
            break;
        }
    }

    if (allNullable) result.insert('#');
    return result;
}

void constructParsingTable() {
    for (auto &[nt, prods] : grammar) {
        for (string prod : prods) {
            set<char> firsts = getFirstOfString(prod);
            for (char term : firsts) {
                if (term != '#') {
                    parsingTable[{nt, term}] = prod;
                }
            }

            if (firsts.count('#')) {
                for (char followSym : followSet[nt]) {
                    parsingTable[{nt, followSym}] = prod;
                }
            }
        }
    }
}

void displayParsingTable() {
    cout << "\nPredictive Parsing Table:\n";
    for (char nt : nonTerminals) {
        for (char t : terminals) {
            if (parsingTable.find({nt, t}) != parsingTable.end()) {
                cout << "M[" << nt << "," << t << "] = " << nt << " → " << parsingTable[{nt, t}] << "\n";
            }
        }
    }
}

bool isLL1Grammar() {
    map<pair<char, char>, int> countTable;
    for (auto &[key, prod] : parsingTable) {
        countTable[key]++;
        if (countTable[key] > 1) return false;
    }
    return true;
}

bool validateString(string input) {
    input += '$';
    stack<char> st;
    st.push('$');
    st.push('S');
    int i = 0;

    while (!st.empty()) {
        char top = st.top();
        char current = input[i];
        st.pop();

        if (top == current) {
            i++;
        } else if (nonTerminals.count(top)) {
            if (parsingTable.find({top, current}) != parsingTable.end()) {
                string prod = parsingTable[{top, current}];
                if (prod != "#") {
                    for (int j = prod.length() - 1; j >= 0; j--)
                        st.push(prod[j]);
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    return i == input.length();
}

int main() {
    initializeGrammar();
    initializeFirstFollow();
    constructParsingTable();
    displayParsingTable();

    if (isLL1Grammar())
        cout << "\n✅ The grammar is LL(1)\n";
    else {
        cout << "\n❌ The grammar is not LL(1)\n";
        return 0;
    }

    vector<string> testStrings = {"abc", "ac", "(abc)", "c", "(ac)", "a", "()", "(ab)", "abcabc", "b"};
    for (string s : testStrings) {
        cout << "\nTesting: \"" << s << "\"\n";
        bool valid = validateString(s);
        cout << (valid ? "✅ Valid string" : "❌ Invalid string") << "\n";
    }

    return 0;
}
