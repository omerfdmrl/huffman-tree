#ifndef HUFFMANENCODING_HPP
#define HUFFMANENCODING_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "MinHeapTree.hpp"

class HuffmanEncoding {
private:
    std::string text;
    std::unordered_map<char, int> freqMap;
    std::unordered_map<char, std::string> huffmanCodes;
    MinHeapTree minHeapTree;
    HuffmanNode* root;

    void buildFrequencyMap();
    void buildHuffmanCodes(HuffmanNode* node, const std::string& code);

public:
    HuffmanEncoding(const std::string& text = "");
    std::string encode();
    std::string decode(const std::string& encodedText);

    void compress(const std::string& inputFile, const std::string& outputFile);
    void decompress(const std::string& inputFile, const std::string& outputFile);

    std::unordered_map<char, int> getFrequencyTable() {
        return freqMap;
    }

    std::unordered_map<char, std::string> getHuffmanCodes() {
        return huffmanCodes;
    }
};

#endif // HUFFMANENCODING_HPP
