#include <gtest/gtest.h>
#include <iostream>
#include <exception>
#include <coding_lib.h>

void CompareResult(std::vector<Bit_t> actual, std::vector<Bit_t> expected)
{
	ASSERT_EQ(actual.size(),expected.size()) << "Actual and expected sizes is not equal\n";
	for (int it = 0; it < actual.size(); ++it)
	{
		ASSERT_EQ(actual.at(it), expected.at(it)) << "Actual and expected nor equal in\" " << it << "\" position\n";
	}
}

TEST(tests_coder_suite, empty_vector)
{	
	Hamming_Encoder74 coder;
	std::vector<Bit_t> empty_vector;
	std::vector<Bit_t> actual_bits;
	coder.Encode(empty_vector, actual_bits);
	std::cout << "\n size of input vector: " << empty_vector.size() << std::endl;
	std::cout << "\n size of output vector: " << actual_bits.size() << std::endl;
	ASSERT_TRUE(actual_bits.size() == 0);
}

TEST(tests_coder_suite, ivanlid_bit_value) {
	Hamming_Encoder74 coder;
	std::vector<Bit_t> input_data = { 0,1,2,0,1,3};
	std::vector<Bit_t> actual_bits;
	ASSERT_ANY_THROW(coder.Encode(input_data, actual_bits)) ;
}

TEST(tests_coder_suite, zero_input)
{
	Hamming_Encoder74 coder;

	std::vector<Bit_t> input_bits(8,0);
	std::vector<Bit_t> excepted_bits(14,0);
	
	std::vector<Bit_t> actual_bits;
	coder.Encode(input_bits, actual_bits);
	std::cout << "\nInput bits: \n";
	DispVector<Bit_t>(input_bits);
	std::cout << "\nOutput bits: \n";
	DispVector<Bit_t>(actual_bits);
	CompareResult(actual_bits, excepted_bits);
}

TEST(tests_coder_suite, word_compare)
{
	Hamming_Encoder74 coder;
	Matrix_t input_words_arr(16, 4);
	input_words_arr = {
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
					1,1,1,1};

	Matrix_t output_words_arr(16, 7);
	output_words_arr = {
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
					1,1,1,1,1,1,1 };

	std::vector<Bit_t> input_word;
	std::vector<Bit_t> expected_word;
	std::vector<Bit_t> actual_word;

	for (int it = 0; it < 16; ++it) {
		input_word.clear(); 
		expected_word.clear();
		actual_word.clear();

		input_word = input_words_arr.getRow(it);
		expected_word = output_words_arr.getRow(it);

		coder.Encode(input_word, actual_word);
		std::cout << "\nInput word:\n";
		DispVector<Bit_t>(input_word);
		std::cout << "\nExpected word:\n";
		DispVector<Bit_t>(expected_word);
		std::cout << "\nActual word:\n";
		DispVector<Bit_t>(actual_word);
		std::cout << "\n";
		CompareResult(expected_word, actual_word);
	}
}



int main(int argc, char *argv[])
{
	try {
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
	catch (const char* exception)
	{
		std::cerr << exception;
	}
}
