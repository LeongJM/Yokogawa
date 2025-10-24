#ifndef BC_UI_H
#define BC_UI_H

#include <string>

class BC_ConsoleUI
{
public:
	BC_ConsoleUI();
	~BC_ConsoleUI();

	const std::string UI_Introduction() const;
	const std::string UI_Calculation(double result);
	const std::string UI_Failure() const;
};

#endif

