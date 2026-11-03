#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) { return a->freq > b->freq; }
};

Node* build_huffman_tree(const string& text, unordered_map<char, int>& frequency) {
    for (char ch : text) frequency[ch]++;
    priority_queue<Node*, vector<Node*>, Compare> heap;
    for (auto p : frequency) heap.push(new Node(p.first, p.second));

    while (heap.size() > 1) {
        Node* left = heap.top(); heap.pop();
        Node* right = heap.top(); heap.pop();
        Node* parent = new Node('\\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        heap.push(parent);
    }
    return heap.empty() ? nullptr : heap.top();
}

void generate_codes(Node* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch] = code.empty() ? "0" : code;
        return;
    }
    generate_codes(root->left, code + "0", codes);
    generate_codes(root->right, code + "1", codes);
}

int main() {
    string text;
    cout << "Enter a string: ";
    getline(cin, text);
    if (text.empty()) {
        cout << "Please enter a non-empty string.\n";
        return 0;
    }

    unordered_map<char, int> frequency;
    Node* root = build_huffman_tree(text, frequency);
    unordered_map<char, string> codes;
    generate_codes(root, "", codes);

    cout << "\nCharacter Frequencies:\n";
    for (auto p : frequency) cout << "'" << p.first << "' : " << p.second << "\n";
    cout << "\nHuffman Codes:\n";
    for (auto p : codes) cout << "'" << p.first << "' : " << p.second << "\n";

    string encoded;
    for (char ch : text) encoded += codes[ch];
    cout << "\nEncoded String:\n" << encoded << "\n";
    return 0;
}
