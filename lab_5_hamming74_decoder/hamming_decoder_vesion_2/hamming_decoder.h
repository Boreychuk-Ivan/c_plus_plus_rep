#pragma once

#include <vector>
#include <cstdint>        
#include <cmath>
#include <cassert>

class DecoderInterface
{
public:
    virtual void Decode(const std::vector<uint8_t>& kInputData, std::vector<uint8_t>& output_data) = 0;
    virtual ~DecoderInterface() {};
};

class HammingDecoder74 : DecoderInterface
{
public:
    void Decode(const std::vector<uint8_t>& kInputData, std::vector<uint8_t>& output_data) override;
    void SyndromeCalculation(const std::vector<uint8_t>& kInputData, std::vector<uint8_t>& syndrome);
    void WordCorrection(const std::vector<uint8_t>& kInputData, const std::vector<uint8_t>& kSyndromeBits, std::vector<uint8_t>& output);
private:
    size_t m_K = 4;
    size_t m_N = 7;
};