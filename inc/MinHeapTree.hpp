#ifndef MINHEAPTREE_HPP
#define MINHEAPTREE_HPP

#include <iostream>
#include <queue>
#include <unordered_map>

class HuffmanNode {
public:
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

class MinHeapTree {
public:
    MinHeapTree();
    ~MinHeapTree();

    HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& freqMap);
    static void printTree(HuffmanNode* node, const std::string& prefix = "");

private:
    HuffmanNode* root;
    void deleteTree(HuffmanNode* node);
};

#endif // MINHEAPTREE_HPP
