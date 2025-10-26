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
		"Please enter \"exit\" to exit this program.\nPlease Enter your calculation. eg. 123+456 : " 
		: 
		"Please enter your next calculation. eg. 123+456: ");
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
	return std::string();
}

const std::string BC_ConsoleUI::UI_History(const std::pair<std::string, long double> history)
{
	return std::string();
}

const std::string BC_ConsoleUI::UI_Exit()
{
	return "Ending Calculator Program.";
}
