#include "Function.h"
#include "OptimizationMethod.h"
#include <chrono>

using namespace std;

string printStat(const std::shared_ptr<OptimizationMethod> method, const std::shared_ptr<Function> &f, Area &area, const std::shared_ptr<StopCriteria> cr, const VectorX &startPoint)
{
	std::stringstream output;
	output << endl
		   << "OPTIMIZATION" << endl;
	auto start = std::chrono::high_resolution_clock::now();
	method->optimise(startPoint, area, *f, *cr);
	auto end = std::chrono::high_resolution_clock::now();
	output << method->getName() << endl;
	output << "Start point: " << startPoint << endl;
	output << "Best point: " << method->getBestPoint() << endl;
	output << "Value of " + f->getName() + " function: " << (*f)(method->getBestPoint()) << endl;
	output << method->getIterNum() << " iteration made" << endl;
	std::chrono::duration<double> duration = end - start;
	output << "Execution time: " << duration.count() << " seconds" << endl
		   << "OPTIMIZATION" << endl
		   << endl;
	cout << output.str();
	return output.str();
}

class InvalidInputException : public std::runtime_error
{
public:
	explicit InvalidInputException(const std::string &message)
		: std::runtime_error(message) {}
};

int safeInputInt(const string &prompt, int minValue, int maxValue)
{
	int value;
	while (true)
	{
		try
		{
			cout << prompt;
			cin >> value;
			if (cin.fail() || value < minValue || value > maxValue)
			{
				throw InvalidInputException("Incorrect input. Try again.");
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return value;
		}
		catch (const InvalidInputException &exc)
		{
			cout << exc.what() << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

double safeInputDouble(const string &prompt)
{
	double value;
	while (true)
	{
		try
		{
			cout << prompt;
			cin >> value;
			if (cin.fail())
			{
				throw InvalidInputException("Incorrect input. Try again.");
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return value;
		}
		catch (const InvalidInputException &exc)
		{
			cout << exc.what() << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

std::shared_ptr<Function> chooseFunction()
{
	cout << "Select the function to optimize:" << endl;

	Function1 func1;
	Function2 func2;
	Function3 func3;
	Function4 func4;
	Function5 func5;
	Function6 func6;

	cout << "1. " << func1.getName() << ": dim = " << func1.getDim() << endl;
	cout << "2. " << func2.getName() << ": dim = " << func2.getDim() << endl;
	cout << "3. " << func3.getName() << ": dim = " << func3.getDim() << endl;
	cout << "4. " << func4.getName() << ": dim = " << func4.getDim() << endl;
	cout << "5. " << func5.getName() << ": dim = " << func5.getDim() << endl;
	cout << "6. " << func6.getName() << ": dim = " << func6.getDim() << endl;

	int funcChoice = safeInputInt("Your choice: ", 1, 6);

	switch (funcChoice)
	{
	case 1:
		return std::make_shared<Function1>();
	case 2:
		return std::make_shared<Function2>();
	case 3:
		return std::make_shared<Function3>();
	case 4:
		return std::make_shared<Function4>();
	case 5:
		return std::make_shared<Function5>();
	case 6:
		return std::make_shared<Function6>();
	default:
		cout << "Incorrect function selection." << endl;
	}
	return nullptr;
}

std::vector<std::pair<double, double>> safeInputBounds(size_t dim)
{
	cout << "Enter the boundaries of the search area (min and max for each coordinate):" << endl;
	std::vector<std::pair<double, double>> bounds;
	for (size_t i = 0; i < dim; ++i)
	{
		cout << "Coordinate " << i + 1 << ":" << endl;
		double min = safeInputDouble("  min: ");
		double max = safeInputDouble("  max: ");
		if (min >= max)
		{
			cout << "Error: min cannot be greater than max. Repeat the input for this coordinate." << endl;
			--i;
		}
		else
		{
			bounds.emplace_back(min, max);
		}
	}
	return bounds;
}

VectorX safeInputVectorX(size_t dim)
{
	cout << "Enter the starting point (by " << dim << " coordinates):" << endl;
	VectorX point(dim);
	for (size_t i = 0; i < dim; ++i)
	{
		point[i] = safeInputDouble("Coordinate " + to_string(i + 1) + ": ");
	}
	return point;
}

shared_ptr<StopCriteria> inputStopCriteria()
{
	cout << "Select a stopping criterion:" << endl;
	cout << "1. GradNormStopCriteria" << endl;
	cout << "2. DifferenceNormStopCriteria" << endl;
	cout << "3. FuncDifferenceNormStopCriteria" << endl;

	int critChoice = safeInputInt("Your choice ", 1, 3);
	double eps = safeInputDouble("Enter precision (eps): ");
	size_t maxIter = safeInputInt("Enter the maximum number of iterations: ", 1, 100000000);

	std::shared_ptr<StopCriteria> criteria;
	switch (critChoice)
	{
	case 1:
		criteria = std::make_shared<GradNormStopCriteria>(eps, maxIter);
		break;
	case 2:
		criteria = std::make_shared<DifferenceNormStopCriteria>(eps, maxIter);
		break;
	case 3:
		criteria = std::make_shared<FuncDifferenceNormStopCriteria>(eps, maxIter);
		break;
	default:
		throw InvalidInputException("Incorrect choice of stopping criterion.");
	}
	return criteria;
}

shared_ptr<OptimizationMethod> inputOptimizationMethod()
{
	cout << "Select an optimization method:" << endl;
	cout << "1. AdamGradientDescent" << endl;
	cout << "2. ClassicGradientDescent" << endl;
	cout << "3. RandomSearch" << endl;

	int methodChoice = safeInputInt("Your choice ", 1, 3);
	std::shared_ptr<OptimizationMethod> method;

	switch (methodChoice)
	{
	case 1:
	{
		double alpha = safeInputDouble("Input alpha: ");
		double beta1 = safeInputDouble("Input beta1: ");
		double beta2 = safeInputDouble("Input beta2: ");
		double epsilon = safeInputDouble("Input epsilon: ");
		method = make_shared<AdamGradientDescent>(alpha, beta1, beta2, epsilon);
		break;
	}
	case 2:
		method = make_shared<ClassicGradientDescent>();
		break;
	case 3:
	{
		double randAlpha = safeInputDouble("Input alpha: ");
		double p = safeInputDouble("Input p: ");
		double delta = safeInputDouble("Input delta: ");
		method = make_shared<RandomSearch>(randAlpha, p, delta);
		break;
	}
	default:
		throw InvalidInputException("Incorrect choice of optimization method.");
	}
	return method;
}

int main()
{
	std::shared_ptr<Function> f = chooseFunction();

	size_t dim = f->getDim();
	std::vector<std::pair<double, double>> bounds = safeInputBounds(dim);
	Area area(bounds);

	VectorX startPoint = safeInputVectorX(dim);

	shared_ptr<StopCriteria> criteria = inputStopCriteria();

	shared_ptr<OptimizationMethod> method = inputOptimizationMethod();

	vector<string> results;

	while (true)
	{
		cout << "You have entered the following parameters:" << endl;
		cout << "1. Function " << f->getName() << " (dim: " << f->getDim() << ")" << endl;
		cout << "2. Area Boundaries: ";
		for (size_t i = 0; i < bounds.size(); ++i)
		{
			cout << "[" << bounds[i].first << ", " << bounds[i].second << "] ";
		}
		cout << endl;
		cout << "3. Start point " << startPoint << endl;
		cout << "4. Stopping criterion: " << criteria->getName() << endl;
		cout << "5. Optimization Method: " << method->getName() << endl;
		cout << "6. Start optimization" << endl;
		cout << "7. Print all results" << endl;
		cout << "0. Exit" << endl;

		int choice = safeInputInt("Select what you want to change (0-6): ", 0, 7);

		switch (choice)
		{
		case 0:
			cout << "Exit" << endl;
			return 0;
		case 1:
			f = chooseFunction();
			dim = f->getDim();
			bounds = safeInputBounds(dim);
			area = Area(bounds);
			startPoint = safeInputVectorX(dim);
			break;
		case 2:
			bounds = safeInputBounds(dim);
			area = Area(bounds);
			break;
		case 3:
			startPoint = safeInputVectorX(dim);
			break;
		case 4:
			criteria = inputStopCriteria();
			break;
		case 5:
			method = inputOptimizationMethod();
			break;
		case 6:
			results.push_back(printStat(method, f, area, criteria, startPoint));
			break;
		case 7:
			if (results.empty())
			{
				cout << "No results yet. Do the optimization first." << endl;
			}
			else
			{
				cout << "Optimization results:" << endl;
				for (const auto &result : results)
				{
					cout << result;
				}
			}
		}
	}
}
