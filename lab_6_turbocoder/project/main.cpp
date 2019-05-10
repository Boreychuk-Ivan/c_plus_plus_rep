#include <iostream>
#include <turbo_coder_lib.h>
#include <matrix_lib.h>

void DispBin(const uint64_t kNumber, const size_t kBits);

template<class T>
void DispVector(const std::vector<T>& kInputVector);

int main()
{
	Constituent_Encoder coder;
	std::vector<Bit_t> input_bits = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
	std::vector<Bit_t> output_bits;
    output_bits.reserve(2*input_bits.size());

	coder.Encode(input_bits, output_bits);

	std::cout << "Input bits : \n";
	DispVector<Bit_t>(input_bits);

	std::cout << "Output bits : \n";
	DispVector<Bit_t>(output_bits);

	Semirandom_Interleaver interleaver(16,3,0);

    std::cout << "interleaver length: "<<interleaver.GetParametrs().length << std::endl;

	//std::vector<Bit_t> input_bits1 = {0,1,1,0,1,0,0,1,1,1,1,1,1,0,1,0};
	//std::vector<Bit_t> output_bits1;
	//interleaver.Interleave(input_bits1, output_bits1);

	//std::cout << "Input bits : \n";
	//DispVector<Bit_t>(input_bits1);

	//std::cout << "Output bits : \n";
	//DispVector<Bit_t>(output_bits1);


    Turbo_Encoder turbo_coder;
    std::vector<Bit_t> turbo_output_bits;
    turbo_output_bits.reserve(input_bits.size()*3);
    turbo_coder.Encode(input_bits, turbo_output_bits);

    std::cout << "Turbo output bits : \n";
    DispVector<Bit_t>(turbo_output_bits);

	return 0;
}


void DispBin(const uint64_t kNumber, const size_t kBits)
{
	std::cout << std::endl;
	for (size_t bit = 0; bit < kBits; ++bit) {
		std::cout << ((kNumber >> (kBits - bit-1)) & 1);
	}
}

template<class T>
void DispVector(const std::vector<T>& kInputVector)
{
	for (auto & elem : kInputVector) {
		std::cout << (uint16_t)elem << " ";
	}
	std::cout << std::endl;
}