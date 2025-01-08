#include "HuffmanEncoding.hpp"

/**
 * @brief Construct a new Huffman Encoding:: Huffman Encoding object
 * 
 * @param text - optional parameter, do not set if want to compress file
 */
HuffmanEncoding::HuffmanEncoding(const std::string& text) : text(text), root(nullptr) {
    if(text.compare("") != 0) {
        buildFrequencyMap();
        root = minHeapTree.buildHuffmanTree(freqMap);
        buildHuffmanCodes(root, "");
    }
}

/**
 * @brief Build frequency table for tree
 * 
 */
void HuffmanEncoding::buildFrequencyMap() {
    for (char ch : text) {
        freqMap[ch]++;
    }
}

/**
 * @brief Build huffman coders
 * 
 * @param node - root node
 * @param code - recursive code
 */
void HuffmanEncoding::buildHuffmanCodes(HuffmanNode* node, const std::string& code) {
    if (!node) return;

    // if it's leaf, add code
    if (!node->left && !node->right) {
        huffmanCodes[node->data] = code;
    }

    // left tree is 0, right is 1
    buildHuffmanCodes(node->left, code + "0");
    buildHuffmanCodes(node->right, code + "1");
}

/**
 * @brief Encode text
 * 
 * @return std::string 
 */
std::string HuffmanEncoding::encode() {
    std::string encodedText;
    for (char ch : text) {
        encodedText += huffmanCodes[ch];
    }
    return encodedText;
}

/**
 * @brief Decode text
 * 
 * @param encodedText - encoded text based on same frequency table
 * @return std::string 
 */
std::string HuffmanEncoding::decode(const std::string& encodedText) {
    HuffmanNode* current = root;

    std::string decoded = "";
    for (char bit : encodedText) {
        // 0 is left, 1 is right
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {
            decoded += current->data;
            current = root;
        }
    }
    return decoded;
}

/**
 * @brief Compress file
 * 
 * @param inputFile - path of input file
 * @param outputFile - path of output file to export
 */
void HuffmanEncoding::compress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile)
        throw std::invalid_argument("Input file cannot open");
    
    char ch;
    while (inFile.get(ch)) {
        freqMap[ch]++;
        text += ch;
    }
    inFile.close();

    std::vector<std::pair<char, int>> freqVector(freqMap.begin(), freqMap.end());
    std::sort(freqVector.begin(), freqVector.end());
    freqMap.clear();
    for (const auto& pair : freqVector) {
        freqMap[pair.first] = pair.second;
    }

    root = minHeapTree.buildHuffmanTree(freqMap);
    buildHuffmanCodes(root, "");

    std::string encodedData;
    for (char ch : text) {
        encodedData += huffmanCodes[ch];
    }

    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile)
        throw std::invalid_argument("Output file cannot open");

    outFile << freqMap.size() << "\n";
    for (const auto& pair : freqMap) {
        outFile << pair.first << " " << pair.second << "\n";
    }

    for (size_t i = 0; i < encodedData.size(); i += 8) {
        std::bitset<8> byte(encodedData.substr(i, 8));
        char byteChar = static_cast<char>(byte.to_ulong());
        outFile.put(byteChar);
    }

    outFile.close();
}

/**
 * @brief Decompress compressed file
 * 
 * @param compressedFile - path of compressed file
 * @param outputFile - path of output file to export
 */
void HuffmanEncoding::decompress(const std::string& compressedFile, const std::string& outputFile) {
    std::ifstream inFile(compressedFile, std::ios::binary);
    if (!inFile)
        throw std::invalid_argument("Input file cannot open");

    size_t freqMapSize;
    inFile >> freqMapSize;
    inFile.ignore();
    freqMap.clear();
    for (size_t i = 0; i < freqMapSize; ++i) {
        char ch;
        int freq;
        inFile.get(ch);
        inFile >> freq;
        inFile.ignore();
        freqMap[ch] = freq;
    }
    std::vector<std::pair<char, int>> freqVector(freqMap.begin(), freqMap.end());
    std::sort(freqVector.begin(), freqVector.end());
    freqMap.clear();
    for (const auto& pair : freqVector) {
        freqMap[pair.first] = pair.second;
    }
    root = minHeapTree.buildHuffmanTree(freqMap);

    std::string encodedData;
    char byte;
    while (inFile.get(byte)) {
        std::bitset<8> bits(byte);
        encodedData += bits.to_string();
    }
    inFile.close();
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile)
        throw std::invalid_argument("Output file cannot open");
    
    HuffmanNode* current = root;

    for (char bit : encodedData) {
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {
            outFile.put(current->data);
            current = root;
        }
    }
    outFile.close();
}