#include <iostream>
#include <coding_lib.h>
#include <matrix_lib.h>

void DispBits(const uint64_t kNumber, const size_t kBits);


int main()
{
	Hamming_Encoder74 hamm_coder;

	std::cout << hamm_coder.getG() << std::endl;
	
	std::vector<Bit_t> input_bits = { 1,0,1,0 };
	std::vector<Bit_t> output_bits;

	hamm_coder.Encode(input_bits, output_bits);

	DispVector<Bit_t>(input_bits);
	DispVector<Bit_t>(output_bits);

	std::string input_string = "Hello!";

	std::vector<uint16_t> encoded_data;
	hamm_coder.EncodeString(input_string, encoded_data);
	
	std::cout << "\n\nInput bits:";
	for (auto &ch : input_string) {
		DispBits(ch, 14);
	}

	std::cout << "\n\nOutput bits:";
	for (auto &num : encoded_data) {
		DispBits(num, 14);
		std::cout << "  " << num << " : ";
	}

	std::cout << std::endl;
	return 0;
}


void DispBits(const uint64_t kNumber, const size_t kBits)
{
	std::cout << std::endl;
	for (size_t bit = 0; bit < kBits; ++bit) {
		std::cout << ((kNumber >> (kBits - bit-1)) & 1);
	}
}
