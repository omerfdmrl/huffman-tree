#include "MinHeapTree.hpp"
#include <queue>
#include <unordered_map>

MinHeapTree::MinHeapTree() : root(nullptr) {}

MinHeapTree::~MinHeapTree() {
    deleteTree(root);
}

/**
 * @brief delete tree
 * 
 * @param node - root node to delete
 */
void MinHeapTree::deleteTree(HuffmanNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

/**
 * @brief create huffman tree based on frequency
 * 
 * @param freqMap - frequency map
 * @return HuffmanNode* 
 */
HuffmanNode* MinHeapTree::buildHuffmanTree(const std::unordered_map<char, int>& freqMap) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;

    for (const auto& pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        // create parent node
        HuffmanNode* node = new HuffmanNode('\0', left->freq + right->freq);
        node->left = left;
        node->right = right;

        minHeap.push(node);
    }

    root = minHeap.top();
    return root;
}

/**
 * @brief print tree
 * 
 * @param node - node to print
 * @param prefix - prefix is for recursive printing
 */
void MinHeapTree::printTree(HuffmanNode* node, const std::string& prefix) {
    if (!node) return;

    if (!node->left && !node->right) {
        std::cout << prefix << "Leaf: '" << node->data 
                  << "' (freq: " << node->freq << ")\n";
    } else {
        std::cout << prefix << "Node: (freq: " << node->freq << ")\n";
    }

    printTree(node->left, prefix + "  ");
    printTree(node->right, prefix + "  ");
}
