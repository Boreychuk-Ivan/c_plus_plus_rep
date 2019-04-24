#include <iostream>
#include <exception>
#include <Windows.h>
#include "calculator_lib.h"

int main()
{
	std::string input_string;
	exprcontainer_t output_expressions;

	Presentation();
	
	while (1) {
		try {

			input_string.clear();
			std::getline(std::cin, input_string);

			StartCalculation(input_string, output_expressions);

			DispResult(output_expressions);

		}
		catch (const char* exception) {
			std::cout << "\n" <<exception;
			std::cout << "_______________________________\n\n";
			std::cout << "try agan:\n";
		}
		catch (std::exception e) {
			std::cerr << e.what();
		}
	}
	return 0;
}