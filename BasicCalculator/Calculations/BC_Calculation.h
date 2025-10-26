/**
* Author:           Leong Jun Ming
* Date:             24/10/25
* Description:      Handles the conversion of the input and calculations
**/

#ifndef BC_CALCULATION_H
#define BC_CALCULATION_H

#include <queue>
#include <string>
#include <tuple>

enum class OperationType : size_t
{
	Undefined = 255,
	Plus = 0,
	Minus,
	Multiply,
	Divide,
	Power,
	SquareRoot,
};

OperationType ConvertStringToOp(const std::string& o);

class BC_Calculator
{
	typedef std::tuple<std::string, std::string, std::string> CTokens;
	
	std::vector<std::pair<std::string, long double>> _history;

	// Tokenizes the full string input into three parts
	CTokens Tokenize(const std::string& str);
public:
	BC_Calculator();
	~BC_Calculator();

	// Calculates a result with a given input string
	long double Calculate(const std::string& str);

	// Returns the last calculated result
	long double ReturnLastResult() const;

	// Gets the full History, or a single calculation and result
	const std::vector<std::pair<std::string, long double>>& GetHistory() const;
	const std::pair<std::string, long double> GetHistory(int index = 0) const;
	
};

#endif // !CALCULATION_H

