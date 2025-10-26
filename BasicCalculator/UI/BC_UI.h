/**
* Author:           Leong Jun Ming
* Date:             24/10/25
* Description:      Handles the display of Console elements
**/

#ifndef BC_UI_H
#define BC_UI_H

#include <string>
#include <vector>
#include "../ErrorHandling/BC_ErrorHandling.h"

class BC_ConsoleUI
{
	bool _first = false;
public:
	BC_ConsoleUI();
	~BC_ConsoleUI();

	// Prints intro on Console
	const std::string UI_Introduction();
	// Displays final result on Console
	const std::string UI_DisplayResult(long double result);
	// Displays error on Console
	const std::string UI_Failure(const BC_Exception& e) const;
	// Displays History
	const std::string UI_History(const std::vector<std::pair<std::string, long double>> history);
	const std::string UI_History(const std::pair<std::string, long double> history);


	// Prints exit on Console
	const std::string UI_Exit();
};

#endif

