#include <iostream>
#include "hamming_decoder.h"


int main()
{
    HammingDecoder74 decoder;

    std::vector<uint8_t> input, output;
    decoder.Decode(input, output);

    std::cout << "Input bits: \n";
    for (auto& bit : input) {
        std::cout << static_cast<unsigned int>(bit);
    }
    std::cout << std::endl;

    std::cout << "Output bits: \n";
    for (auto& bit : output) {
        std::cout << static_cast<unsigned int>(bit);
    }
    std::cout << std::endl;

}



