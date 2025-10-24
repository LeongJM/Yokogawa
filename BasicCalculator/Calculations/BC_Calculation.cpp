/**
* Author:           Leong Jun Ming
* Date:             24/10/25
* Description:      Handles the conversion of the input and calculations
**/

#include "BC_Calculation.h"
#include "../ErrorHandling/BC_ErrorHandling.h"

BC_Calculator::BC_Calculator()
{

}

BC_Calculator::~BC_Calculator()
{

}

BC_Calculator::CTokens BC_Calculator::Tokenize(const std::string& str)
{
	return std::make_tuple("", "", "");
}

double BC_Calculator::Calculate(const std::string& str)
{
	CTokens tokens = Tokenize(str);
	std::string opVal = std::get<1>(tokens);
	switch (ConvertStringToOp(opVal))
	{
	case OperationType::Plus:
		break;
	case OperationType::Minus:
		break;
	case OperationType::Multiply:
		break;
	case OperationType::Divide:
		break;
	case OperationType::Power:
		break;
	case OperationType::SquareRoot:
		break;
	default:
		break;
	}
	return 0.0;
}

double BC_Calculator::ReturnLastResult() const
{
	return 0.0;
}

const std::vector<std::pair<std::string, double>>& BC_Calculator::GetHistory() const
{
	// TODO: insert return statement here
	return _history;
}

const double BC_Calculator::GetHistory(int howManyPrev) const
{
	return 0.0;
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
		return OperationType::SquareRoot;
	}
	return OperationType::Undefined;
}
