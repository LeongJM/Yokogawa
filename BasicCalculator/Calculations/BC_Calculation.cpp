/**
* Author:           Leong Jun Ming
* Date:             24/10/25
* Description:      Handles the conversion of the input and calculations
**/

#include "BC_Calculation.h"
#include "../ErrorHandling/BC_ErrorHandling.h"
#include <limits>
#include <cmath>

//#include <iostream> // remove

BC_Calculator::BC_Calculator()
{

}

BC_Calculator::~BC_Calculator()
{

}

BC_Calculator::CTokens BC_Calculator::Tokenize(const std::string& str)
{
	std::string substr = str.substr(1); // Ignore first digit, all operations must begin from 2nd digit onwards
	std::size_t found = substr.find_first_of("+-*/^~"); // Find operation char
	if (found == std::string::npos)
	{
		throw BC_Exception(ErrorType::InvalidArg, ""); //Cannot find any
	}

	return std::make_tuple(str.substr(0, found + 1), str.substr(found + 1, 1), str.substr(found + 2));
}

long double BC_Calculator::Calculate(const std::string& str)
{
	CTokens tokens;
	try
	{
		 tokens = Tokenize(str);
	}
	catch (const std::exception& e)
	{
		throw BC_Exception(ErrorType::InvalidArg, e.what());
	}
	std::string opVal = std::get<1>(tokens);

	//std::cout << std::get<0>(tokens) << " : " << std::get<1>(tokens) << " : " << std::get<2>(tokens) << std::endl;

	long double val1 = 0.0f, val2 = 0.0f;
	try
	{
		val1 = std::stold(std::get<0>(tokens));
		val2 = std::stold(std::get<2>(tokens));

		// Uses stold's own checks, so it discards whitespaces and any unnecessary values
		// Add additional checking in to throw if it fails?

		//std::cout << val1 << " : " << val2 << std::endl;
	}
	catch (const std::invalid_argument& e) // Cannot convert to any digits at all
	{
		throw BC_Exception(ErrorType::InvalidArg, e.what());
	}
	catch (const std::out_of_range& e) // Out of range
	{
		throw BC_Exception(ErrorType::OutOfRange, e.what());
	}

	long double finalResult = 0.0f;

	// Operations here
	switch (ConvertStringToOp(opVal))
	{
	case OperationType::Plus:
		// Check if addition will cause overflow
		if (val1 > 0 && val2 > 0 && std::numeric_limits<long double>::max() - val1 < val2)
		{
			throw BC_Exception(ErrorType::OutOfRange, "");
		}
		finalResult = val1 + val2;
		break;
	case OperationType::Minus:
		if (val1 < 0 && val2 < 0 && std::numeric_limits<long double>::min() - val1 < val2)
		{
			throw BC_Exception(ErrorType::OutOfRange, "");
		}
		finalResult = val1 - val2;
		break;
	case OperationType::Multiply:
		if (((val1 > 0 && val2 > 0) || (val1 < 0 && val2 < 0)) && std::numeric_limits<long double>::max() / val1 < val2)
		{
			throw BC_Exception(ErrorType::OutOfRange, "");
		}
		else if (((val1 < 0 && val2 > 0) || (val1 > 0 && val2 < 0)) && std::numeric_limits<long double>::min() / val1 < val2)
		{
			throw BC_Exception(ErrorType::OutOfRange, "");
		}
		finalResult = val1 * val2;
		break;
	case OperationType::Divide:
		if (val2 == 0)
		{
			throw BC_Exception(ErrorType::DivideByZero, "");
		}
		finalResult = val1 / val2;
		break;
	case OperationType::Power:
		finalResult = std::powl(val1, val2);
		if (finalResult == HUGE_VALL || finalResult == -HUGE_VALL)
		{
			throw BC_Exception(ErrorType::OutOfRange, "");
		}
		break;
	case OperationType::Root:
		if (val2 == 0)
		{
			throw BC_Exception(ErrorType::InvalidArg, "");
		}
		finalResult = std::powl(val1, 1/val2);
		if (std::isnan(finalResult))
		{
			throw BC_Exception(ErrorType::OutOfRange, "");
		}
		break;
	default:
		break;
	}

	// Add to History
	std::string insert = std::to_string(val1) + std::get<1>(tokens) + std::to_string(val2);

	AddToHistory(insert, finalResult);
	
	return finalResult;
}

std::vector<std::pair<std::string, long double>> BC_Calculator::GetHistory(size_t maxCalcs) const
{
	if (maxCalcs <= 0)
	{
		return std::vector<std::pair<std::string, long double>>(_history.rbegin(), _history.rend());
	}
	return std::vector<std::pair<std::string, long double>>(_history.rbegin(), _history.rbegin() + std::min(maxCalcs, _history.size()));
}

void BC_Calculator::AddToHistory(std::string input, long double output)
{
	_history.push_back(std::make_pair(input, output));
}

OperationType ConvertStringToOp(const std::string& o)
{
	if (o == "+")
	{
		return OperationType::Plus;
	}
	else if (o == "-")
	{
		return OperationType::Minus;
	}
	else if (o == "*")
	{
		return OperationType::Multiply;
	}
	else if (o == "/")
	{
		return OperationType::Divide;
	}
	else if (o == "^")
	{
		return OperationType::Power;
	}
	else if (o == "~")
	{
		return OperationType::Root;
	}
	return OperationType::Undefined;
}
