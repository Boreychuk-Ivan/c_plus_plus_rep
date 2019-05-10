#pragma once
#include <vector>
#include <cstdint>		//uint8_t
#include "../matrix_lib/matrix_lib.h"
#include <string>
#include <cmath>

using Matrix_t = Matrix<uint8_t>;
using data_t = std::vector<uint8_t>;
using data16_t = std::vector<uint16_t>;

class I_Decoder
{
public:
	virtual void Decode(const data_t& kInputData, data_t& output_data) = 0;
	virtual ~I_Decoder() {};
};

class Syndrome_Decoder : public I_Decoder
{
protected:
	const size_t m_N, m_K;
	Matrix_t m_parity_check_matrix;
	Matrix_t m_syndrome_table;
public:
	Syndrome_Decoder(const size_t N, const size_t K) : m_N(N), m_K(K)
	{
		m_syndrome_table = Matrix_t( pow(2,(m_N-m_K)) , N);
		m_parity_check_matrix = Matrix_t(N - K, N);
	}
	virtual void Decode(const data_t& kInputData, data_t& output_data) = 0;
	Matrix_t getH(void) const { return m_parity_check_matrix; };
	Matrix_t& setH(void) { return m_parity_check_matrix; };
	Matrix_t getS(void) const { return m_syndrome_table; };
	Matrix_t& setS(void) { return m_syndrome_table; };

	virtual ~Syndrome_Decoder() {};
};

class Hamming_Decoder74 : public Syndrome_Decoder
{
private:
	using Syndrome_Decoder::m_parity_check_matrix;
	using Syndrome_Decoder::m_syndrome_table;
public:
	Hamming_Decoder74() : Syndrome_Decoder(7, 4)
	{
		m_parity_check_matrix = { 1,0,1,1,1,0,0,
								  1,1,1,0,0,1,0,
								  0,1,1,1,0,0,1 };

		m_syndrome_table = { 0,0,0,0,0,0,0,
							0,0,0,0,0,0,1,
							0,0,0,0,0,1,0,
							0,1,0,0,0,0,0,
							0,0,0,0,1,0,0,
							0,0,0,1,0,0,0,
							1,0,0,0,0,0,0,
							0,0,1,0,0,0,0 };
	}

	void Decode(const data_t& kInputBits, data_t& output_bits) override;
	void Decode2String(const data16_t& kInputData, std::string& output_string);

};
