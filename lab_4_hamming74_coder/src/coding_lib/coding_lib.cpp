#include "coding_lib.h"

void Hamming_Encoder74::Encode(std::vector<Bit_t> input_bits, std::vector<Bit_t>& output_bits)
{

	if (input_bits.size() % m_K) {
		std::cout << "Warrning. Number of input bits not divided by K = 4!\n\
					  \rZeros will be added to the end.\n";
		for (int it(0); it < input_bits.size() % m_K; ++it) { input_bits.push_back(0); }
	}

	for (int it = 0; it < input_bits.size(); it+=m_K)
	{
		Matrix_t input_word(1, m_K);
		for (int bit = 0; bit < m_K; ++bit) {
			input_word.at(bit) = input_bits.at(it + bit);
			if (input_word.at(bit) > 1) { throw "Error! Invalid bit value (>1)\n"; }
		}

		uint8_t mod_dimension = 2;
		Matrix_t output_word(1, m_N);
		output_word = (input_word*m_generator_mtx) % mod_dimension;

		for (int bit = 0; bit < m_N; ++bit) {
			output_bits.push_back(output_word.at(bit));
		}
	}

}


void Hamming_Encoder74::EncodeString(const std::string& kInputString, std::vector<uint16_t>& output_data)
{
	for (const char &symbol : kInputString) {
		std::vector<Bit_t> input_vector(2*m_K);
		for (size_t it = 0; it < 2*m_K; ++it) {
			input_vector.at(it) = (symbol >> (2*m_K-it-1)) & 1;
		}

		std::vector<Bit_t> output_vector;
		Encode(input_vector, output_vector);

		uint16_t output_word = 0;
		for (size_t bit = 0; bit < 2 * m_N; ++bit) {
			output_word |= (output_vector.at(bit) << (2*m_N-bit-1));
		}
		output_data.push_back(output_word);
	}
}
