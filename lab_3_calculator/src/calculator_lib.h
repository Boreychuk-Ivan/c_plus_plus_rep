#pragma once

#include <iostream>
#include <sstream>
#include <cmath>     //Math functions
#include <cctype>	 //isdigit,isalpha,...
#include <algorithm> // remove and remove_if
#include <vector>
#include <limits>
#include <map>
#include <functional>
#include <iterator>

using expresson_t = std::stringstream;
using exprcontainer_t = std::vector<std::string>;
using variables_t = std::map<std::string,float>;


class Memory{
	std::vector<float> mem = {0,0,0,0,0};
public:
	void  Put(float val, const size_t it = 0) { mem[it] = val; }
	float Get(const size_t it = 0) const { return mem.at(it); }
};

class FuncLib {
public:
	using floatfunc1_t = float(*)(float);
	using floatfunc2_t = float(*)(float,float);

	using constant_t = std::map<std::string, float>;
	using funclib1_t = std::map<std::string, floatfunc1_t>;
	using funclib2_t = std::map<std::string, floatfunc2_t>;

private:
	constant_t constants;
	funclib1_t functions_arg1;
	funclib2_t functions_arg2;
public:
	FuncLib() {
		constants["pi"] = 3.14159265358979323846;

		functions_arg1["abs"]  = static_cast<floatfunc1_t>(abs);
		functions_arg1["sqrt"] = static_cast<floatfunc1_t>(sqrt);

		//Trigonometric functions
		functions_arg1["cos"]  = static_cast<floatfunc1_t>(cos);
		functions_arg1["sin"]  = static_cast<floatfunc1_t>(sin);
		functions_arg1["tan"]  = static_cast<floatfunc1_t>(tan);
		functions_arg1["acos"] = static_cast<floatfunc1_t>(acos);
		functions_arg1["asin"] = static_cast<floatfunc1_t>(asin);
		functions_arg1["atan"] = static_cast<floatfunc1_t>(atan);

		//Exponential and logarithmic functions
		functions_arg1["log"]   = static_cast<floatfunc1_t>(log);
		functions_arg1["log2"]  = static_cast<floatfunc1_t>(log2);
		functions_arg1["log10"] = static_cast<floatfunc1_t>(log10);
		functions_arg1["exp"]   = static_cast<floatfunc1_t>(exp);
		functions_arg1["erf"]   = static_cast<floatfunc1_t>(erf);

		//Rounding
		functions_arg1["round"] = static_cast<floatfunc1_t>(round);
		functions_arg1["ceil"]  = static_cast<floatfunc1_t>(ceil);
		functions_arg1["floor"] = static_cast<floatfunc1_t>(floor);

		//Minimum, maximum, difference functions
		functions_arg2["mod"]   = static_cast<floatfunc2_t>(fmod);
		functions_arg2["max"]   = static_cast<floatfunc2_t>(fmax);
		functions_arg2["min"]   = static_cast<floatfunc2_t>(fmin);
	}

	float        FindConstant(std::string function_name);
	floatfunc1_t FindFunc1 (std::string function_name);
	floatfunc2_t FindFunc2 (std::string function_name);
};

std::string StringParsing(std::string input_string, float& result);
std::string ResultFormat(std::string input_string, float& result, double precision = 3);
void SplitString(const std::string& str, exprcontainer_t& cont, char delim);

void StartCalculation(std::string input_string, exprcontainer_t& output_expressions);

bool FindRusLiteral(std::string);

float RecognitionLvl4(expresson_t& expression);     //num () mathformulas
float RecognitionLvl3(expresson_t& expression, float left_operand); // ^
float RecognitionLvl2(expresson_t& expression, float left_operand); // * /
float RecognitionLvl1(expresson_t& expression, float left_operand); // + -
float RecognitionLvl0(expresson_t& expression);		//Input

float MathFormulas(expresson_t& expression);

float ReadMemory(expresson_t& input_expression, Memory& memory);
bool  WriteMemory(expresson_t& input_expression, float value, Memory& memory);


bool  WriteVariable(expresson_t& input_expression, variables_t& g_var_memory, std::string& var_name, float& var_value);
float ReadVariable(expresson_t& input_expression, variables_t& g_var_memory);

void DispResult(exprcontainer_t output_expressions);
void Presentation();
void DispHelp();


