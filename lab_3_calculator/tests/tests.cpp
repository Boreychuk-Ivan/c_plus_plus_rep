#include <iostream>
#include <exception>
#include "calculator_lib.h"
#include <gtest/gtest.h>

void ResultCompare(exprcontainer_t commands, exprcontainer_t results) {
	
	exprcontainer_t output_expr;

	std::cout << "\nInput commands:\n";
	for (int it(0); it < commands.size(); it++)
	{
		StartCalculation(commands.at(it), output_expr);
		
		std::cout << commands.at(it) << "\n";
		std::cout << "  " << output_expr.at(0) << "\n";

		ASSERT_EQ(output_expr.at(0), results.at(it))
			<< "\ncmd:" << commands.at(it) << " res: " << results.at(it);
	}
}


TEST(calc_test_suite, simple_test)
{
	exprcontainer_t commands = {
		"150+150",
		"500-250",
		"100*5",
		"700/7",
		"5^2",
		"(2.5*5.01^2)/35+(565452/19723)"
	};

	exprcontainer_t results = {
		"150+150 = 300\n",
		"500-250 = 250\n",
		"100*5 = 500\n",
		"700/7 = 100\n",
		"5^2 = 25\n",
		"(2.5*5.01^2)/35+(565452/19723) = 30.463\n"
	};	
	ResultCompare(commands, results);
}
	
TEST(calc_test_suite, function_usage)
{
	exprcontainer_t commands = {
		"cos(pi)",
		"log2(32)",
		"mod(5,2)",
		"ceil(3.2)",
		"abs(-5)",
		"max(10,2)"
	};

	exprcontainer_t results = {
		"cos(pi) = -1\n",
		"log2(32) = 5\n",
		"mod(5,2) = 1\n",
		"ceil(3.2) = 4\n",
		"abs(-5) = 5\n",
		"max(10,2) = 10\n"
	};

	ResultCompare(commands, results);
}

TEST(calc_test_suite, memory_usage)
{
	exprcontainer_t commands = {
		"10*log10(40)",
		"MW",
		"MR",
		"20+MR",
		"MW[1]",
		"60-MR-MR[1]",
		"MR[4]"
	};

	exprcontainer_t results = {
		"10*log10(40) = 16.021\n",
		"MW = 16.021\n",
		"MR = 16.021\n",
		"20+MR = 36.021\n",
		"MW[1] = 36.021\n",
		"60-MR-MR[1] = 7.959\n",
		"MR[4] = 0\n"
	};

	ResultCompare(commands, results);
}


TEST(calc_test_suite, variable_usage)
{
	exprcontainer_t commands = {
		"bits = 8",
		"minval = -2^(bits-1)",
		"maxval = 2^(bits-1)-1",
		"range = maxval-minval"
	};

	exprcontainer_t results = {
		"bits = 8\n",
		"minval = -128\n",
		"maxval = 127\n",
		"range = 255\n"
	};

	ResultCompare(commands, results);
}

TEST(calc_test_suite, exceptions)
{
	exprcontainer_t commands = {
		"eAdxz,31",
		"10*,45",
		"a*b",
		"число = 0",
		"a,,22+321",
		"10/0",
		"a=ds==/*=",
	};
	exprcontainer_t output_expr;

	std::cout << "\nThis commands would throw exception!\n";
	for (auto cmd : commands) {
		std::cout << cmd << "\n";
		ASSERT_THROW(StartCalculation(cmd, output_expr), const char*)
			<< "cmd : " << cmd << " result : " << output_expr.at(0)<<"\n";
	}
	std::cout << "\n";
}

TEST(calc_test_suite, interesting_features)
{
	exprcontainer_t commands = {
		"",
		"1------------1",
		"1-----------1",
		"10+++++++++++10",
		"10-+-+-+-+-+-+10",
		"10*log10(log10(log10(10)))",
		"10*log10(log10(log10(10000)))"
	};
	exprcontainer_t results = {
		"",
		"1------------1 = 2\n",
		"1-----------1 = 0\n",
		"10+++++++++++10 = 20\n",
		"10-+-+-+-+-+-+10 = 20\n",
		"10*log10(log10(log10(10))) = -inf\n",
		"10*log10(log10(log10(10000))) = -2.204\n"
	};

	ResultCompare(commands, results);
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


