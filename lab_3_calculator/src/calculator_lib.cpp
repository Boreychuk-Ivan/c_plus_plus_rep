#include "calculator_lib.h"
#include <iomanip>      // std::setprecision


Memory       g_calc_memory;	//Global memory for MW,MR
variables_t  g_var_memory;  //Global memory for variables

const size_t precision = 3;


void StartCalculation(std::string input_string, exprcontainer_t& output_expressions)
{
	output_expressions.clear();
	static float mem_result(0);

	if (input_string == "") { output_expressions.push_back(""); return; }
	
	if (FindRusLiteral(input_string)) {
		throw "StringParsing: Error. Invalid expression\n";
	}

	input_string.erase(						//Erase spaces
		std::remove_if(input_string.begin(), input_string.end(), isspace),
		input_string.end());

    std::replace(input_string.begin(), input_string.end(), ',','.');

	exprcontainer_t splitted_formulas;
	SplitString(input_string, splitted_formulas, ';');

	for (auto formula : splitted_formulas) {
		output_expressions.push_back(StringParsing(formula, mem_result));
	}
}

std::string StringParsing(std::string input_string, float& result) {

	expresson_t input_formula;
	input_formula.clear();
	input_formula.str(input_string);

	std::string var_name;

	if (input_string == "q") exit(1);
	if (input_string == "cls") { system("cls"); Presentation();  return ""; }
	if (input_string == "help") { DispHelp();  return ""; }

	if (WriteMemory(input_formula, result, g_calc_memory)) {
		return ResultFormat(input_string, result, precision);
	}
	else if (WriteVariable(input_formula, g_var_memory, var_name, result)) {
		return ResultFormat(var_name, result, precision);
	}
	else {
		result = RecognitionLvl0(input_formula);
		if (input_formula.peek() != -1) { throw "StringParsing: Error. Invalid expression!\n"; }
		return ResultFormat(input_string, result, precision);
	}
}

std::string ResultFormat(std::string input_string, float& result, double precision) {
	std::stringstream output_stream;
	output_stream << input_string << " = ";
	if (abs(result) > pow(10, -(precision-1))){
		if (fmod(abs(result), 1) > pow(10, -precision)) {
			output_stream << std::setprecision(precision) << std::fixed << result << "\n";
		}
		else {
			output_stream << std::setprecision(0) << std::fixed << result << "\n";
		}
	}
	else {
		if (result == 0) { 
			output_stream << result << "\n";
		}
		else {
			output_stream << std::setprecision(precision) << std::scientific << result << "\n";
		}
	}
	return output_stream.str();

}

void SplitString(const std::string& str, exprcontainer_t& cont, char delim){
	std::stringstream tmp_ss(str);
	std::string token;
	while (std::getline(tmp_ss, token, delim)) {
		cont.push_back(token);
	}
}

float RecognitionLvl0(expresson_t& expression) {
	return RecognitionLvl1(expression, RecognitionLvl2(expression, RecognitionLvl3(expression, RecognitionLvl4(expression))));
}

float RecognitionLvl1(expresson_t& expression, float left_operand) {
	char check_char = expression.peek();
	if (check_char == -1) return left_operand;
	if (check_char != '+' && check_char != '-') {
		return left_operand;                                //Return unused operand
	}
	expression.get();
	float right_operand = RecognitionLvl2(expression, RecognitionLvl3(expression, RecognitionLvl4(expression)));
	if (check_char == '+') {
		return RecognitionLvl1(expression, left_operand + right_operand);
	}
	else if (check_char == '-') {
		return RecognitionLvl1(expression, left_operand - right_operand);
	}

}

float RecognitionLvl2(expresson_t& expression, float left_operand){
    char check_char = expression.peek();
    if (check_char != '*' && check_char != '/') {
        return left_operand;                                //Return unused operand
    }

    expression.get();
    float right_operand = RecognitionLvl3(expression, RecognitionLvl4(expression));
    if (check_char == '*'){
        return RecognitionLvl2(expression, left_operand*right_operand);
    }
    else if (check_char == '/') {
        if (right_operand == 0) { throw "RecognitionLvl2: Error. Divide by zero\n"; }
        return RecognitionLvl2(expression, left_operand/right_operand);
    }
}

float RecognitionLvl3(expresson_t& expression, float left_operand) {
	char check_char = expression.peek();
	if (check_char != '^') {
		return left_operand;                                //Return unused operand
	}
	expression.get();

	float right_operand = RecognitionLvl4(expression);
	if (check_char == '^') {
		return RecognitionLvl3(expression, pow(left_operand, right_operand));
	}
}

float RecognitionLvl4(expresson_t& expression) {
    char check_char = expression.peek();    //Get char and put back
    if (check_char == -1) return 0;
    if (check_char == 'M') {
        return ReadMemory(expression, g_calc_memory);
    };
    if (std::isdigit(check_char)) {
        float num;
        expression >> num;
        return num;
    }else if (check_char == '(') {
        expression.get();                   //Delete '(' from stream
        float result = RecognitionLvl0(expression);
        if (expression.get() == ')') return result;
        throw "RecognitionLvl4: Error. Invalid symbol\n";
    }else if (check_char == '-') {                //Negative numbers
        expression.get();
        return -1* RecognitionLvl4(expression);
    }else if (check_char == '+') {                //+ more than one
        expression.get();
        return RecognitionLvl4(expression);
    }else if (std::isalpha(check_char)) {
        return MathFormulas(expression);
    //}else if (check_char == ',') {                //In case mod(a,b)
    //    expression.get();
    //    if (std::isdigit(expression.peek())) {
    //        return RecognitionLvl4(expression);
    //    }
    //    else if(std::isalpha(expression.peek())){
    //        return MathFormulas(expression);
    //    }
    //    throw "RecognitionLvl4: Error. Invalid symbol\n";
    }
    throw "Factor: Error. Invalid symbol\n";
    return 0;
}

float MathFormulas(expresson_t& expression){
    FuncLib local_func_lib;

	char buff[10];
    std::string math_formula;

    while (std::isalnum(expression.peek())) {
        math_formula.push_back(expression.get());
    }

	float constant = local_func_lib.FindConstant(math_formula);
	if (constant != 0) { return constant; }

	FuncLib::floatfunc1_t func1 = local_func_lib.FindFunc1(math_formula);
	FuncLib::floatfunc2_t func2 = local_func_lib.FindFunc2(math_formula);

	float result;
	if (func1 != nullptr) {
		float tmp = func1(RecognitionLvl4(expression));
		return tmp;
	}

	if (func2 != nullptr) {
		expression.get();	//get '('
		float left_operand = RecognitionLvl4(expression);
		expression.get();	//get ','
		float right_operand = RecognitionLvl4(expression);
		expression.get();   //get ')'
		return (func2(left_operand, right_operand));
	}

	expresson_t tmp_expression;
	tmp_expression.str(math_formula);
	return ReadVariable(tmp_expression, g_var_memory);

    throw "MathFormulas: Error. Ivalid formula\n";
}

float ReadMemory(expresson_t& expression, Memory& memory)
{
    std::string mem_command;
    mem_command.push_back(expression.get());
    mem_command.push_back(expression.get());

    if (mem_command == "MR"){
		size_t cell = 0;
		if (expression.peek() == '[') {
            expression.get();
            cell = RecognitionLvl4(expression);
            if (cell > 20) {
				throw "MathFormulas: Error. Not valid cell id";
			}
            if (expression.peek() != ']') {
				throw "MathFormulas: Error. Invalid symbols\n";
			}
            expression.get();
        }
        return memory.Get(cell);
    }
}

bool WriteMemory(expresson_t& input_expression, float value, Memory& memory) {
	expresson_t expression;
	expression.str(input_expression.str());	//Copy

	std::string mem_command;
    mem_command.push_back(expression.get());
    mem_command.push_back(expression.get());

    if (mem_command == "MW") {
        size_t cell = 0;
        if (expression.peek() == '[') {
            expression.get();
            cell = RecognitionLvl4(expression);
            if (cell > 20) { throw "MathFormulas: Error. Not valid cell id"; }
            if (expression.peek() != ']') { throw "MathFormulas: Error. Invalid symbols"; }
            expression.get();
        }
		memory.Put(value, cell);
        return 1;
    }
    return 0;

}

bool WriteVariable(expresson_t& input_expression, variables_t& g_var_memory, std::string& var_name, float& var_value) {
	expresson_t expression;
	expression.str(input_expression.str());	//Copy

	std::string name;

	if (!std::isalnum(expression.peek())) { return 0; }
	while (std::isalnum(expression.peek()) && expression.peek() != '=' && expression.peek() != -1) {
		name.push_back(expression.get());
	}

	FuncLib local_func_lib;
	float constant = local_func_lib.FindConstant(name);
	FuncLib::floatfunc1_t func1 = local_func_lib.FindFunc1(name);
	FuncLib::floatfunc2_t func2 = local_func_lib.FindFunc2(name);


	if (name == "MW"  || name == "MR" ||
		constant != 0 || func1 != nullptr || func2 != nullptr) {
		return 0;
	}

	if (expression.peek() != '=') {
		return 0;
	}
	else {
		expression.get();	//Extract '='
	}

	float value = RecognitionLvl0(expression);

	variables_t::iterator it = g_var_memory.find(name);
	if (it != g_var_memory.end()) {	//if variable already exist
		it->second = value;
	}
	else {
		g_var_memory.insert(std::pair<std::string, float>(name, value));
	}

	var_name = name;
	var_value = value;

	return 1;
}

float ReadVariable(expresson_t& expression, variables_t& g_var_memory)
{
	std::string name;
	while (std::isalnum(expression.peek())) {
		name.push_back(expression.get());
	}
	variables_t::iterator it = g_var_memory.find(name);
	if (it != g_var_memory.end()) {
		return (it->second);
	}
	else {
		throw "ReadVariable: Error. Invalid variable name.\n";
	}
}

FuncLib::floatfunc1_t FuncLib::FindFunc1(std::string function_name) {
	funclib1_t::iterator it1 = functions_arg1.find(function_name);

	if (it1 != functions_arg1.end()) {
		return (it1->second);
	}
	else {
		return nullptr;
	}
}

FuncLib::floatfunc2_t FuncLib::FindFunc2(std::string function_name) {
	FuncLib::funclib2_t::iterator it2;
	it2 = functions_arg2.find(function_name);
	if (it2 != functions_arg2.end()) {
		return (it2->second);
	}
	else {
		return nullptr;
	}
}

float FuncLib::FindConstant(std::string function_name) {
	FuncLib::constant_t::iterator it_c;
	it_c = constants.find(function_name);
	if (it_c != constants.end()) {
		return (it_c ->second);
	}
	else {
		return 0;
	}
}

void DispResult(exprcontainer_t output_expressions) {
	std::cout << "\nans: \n\n";
	for (auto output_string : output_expressions) {
		std::cout << "  "<< output_string << " \n";
	}
	std::cout << "_______________________________\n\n";
}

void Presentation() {
	std::cout << "+++++++++++++++++++++++++++++++++\n";
	std::cout << "+                               +\n";
	std::cout << "+ Calculator 2019. Author: iVBk +\n";
	std::cout << "+                               +\n";
	std::cout << "+++++++++++++++++++++++++++++++++\n";
	std::cout << "\n";
	std::cout << "Enter \"help\" for documenation.\n";
	std::cout << "\nEnter the expression:" << "\n";
}

void DispHelp() {
	std::cout << "\n";
	std::cout << "+++++++++++++++++++++++++++++++++\n";
	std::cout << "+              HELP             +\n";
	std::cout << "+++++++++++++++++++++++++++++++++\n";
	std::cout << "\n";
	std::cout << "Here is describing how you can use it.\n\n";
	std::cout << "Incredible main features:\n";
	std::cout << "    + - * / ^\n";
	std::cout << "..................................\n\n";
	std::cout << "Think it all? NO!\n";
	std::cout << "You can calculate:\n";
	std::cout << "\nTrigonometric functions:\n";
	std::cout << "    cos, sin, tan, acos,asin,atan\n";
	std::cout << "\nExponential and logarithmic functions:\n";
	std::cout << "    log, log2, log10, exp, erf\n";
	std::cout << "\nRounding:\n";
	std::cout << "    round, ceil, floor\n";
	std::cout << "\nMinimum, maximum, difference functions:\n";
	std::cout << "    mod(a,b),max(a,b),min(a,b)\n";
	std::cout << "..................................\n\n";
	std::cout << "And it not all!\n";
	std::cout << "You can store calculations in memory:\n";
	std::cout << "  MW, MW[k] - add to storage\n";
	std::cout << "  MR, MR[k] - get from storage\n";
	std::cout << "\nYou can create own variable:\n";
	std::cout << "**name must begin with a letter [A-Z,a-z]\n\
				  \r  and must consist of [A-Z,a-z,0-9]:\n";
	std::cout << "example:\n    a = 10;    b = 20;\n    a + b = 30\n";
	std::cout << "..................................\n";
	std::cout << "\nOperations can be divided by ';'\n";
	std::cout << "..................................\n";
	std::cout << "Exit: 'q'. Clear screen: \"cls\" \n";
	std::cout << "\nSimple emaple:\n\
				  \r    10*log10(2); MW[1];\n\
				  \r    10*log10(10);MW[2]\n\
				  \r    MR[1]+MR[2]\n\n";
	std::cout << "\nEnter the expression:" << "\n";
}

bool FindRusLiteral(std::string str) {
	bool result = 0;
	for (char &ch : str)
		result |= ((ch >= 'À' && ch <= 'ß') || (ch >= 'à' && ch <= 'ÿ'));
	return result;
}


