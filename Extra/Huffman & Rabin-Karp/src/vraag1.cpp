#include "huffman.h"

#include <iostream>
using std::cout;

int main() {
    map<uchar, uint> freq{{'a', 7}, {'b', 8}, {'c', 1}, {'d', 2}, {'e', 30}, {'f', 1}, {'g', 15}};

    map<uchar, string> codering = huffman(freq);

    for (const auto& [c, code] : codering) {
        cout << "Code '" << c << "' heeft voorstelling: " << code << "\n";
    }
    return 0;
}