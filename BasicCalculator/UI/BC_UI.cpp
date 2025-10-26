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
	std::string ret = (_first ? "Enter your next calculation: " : "Enter your calculation. eg. 123+456");
	_first = true;
	return ret;
}

const std::string BC_ConsoleUI::UI_DisplayResult(double result)
{
	return "Result: " + std::to_string(result);
}

const std::string BC_ConsoleUI::UI_Failure(const BC_Exception& e) const
{
	return "Failure: " + std::string(e.type()) + " " + std::string(e.what());
}

const std::string BC_ConsoleUI::UI_History(const std::vector<std::pair<std::string, double>> history)
{
	return std::string();
}

const std::string BC_ConsoleUI::UI_History(const std::pair<std::string, double> history)
{
	return std::string();
}
