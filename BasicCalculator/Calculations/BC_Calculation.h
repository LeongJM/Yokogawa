#ifndef BC_CALCULATION_H
#define BC_CALCULATION_H

#include <queue>
#include <string>

class BC_Calculator
{
	std::vector<std::pair<std::string, double>> _history;

	void Tokenize(std::string str);
public:
	BC_Calculator();
	~BC_Calculator();

	double Calculate(std::string str);

	double ReturnLastResult() const;

	const std::vector<std::pair<std::string, double>>& GetHistory() const;
	const double GetHistory(int howManyPrev = 0) const;
	
};

#endif // !CALCULATION_H

