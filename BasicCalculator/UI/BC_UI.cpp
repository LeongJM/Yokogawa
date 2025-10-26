/**
* Author:           Leong Jun Ming
* Date:             24/10/25
* Description:      Handles the display of Console elements
**/

#include "BC_UI.h"

BC_ConsoleUI::BC_ConsoleUI()
{
}

BC_ConsoleUI::~BC_ConsoleUI()
{
}

const std::string BC_ConsoleUI::UI_Introduction()
{
	std::string ret = (!_first ? 
		"Hello! This is a calculator Program."
		"\nPlease enter \"exit\" to exit this program."
		"\nYou may use Addition [+], Subtraction [-], Multiplication [*], Division [/], Power[^], and Root[~]."
		"\nExamples: 1+1, 2-1, 3*2, 4^2, 5~2"
		"\nYou may also use Decimals and Exponents. Whitespaces may be used to separate Input values."
		"\nExamples: 1.5e10 * 3"
		"\nPlease enter your next calculation: " 
		: 
		"Please enter your next calculation: ");
	_first = true;
	return ret;
}

const std::string BC_ConsoleUI::UI_DisplayResult(long double result)
{
	return "Result: " + std::to_string(result) + '\n' + "==============================";
}

const std::string BC_ConsoleUI::UI_Failure(const BC_Exception& e) const
{
	return "Failure: " + std::string(e.type()) + " " + std::string(e.what()) + '\n' + "==============================";
}

const std::string BC_ConsoleUI::UI_History(const std::vector<std::pair<std::string, long double>> history)
{
	if (history.size() > 0)
	{
		std::string calcStr = { "Calculations: " };
		for (std::pair<std::string, long double> h : history)
		{
			calcStr += '\n' + h.first + "=" + std::to_string(h.second);
		}
		calcStr += +"\n==============================";
		return calcStr;
	}
	return "No History found!";
}

const std::string BC_ConsoleUI::UI_Exit()
{
	return "Ending Calculator Program.";
}
