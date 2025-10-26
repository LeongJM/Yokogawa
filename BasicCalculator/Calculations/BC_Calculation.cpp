/**
* Author:           Leong Jun Ming
* Date:             24/10/25
* Description:      Handles the conversion of the input and calculations
**/

#include "BC_Calculation.h"
#include "../ErrorHandling/BC_ErrorHandling.h"
#include <limits>
#include <math.h>

#include <iostream> // remove

BC_Calculator::BC_Calculator()
{

}

BC_Calculator::~BC_Calculator()
{

}

BC_Calculator::CTokens BC_Calculator::Tokenize(const std::string& str)
{
	std::string substr = str.substr(1); //Ignore first digit, all operations must begin from 2nd digit onwards
	std::size_t found = str.find_first_of("+-*/^e~");

	return std::make_tuple(str.substr(0, found), str.substr(found, 1), str.substr(found+1));
}

long double BC_Calculator::Calculate(const std::string& str)
{
	CTokens tokens = Tokenize(str);
	std::string opVal = std::get<1>(tokens);

	std::cout << std::get<0>(tokens) << " : " << std::get<1>(tokens) << " : " << std::get<2>(tokens) << std::endl;

	long double val1 = 0.0f, val2 = 0.0f;
	try
	{
		val1 = std::stold(std::get<0>(tokens)); 
		val2 = std::stold(std::get<2>(tokens));
	}
	catch (const std::invalid_argument& e)
	{
		throw BC_Exception(ErrorType::InvalidArg, e.what());
	}
	catch (const std::out_of_range& e)
	{
		throw BC_Exception(ErrorType::OutOfRange, e.what());
	}

	// Operations here
	switch (ConvertStringToOp(opVal))
	{
	case OperationType::Plus:
		// Check if addition will cause overflow
		if (val1 > 0 && val2 > 0 && std::numeric_limits<long double>::max() - val1 < val2)
		{
			throw BC_Exception(ErrorType::OutOfRange, "+ OOR");
		}
		return val1 + val2;
		break;
	case OperationType::Minus:
		if (val1 < 0 && val2 < 0 && std::numeric_limits<long double>::min() - val1 < val2)
		{
			throw BC_Exception(ErrorType::OutOfRange, "- OOR");
		}
		return val1 - val2;
		break;
	case OperationType::Multiply:
		if (((val1 > 0 && val2 > 0) || (val1 < 0 && val2 < 0)) && std::numeric_limits<long double>::max() / val1 < val2)
		{
			throw BC_Exception(ErrorType::OutOfRange, "* OOR");
		}
		else if (((val1 < 0 && val2 > 0) || (val1 > 0 && val2 < 0)) && std::numeric_limits<long double>::min() / val1 < val2)
		{
			throw BC_Exception(ErrorType::OutOfRange, "* -OOR");
		}
		return val1 * val2;
		break;
	case OperationType::Divide:
		if (val2 == 0)
		{
			throw BC_Exception(ErrorType::DivideByZero, "/ DVZ");
		}
		return val1 / val2;
		break;
	case OperationType::Power:
		return powl(val1, val2);
		break;
	case OperationType::Exponent:
		return expl(val1);
		break;
	case OperationType::SquareRoot:
		return sqrtl(val1);
		break;
	default:
		break;
	}
	
	return 0.0;
}

long double BC_Calculator::ReturnLastResult() const
{
	return 0.0;
}

const std::vector<std::pair<std::string, long double>>& BC_Calculator::GetHistory() const
{
	// TODO: insert return statement here
	return _history;
}

const std::pair<std::string, long double> BC_Calculator::GetHistory(int howManyPrev) const
{
	return std::pair<std::string, long double>{ "", 0.0f };
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
	else if (o == "e")
	{
		return OperationType::Exponent;
	}
	else if (o == "~")
	{
		return OperationType::SquareRoot;
	}
	return OperationType::Undefined;
}
