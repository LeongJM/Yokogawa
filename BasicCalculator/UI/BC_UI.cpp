#include "BC_UI.h"

BC_ConsoleUI::BC_ConsoleUI()
{
}

BC_ConsoleUI::~BC_ConsoleUI()
{
}

const std::string BC_ConsoleUI::UI_Introduction() const
{
	return "Enter your calculation. eg. 123+456";
}

const std::string BC_ConsoleUI::UI_Calculation(double result)
{
	return std::string();
}

const std::string BC_ConsoleUI::UI_Failure() const
{
	return std::string();
}
