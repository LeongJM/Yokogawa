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
        std::cout << bcui.UI_Introduction() << std::endl;
        std::cin >> str;
        if (str == "exit")
        {
            std::cout << "Ending Calculator Program." << std::endl;
            break;
        }
        try
        {
            bcui.UI_DisplayResult(bccc.Calculate(str));
        }
        catch (const BC_Exception& e)
        {
            bcui.UI_Failure(e);
        }
    }

    return 0;
}
