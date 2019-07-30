#include <vector>
#include <iostream>
#include "hamming_encoder_lib.h"

using Bit_t = uint8_t;


class Constituent_Encoder
{
public:
    enum OUT_TYPE { ALL, FIRST, SECOND };
private:
	std::vector<Bit_t> m_delay_line;
    OUT_TYPE m_select_out;
public:
    Constituent_Encoder() : m_delay_line{0, 0}, m_select_out(ALL){}
	void Encode(const std::vector<Bit_t> kInputBits, std::vector<Bit_t>& output_bits);

	void PushDelayLine(const Bit_t& in_bit) {
		if (in_bit > 1) { std::cerr << "PushDelayLine: Error! Invalid bit value!\n"; exit(1); }
		m_delay_line.insert(m_delay_line.begin(), in_bit);
		m_delay_line.pop_back();
	}

	void Reset() {
        m_delay_line.clear();  
        m_delay_line = { 0, 0 }; 
    }
	std::vector<Bit_t> GetDelayLine() const 
    { 
        return m_delay_line; 
    }

    void SelectOut(OUT_TYPE out_type)
    {
        m_select_out = out_type;
    }
};


class Semirandom_Interleaver
{
private:
	unsigned int m_length, m_step_size, m_shift;
	std::vector<Bit_t> m_delay_line;
    std::vector<unsigned int> m_permutation_indexes;
public:
	Semirandom_Interleaver(int length, int step_size, int shift) :
		m_length(length), m_step_size(step_size), m_shift(shift)
	{
		if ((length < 0) || (step_size < 0) || (shift < 0) || (step_size > length) || (shift > length)) {
			std::cerr << "Semirandom_Interleaver: Error! invalid object creation\n"; exit(2);
		}
		m_delay_line = std::vector<Bit_t>(m_length,0);
        for(int it = 0; it < m_length; ++it)
        {
            m_permutation_indexes.push_back(((m_step_size*it + m_shift) % m_length));
        }
	}

	void PushDelayLine(const Bit_t& in_bit){
		if (in_bit > 1) { std::cerr << "PushDelayLine: Error! Invalid bit value!\n"; exit(1); }
		m_delay_line.insert(m_delay_line.begin(), in_bit);
		m_delay_line.pop_back();
	}

	void Reset()
    { 
        m_delay_line.clear();  
        m_delay_line = std::vector<Bit_t>(m_length,0); 
    }

	void Interleave(const std::vector<Bit_t> kInputBits, std::vector<Bit_t>& output_bits);

    auto GetParametrs()
    {
        struct result { 
            unsigned int length;
            unsigned int step_size;
            unsigned int shift;
        };
        return result{ m_length, m_step_size, m_shift };
    }
};


class Turbo_Encoder : public I_Encoder
{
private:
    Constituent_Encoder    m_coder_1;
    Constituent_Encoder    m_coder_2;
    Semirandom_Interleaver m_interleaver;
public:
    Turbo_Encoder() : m_interleaver(16, 3, 0)
    {
        m_coder_1.SelectOut(Constituent_Encoder::ALL);
        m_coder_2.SelectOut(Constituent_Encoder::SECOND);
    }

    void Reset()
    {
        m_coder_1.Reset();
        m_coder_2.Reset();
        m_interleaver.Reset();
    }

    void Encode(std::vector<Bit_t> input_bits, std::vector<Bit_t>& output_bits);
};