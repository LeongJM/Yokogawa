/**
* Author:           Leong Jun Ming
* Date:             24/10/25
* Description:      Handles the conversion of the input and calculations
**/

#ifndef BC_CALCULATION_H
#define BC_CALCULATION_H

#include <array>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <functional>
#include <memory>

class BC_Calculator
{
	typedef std::tuple<std::string, std::string, std::string> CTokens;
	typedef std::function<long double(const long double&, const long double&)> OpFunc;
	typedef std::map<char, OpFunc> Operators;
	
	std::vector<std::pair<std::string, long double>> _history;

	static std::unique_ptr<Operators> _operations;

	// Adds all operations
	void AddOperations();
	// Could probably move to Public if want others to add more funcs
	bool AddOperation(char op, OpFunc fn);
	// Tokenizes the full string input into three parts
	CTokens Tokenize(const std::string& str);

public:
	BC_Calculator();
	~BC_Calculator();

	// Calculates a result with a given input string
	long double Calculate(const std::string& str);

	// Gets the full History, or a single calculation and result
	std::vector<std::pair<std::string, long double>> GetHistory(size_t maxCalcs = 0) const;

	void AddToHistory(std::string input, long double output);
	
};

#endif // !CALCULATION_H

