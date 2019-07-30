#pragma once
#include <vector>
#include <cstdint>		//uint8_t
#include <string>

#include "matrix_lib.h"


using Matrix_t = Matrix<uint8_t>;
using Bit_t = uint8_t;

class I_Encoder
{
public:
	virtual void Encode(std::vector<Bit_t> input_data, std::vector<Bit_t>& output_data) = 0;
	virtual ~I_Encoder() {};
};


class Block_Encoder : public I_Encoder
{
protected:
	const size_t m_N, m_K;
	Matrix_t m_generator_mtx;
	Matrix_t m_parity_check_matrix;
public:
	Block_Encoder(const size_t N, const size_t K) : m_N(N), m_K(K)
	{
		m_generator_mtx = Matrix_t(K, N);
		m_parity_check_matrix = Matrix_t(N-K, N);
	}

	virtual void Encode(std::vector<Bit_t> input_bits, std::vector<Bit_t>& output_bits) = 0;
	Matrix_t getG(void) const { return m_generator_mtx; }
	Matrix_t getH(void) const { return m_parity_check_matrix; };
	Matrix_t& setG(void) { return m_generator_mtx; };
	Matrix_t& setH(void) { return m_parity_check_matrix; };
	virtual ~Block_Encoder() {};
};


class Hamming_Encoder74 : public Block_Encoder
{
private:
	using Block_Encoder::m_generator_mtx;
	using Block_Encoder::m_parity_check_matrix;

public:

	Hamming_Encoder74() : Block_Encoder(7,4)
	{
		m_generator_mtx = { 1,0,0,0,1,1,0,
							0,1,0,0,0,1,1,
							0,0,1,0,1,1,1,
							0,0,0,1,1,0,1 };

		m_parity_check_matrix = { 1,0,1,1,1,0,0,
								  1,1,1,0,0,1,0,
								  0,1,1,1,0,0,1 };
	}

	//Bits encoder
	void Encode(std::vector<Bit_t> input_bits, std::vector<Bit_t>& output_bits) override;

	//For fun / it is useless
	void EncodeString(const std::string& kInputString, std::vector<uint16_t>& output_data);
};


template<class T>
void DispVector(const std::vector<T>& kInputVector)
{
	for (auto & elem : kInputVector) {
		std::cout << (uint16_t)elem << " ";
	}
	std::cout << std::endl;
}