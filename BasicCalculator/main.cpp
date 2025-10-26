/**
* Author:           Leong Jun Ming
* Date:             24/10/25
* Description:      Main File for Calculator
**/

#include <iostream>
#include "UI/BC_UI.h"
#include "Calculations/BC_Calculation.h"

int main()
{
    BC_ConsoleUI bcui;
    BC_Calculator bccc;
    
    while (true)
    {
        std::string str;
        std::cout << bcui.UI_Introduction();
        std::getline(std::cin, str);
        if (str.find("exit") != std::string::npos)
        {
            std::cout << bcui.UI_Exit() << std::endl;
            break;
        }
        if (str.find("history") != std::string::npos)
        {
            std::string num = str.substr(7);
            size_t maxView = 0;
            try
            {
                maxView = std::stoi(num);
            }
            catch (const std::exception& e) // Catches if no number or bad input given
            {
                //std::cout << "Invalid number." << std::endl;
                //continue;
            }
            std::cout << bcui.UI_History(bccc.GetHistory(maxView)) << std::endl;
            continue;
        }
        try
        {
            std::cout << bcui.UI_DisplayResult(bccc.Calculate(str)) << std::endl;
        }
        catch (const BC_Exception& e)
        {
            // Catches all Exceptions here
            std::cout << bcui.UI_Failure(e) << std::endl;
        }
    }
        
    return 0;
}
