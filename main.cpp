#include <iostream>
#include "HuffmanEncoding.hpp"

int main() {
    HuffmanEncoding huffman;
    
    huffman.compress("test.txt", "test_compressed");

    huffman.decompress("test_compressed", "test_decoded.txt");

    return 0;
}
