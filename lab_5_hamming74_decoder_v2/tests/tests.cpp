#include <iostream>
#include <exception>
#include "hamming_decoder.h"
#include <gtest/gtest.h>

template <class T>
bool CompareVector(const std::vector<T>& kV_0, const std::vector<T>& kV_1)
{
    if (kV_0.size() != kV_1.size()) return 0;
    for (size_t it = 0; it < kV_0.size(); ++it)
    {
        if (std::abs(kV_0.at(it) - kV_1.at(it)) > 1e-3) return 0;
    }
    return 1;
}

TEST(HammingDecoderTests, decoding_correct_words_test)
{
    std::vector<uint8_t> input
    {
        0,0,0,0,0,0,0,
        0,0,0,1,1,0,1,
        0,0,1,0,1,1,1,
        0,0,1,1,0,1,0,
        0,1,0,0,0,1,1,
        0,1,0,1,1,1,0,
        0,1,1,0,1,0,0,
        0,1,1,1,0,0,1,
        1,0,0,0,1,1,0,
        1,0,0,1,0,1,1,
        1,0,1,0,0,0,1,
        1,0,1,1,1,0,0,
        1,1,0,0,1,0,1,
        1,1,0,1,0,0,0,
        1,1,1,0,0,1,0,
        1,1,1,1,1,1,1,
    };

    std::vector<uint8_t> output_expected
    {
        0,0,0,0,
        0,0,0,1,
        0,0,1,0,
        0,0,1,1,
        0,1,0,0,
        0,1,0,1,
        0,1,1,0,
        0,1,1,1,
        1,0,0,0,
        1,0,0,1,
        1,0,1,0,
        1,0,1,1,
        1,1,0,0,
        1,1,0,1,
        1,1,1,0,
        1,1,1,1
    };

    std::vector<uint8_t> output_actual;
    HammingDecoder74 decoder;
    decoder.Decode(input, output_actual);
    ASSERT_TRUE(CompareVector(output_expected, output_actual));
}

TEST(HammingDecoderTests, decoding_words_with_error_test)
{
    std::vector<uint8_t> input
    {
        0,0,0,0,0,1,0,
        0,0,0,0,1,0,1,
        0,0,1,0,1,1,1,
        0,0,1,1,0,0,0,
        0,1,0,0,0,1,1,
        1,1,0,1,1,1,0,
        0,1,1,0,1,0,0,
        0,0,1,1,0,0,1,
        1,0,0,0,1,1,0,
        1,0,1,1,0,1,1,
        1,0,1,0,0,0,1,
        1,0,0,1,1,0,0,
        1,1,0,0,1,0,1,
        1,1,0,0,0,0,0,
        1,1,1,0,0,1,0,
        1,1,0,1,1,1,1,
    };

    std::vector<uint8_t> output_expected
    {
        0,0,0,0,
        0,0,0,1,
        0,0,1,0,
        0,0,1,1,
        0,1,0,0,
        0,1,0,1,
        0,1,1,0,
        0,1,1,1,
        1,0,0,0,
        1,0,0,1,
        1,0,1,0,
        1,0,1,1,
        1,1,0,0,
        1,1,0,1,
        1,1,1,0,
        1,1,1,1
    };

    std::vector<uint8_t> output_actual;
    HammingDecoder74 decoder;
    decoder.Decode(input, output_actual);
    ASSERT_TRUE(CompareVector(output_expected, output_actual));
}

TEST(HammingDecoderTests, decoding_empty_vector_test)
{
    std::vector<uint8_t> empty_input, output_actual;
    HammingDecoder74 decoder;
    decoder.Decode(empty_input, output_actual);
    ASSERT_TRUE(output_actual.size() == 0);
}

TEST(HammingDecoderTests, invalid_input_values)
{
    std::vector<uint8_t> input{0,1,2,3,5,6}, output_actual;
    HammingDecoder74 decoder;
    ASSERT_ANY_THROW(decoder.Decode(input, output_actual));
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
