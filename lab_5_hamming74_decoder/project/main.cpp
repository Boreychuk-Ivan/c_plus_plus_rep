#include <iostream>
#include <decoding_lib.h>
#include <matrix_lib.h>

void DispBits(const uint64_t kNumber, const size_t kBits);

int main()
{
	Hamming_Decoder74 hamm_decoder;
	
	data_t input_bits = { 0,0,1,1,0,1,0 };
	data_t output_bits;
	hamm_decoder.Decode(input_bits, output_bits);
	
	std::cout << "Input bits: \n";
	for (auto &bit : input_bits) {
		std::cout << static_cast<unsigned int>(bit);
	}
	std::cout << std::endl;

	std::cout << "Output bits: \n";
	for (auto &bit : output_bits) {
		std::cout << static_cast<unsigned int>(bit);
	}
	std::cout << std::endl;

	data16_t encoded_massage = { 0x11c6, 0x1a2e, 0x1a65, 0x1a65, 0x1a7f, 0x0b8d};
	data16_t error = {0x0100, 0x1000, 0x0001, 0x0010, 0x0100, 0x1000};

	for (int it = 0; it < encoded_massage.size(); ++it) {
		encoded_massage.at(it) ^= error.at(it);
	}

	std::string decoded_massage;
	hamm_decoder.Decode2String(encoded_massage, decoded_massage);
	
	std::cout << "decoded massage: "<< decoded_massage;

	return 0;
}


void DispBits(const uint64_t kNumber, const size_t kBits)
{
	std::cout << std::endl;
	for (size_t bit = 0; bit < kBits; ++bit) {
		std::cout << ((kNumber >> (kBits - bit-1)) & 1);
	}
}