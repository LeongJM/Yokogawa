#include <iostream>
#include "UI/BC_UI.h"
#include "Calculations/BC_Calculation.h"
#include "ErrorHandling/BC_ErrorHandling.h"

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
    }

    return 0;
}
