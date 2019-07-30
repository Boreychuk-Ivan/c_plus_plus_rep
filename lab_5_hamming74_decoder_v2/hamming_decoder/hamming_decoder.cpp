#include "hamming_decoder.h"

void HammingDecoder74::Decode(const std::vector<uint8_t>& kInputData, std::vector<uint8_t>& output_data)
{
    if (!CheckInputCorrection(kInputData)) throw "Error : Input elements must be 0 or 1\n";

    std::vector<uint8_t> input_corrected(kInputData);
    int corrected_size = (kInputData.size() % m_N == 0) ? kInputData.size() : ((kInputData.size()/m_N + 1)*m_N);
    input_corrected.resize(corrected_size);  
    output_data.resize(input_corrected.size() / m_N * m_K);
    int it_out = 0;
    for (size_t it = 0; it < input_corrected.size(); it += m_N)
    {
        std::vector<uint8_t> in_part(input_corrected.begin()+ it, input_corrected.begin() + it + m_N);
        std::vector<uint8_t> syndrome, corrected_word;
        SyndromeCalculation(in_part, syndrome);
        WordCorrection(in_part, syndrome, corrected_word);
        for(size_t it_2 = 0; it_2 < m_K; ++it_2)
            output_data.at(it_out++) = corrected_word.at(it_2);
    }
}

void HammingDecoder74::SyndromeCalculation(const std::vector<uint8_t>& kInputData, std::vector<uint8_t>& syndrome)
{
    assert(kInputData.size() == m_N);
    const std::vector<uint8_t>& a = kInputData;

    syndrome.resize(m_N - m_K);
    syndrome.at(0) = a[0] ^ a[2] ^ a[3] ^ a[4];
    syndrome.at(1) = a[0] ^ a[1] ^ a[2] ^ a[5];
    syndrome.at(2) = a[1] ^ a[2] ^ a[3] ^ a[6];
}

void HammingDecoder74::WordCorrection(const std::vector<uint8_t>& kInputData, const std::vector<uint8_t>& kSyndromeBits, std::vector<uint8_t>& output)
{
    assert(kInputData.size() == m_N);
    assert(kSyndromeBits.size() == m_N - m_K);

    uint8_t syndrome = 0;
    for (size_t bit = 0; bit < (m_N - m_K); ++bit) {
        syndrome |= (kSyndromeBits.at(bit) << ((m_N - m_K) - bit - 1));
    }

    std::vector<uint8_t> corrected_word(kInputData);
    if      (syndrome == 1)
        corrected_word.at(6) ^= 1;
    else if (syndrome == 2)
        corrected_word.at(5) ^= 1;
    else if (syndrome == 3)
        corrected_word.at(1) ^= 1;
    else if (syndrome == 4)
        corrected_word.at(4) ^= 1;
    else if (syndrome == 5)
        corrected_word.at(3) ^= 1;
    else if (syndrome == 6)
        corrected_word.at(0) ^= 1;
    else if (syndrome == 7)
        corrected_word.at(2) ^= 1;
    
    output = corrected_word;
}

bool HammingDecoder74::CheckInputCorrection(const std::vector<uint8_t>& kInputData)
{
    for (size_t it = 0; it < kInputData.size(); ++it)
    {
        if (kInputData.at(it) > 1) return 0;
    }
    return 1;
}
