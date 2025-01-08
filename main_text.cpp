#include <iostream>
#include "HuffmanEncoding.hpp"

int main() {
    std::string text = "hello world";

    HuffmanEncoding huffman(text);
    std::string decoded = huffman.encode();

    for (const auto& pair : huffman.getHuffmanCodes()) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    std::cout << "Decoded Text: " << decoded << std::endl;

    std::string encoded = huffman.decode("01100010101101111010110001101110");

    std::cout << "Encoded Text: " << encoded << std::endl;

    return 0;
}
