#include <decoding_lib.h>

void Hamming_Decoder74::Decode(const data_t& kInputBits, data_t& output_bits)
{
	if (kInputBits.size() % m_N) {
		std::cout << "Warrning. Number of input bits not divided by N = 7!\n";
	}
	
	for (int it = 0; it < kInputBits.size(); it += m_N)
	{
		Matrix_t input_word(1, m_N);
		for (int bit = 0; bit < m_N; ++bit) {
			input_word.at(bit) = kInputBits.at(it + bit);
			assert(input_word.at(bit) <= 1);
		}

		uint8_t mod_dimension = 2;
		Matrix_t syndrome_bits(1, (m_N-m_K));
		syndrome_bits = (input_word * (!m_parity_check_matrix)) % mod_dimension;

		uint8_t syndrome = 0;
		for (size_t bit = 0; bit < (m_N - m_K); ++bit) {
			syndrome |= (syndrome_bits.at(bit) << ((m_N - m_K) - bit - 1));
		}

		Matrix_t corrected_word(1, m_K);
		corrected_word = (input_word + m_syndrome_table.getRow(syndrome)) % mod_dimension;
		
		for (size_t bit = 0; bit < m_K; ++bit) {
			output_bits.push_back(corrected_word.at(bit));
		}
	}
}


void Hamming_Decoder74::Decode2String(const data16_t& kInputData, std::string& output_string)
{
	for (auto& number : kInputData) {
		data_t input_bits(2 * m_N);
		for (size_t it = 0; it < 2 * m_N; ++it) {
			input_bits.at(it) = (number >> (2 * m_N - it - 1)) & 1;
		}
		
		data_t output_bits;
		Decode(input_bits, output_bits);

		char output_char = 0;
		for (size_t bit = 0; bit < 2 * m_K; ++bit) {
			output_char |= (output_bits.at(bit) << (2 * m_K - bit - 1));
		}	
		output_string.push_back(output_char);
	}
}