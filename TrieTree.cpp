// Roman Shimkin, 62 group, Lab 1, Variant 9
// task: to build Trie-Tree with reversed words

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

const int SIZE = 26;

int code(char x) {
    if (x >= 'A' && x <= 'Z') return x - 'A';
    else if (x >= 'a' && x <= 'z') return x - 'a';
    else return -1;
}

struct Node {
    Node* ptrs[SIZE];
    bool eow;
    int num, now;
public:
    Node() {
        for (int i = 0; i < SIZE; i++)
            ptrs[i] = nullptr;
        eow = false;
        num = 0;
        now = -1;
    }
    int empty() {
        return num == 0;
    }
    int next() {
        int n = eow ? num - 1 : num;
        if (n) {
            Node* node = nullptr;
            do {
                now = (now + 1) % 26;
                node = ptrs[now];
            } while (!node);
            return now;
        }
        else return -1;
    }
    void getWords(vector<string>& vect, string prev = "") {
        if (eow) vect.push_back(prev);
        int n = eow ? num - 1 : num;
        for (int i = 0; i < n; i++) {
            int elem = next();
            string str = prev + static_cast<char>(elem + 'a');
            ptrs[elem]->getWords(vect, str);
        }
    }
    void printWords(string prev = "") {
        if (eow) cout << "word: '" << prev << "'\n";
        int n = eow ? num - 1 : num;
        for (int i = 0; i < n; i++) {
            int elem = next();
            char last = char(elem + 'a');
            prev += last;
            ptrs[elem]->printWords(prev);
        }
    }
    bool addWord(stack<char>& st) {
        if (st.empty()) {
            if (!eow) {
                eow = true;
                num++;
                return true;
            }
            else return false;
        }
        int elem = code(st.top());
        st.pop();
        if (elem == -1) return false;
        else {
            if (!ptrs[elem]) ptrs[elem] = new Node;
            bool res = ptrs[elem]->addWord(st);
            if (!res) {
                if (ptrs[elem]->empty()) {
                    Node* temp = ptrs[elem];
                    ptrs[elem] = nullptr;
                    delete temp;
                }
            }
            else num++;
            return res;
        }
    }
};

class TrieTree {
    Node* tree;
public:
    TrieTree() { }
    bool empty() {
        return tree == nullptr;
    }
    void print() {
        if (tree) tree->printWords();
        cout << "!!!\n";
    }
    vector<string> get() {
        vector<string> vect;
        if (tree) tree->getWords(vect);
        return vect;
    }
    void add(const string word) {
        if (!tree) tree = new Node;
        string copy(word);
        reverse(copy.begin(), copy.end());
        stack<char> st;
        for (int i = 0; i < copy.length(); i++)
            st.push(copy[i]);
        if (tree->addWord(st)) cout << "\t" << word << "is added\n";
    }
};

int main()
{
    TrieTree firstTree;
    int num;
    //cin >> num;
    string str;
    /*for (int i = 0; i < num; i++) {
        getline(cin, str);
        firstTree.add(str);
    }*/
    str = "boy";
    firstTree.add(str);
    firstTree.print();
    firstTree.add("fuck");
    vector<string> vect = firstTree.get(); 
    for (auto x : vect) cout << x << endl;
}