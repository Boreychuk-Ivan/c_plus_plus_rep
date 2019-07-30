#include "turbo_coder_lib.h"

void Constituent_Encoder::Encode(const std::vector<Bit_t> kInputBits, std::vector<Bit_t>& output_bits)
{
	for (auto &in_bit : kInputBits) {
        Bit_t sum_1 = in_bit ^ m_delay_line.at(0) ^ m_delay_line.at(1);
		Bit_t sum_2 = sum_1 ^ m_delay_line.at(1);
        PushDelayLine(sum_1);

        if(m_select_out == ALL)
        {
            output_bits.push_back(in_bit);
            output_bits.push_back(sum_2);
        }
        else if (m_select_out == FIRST)
        {
            output_bits.push_back(in_bit);
        }
        else if (m_select_out == SECOND)
        {
            output_bits.push_back(sum_2);
        }
	}
}

void Semirandom_Interleaver::Interleave(const std::vector<Bit_t> kInputBits, std::vector<Bit_t>& output_bits)
{
	for (size_t it = 0; it < kInputBits.size(); it += m_length) {
		for (size_t bit = 0; bit < m_length; ++bit) {
			m_delay_line.at(bit) = kInputBits.at(it + bit);
		}

		for (int it = 0; it < m_length; ++it) {
			output_bits.push_back( m_delay_line.at(m_permutation_indexes.at(it)) );
		}
	}
}

void Turbo_Encoder::Encode(std::vector<Bit_t> input_bits, std::vector<Bit_t>& output_bits)
{
    
    int block_size = m_interleaver.GetParametrs().length;
    for (int it = 0; it < input_bits.size() % block_size; ++it)
    {
        input_bits.push_back(0);
    }

    int num_blocks = input_bits.size() / block_size;
    
    for (size_t block_it = 0; block_it < num_blocks; ++block_it)
    {
        std::vector<Bit_t> input_block;
        int offset = block_it * block_size;
        input_block.insert(input_block.begin(), input_bits.begin()+ offset, input_bits.begin() + offset + block_size);

        std::vector<Bit_t> interleaved_bits;
        m_interleaver.Interleave(input_block, interleaved_bits);

        std::vector<Bit_t> encoded_bits_1;
        std::vector<Bit_t> encoded_bits_2;

        m_coder_1.Encode(input_bits, encoded_bits_1);
        m_coder_2.Encode(interleaved_bits, encoded_bits_2);

        for(size_t bit_it = 0; bit_it < block_size; ++bit_it)
        {
            output_bits.push_back(encoded_bits_1.at(2*bit_it));
            output_bits.push_back(encoded_bits_1.at(2*bit_it+1));
            output_bits.push_back(encoded_bits_2.at(bit_it));
        }
    }
}
