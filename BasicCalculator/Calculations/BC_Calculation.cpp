/**
* Author:           Leong Jun Ming
* Date:             24/10/25
* Description:      Handles the conversion of the input and calculations
**/

#include "BC_Calculation.h"
#include "../ErrorHandling/BC_ErrorHandling.h"
#include <limits>
#include <cmath>
#include <algorithm>

//#include <iostream> // remove

std::unique_ptr<BC_Calculator::Operators> BC_Calculator::_operations = nullptr;

BC_Calculator::BC_Calculator()
{
	// Create new instance
	if (_operations == nullptr)
	{
		_operations = std::make_unique<Operators>();
		AddOperations();
	}
}

BC_Calculator::~BC_Calculator()
{

}

void BC_Calculator::AddOperations()
{
	// Can add all operations here
	AddOperation('+', [](const long double& v1, const long double& v2)
		{
			// Checks for overflow
			if (v1 > 0 && v2 > 0 && std::numeric_limits<long double>::max() - v1 < v2)
			{
				throw BC_Exception(ErrorType::OutOfRange, "");
			}
			return v1 + v2;
		});
	AddOperation('-', [](const long double& v1, const long double& v2)
		{
			if (v1 < 0 && v2 < 0 && std::numeric_limits<long double>::min() - v1 < v2)
			{
				throw BC_Exception(ErrorType::OutOfRange, "");
			}
			return v1 - v2;
		});
	AddOperation('*', [](const long double& v1, const long double& v2)
		{
			if (((v1 > 0 && v2 > 0) || (v1 < 0 && v2 < 0)) && std::numeric_limits<long double>::max() / v1 < v2)
			{
				throw BC_Exception(ErrorType::OutOfRange, "");
			}
			else if (((v1 < 0 && v2 > 0) || (v1 > 0 && v2 < 0)) && std::numeric_limits<long double>::min() / v1 < v2)
			{
				throw BC_Exception(ErrorType::OutOfRange, "");
			}
			return v1 * v2;
		});
	AddOperation('/', [](const long double& v1, const long double& v2)
		{
			// Checks for Divide by 0
			if (v2 == 0)
			{
				throw BC_Exception(ErrorType::DivideByZero, "");
			}
			return v1 / v2;
		});
	AddOperation('^', [](const long double& v1, const long double& v2)
		{
			// Checks for overflow
			long double finalResult = std::powl(v1, v2);
			if (finalResult == HUGE_VALL || finalResult == -HUGE_VALL)
			{
				throw BC_Exception(ErrorType::OutOfRange, "");
			}
			return finalResult;
		});
	AddOperation('~', [](const long double& v1, const long double& v2)
		{
			// Checks for Root by 0
			if (v2 == 0)
			{
				throw BC_Exception(ErrorType::InvalidArg, "");
			}
			long double finalResult = std::powl(v1, 1 / v2);
			if (std::isnan(finalResult))
			{
				throw BC_Exception(ErrorType::OutOfRange, "");
			}

			return finalResult;
		});
}

bool BC_Calculator::AddOperation(char op, OpFunc fn)
{
	return _operations->emplace(op, fn).second;
}

BC_Calculator::CTokens BC_Calculator::Tokenize(const std::string& str)
{
	std::string substr = str.substr(1); // Ignore first digit, all operations must begin from 2nd digit onwards

	// Can theoretically add/remove symbols during runtime so left here instead of pre-defining
	std::string allOpSymbols;
	for (Operators::value_type i : *_operations)
	{
		allOpSymbols += i.first;
	}

	std::size_t found = substr.find_first_of(allOpSymbols); // Find operation char
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
	long double val1 = 0.0l, val2 = 0.0l;

	try
	{
		// Uses stold's own checks, so it discards whitespaces and any unnecessary values
		// Want to have decimals and exponents
		// Only first value gets to be negative number
		std::string token1 = std::get<0>(tokens); std::string token2 = std::get<2>(tokens);
		if (!std::all_of(token1.begin() + (token1[0] == '-'? 1 : 0), token1.end(), [](const char& c) { return::isdigit(c) || c == 'e' || c == '.'; })
			|| !std::all_of(token2.begin(), token2.end(), [](const char& c) { return::isdigit(c) || c == 'e' || c == '.'; }))
		{
			throw BC_Exception(ErrorType::InvalidArg, "");
		}

		val1 = std::stold(token1);
		val2 = std::stold(token2);
		
	}
	catch (const std::invalid_argument& e) // Cannot convert to any digits at all
	{
		throw BC_Exception(ErrorType::InvalidArg, "");
	}
	catch (const std::out_of_range& e) // Out of range
	{
		throw BC_Exception(ErrorType::OutOfRange, "");
	}

	long double finalResult = 0.0f;

	// Runs the correct operation
	Operators::iterator it = _operations->find(opVal[0]);
	if (it == _operations->end())
	{
		throw BC_Exception(ErrorType::InvalidArg, "");
	}
	else
	{
		finalResult = it->second(val1, val2);
	}

	// Add to History
	std::string insert = std::to_string(val1) + std::get<1>(tokens) + std::to_string(val2);

	AddToHistory(insert, finalResult);
	
	return finalResult;
}

std::vector<std::pair<std::string, long double>> BC_Calculator::GetHistory(size_t maxCalcs) const
{
	// Sends History in reverse order
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