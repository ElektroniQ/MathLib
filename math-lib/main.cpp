#include "InfixCalc.hpp"

int main()
{
    InfixCalc calc;

	std::string input;
	std::cout << ">>> Insert equation or define variable:" << std::endl;
	while (1)
	{
		std::cout << "<<< ";

		std::getline(std::cin, input);

		auto equalPos = input.find('=');
		if (equalPos != std::string::npos)
		{
			auto variableName = input.substr(0, equalPos);
			auto variableValue = stod(input.substr(equalPos + 1));
			calc.SetVariable(variableName, variableValue);
			std::cout << ">>> " << "Variable set: " << variableName << "=" << variableValue << std::endl;
		}
		else
		{
			calc.ParseEquation(input);
			auto output = calc.Compute();

			auto errors = calc.GetSyntaxErrors();
			if (errors.size() > 0)
			{
				std::cout << ">>> " << errors << std::endl;
			}
			std::cout << ">>> " << input << "=" << output << std::endl;
		}
	}

    return 0;
}

