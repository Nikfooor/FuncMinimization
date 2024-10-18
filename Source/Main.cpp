#include "Function.h"
#include "OptimizationMethod.h"
#include <chrono>

using namespace std;

void printStat(const std::shared_ptr<OptimizationMethod> method, const std::shared_ptr<Function> &f, Area &area, const std::shared_ptr<StopCriteria> cr, const VectorX &startPoint)
{
	auto start = std::chrono::high_resolution_clock::now();
	method->optimise(area, *f, *cr);
	auto end = std::chrono::high_resolution_clock::now();
	cout << method->getName() << endl;
	cout << "Start point: " << startPoint << endl;
	cout << "Best point: " << method->getBestPoint() << endl;
	cout << "Value of " + f->getName() + " function: " << (*f)(method->getBestPoint()) << endl;
	cout << method->getIterNum() << " iteration made" << endl;
	std::chrono::duration<double> duration = end - start;
	cout << "Execution time: " << duration.count() << " seconds" << endl
		 << endl;
}

int main()
{
	std::vector<std::pair<double, double>> bounds{{-5, 5}, {-5, 5}};
	Area area(bounds);
	VectorX startPoint{2, 1.9};
	std::shared_ptr<StopCriteria> criteria = std::make_shared<DifferenceNormStopCriteria>(1e-8, 1000);
	std::shared_ptr<Function> f = std::make_shared<Function3>();
	std::vector<std::shared_ptr<OptimizationMethod>> methods{
		std::make_shared<AdamGradientDescent>(startPoint, 1, 0.8, 0.99, 1e-8),
		std::make_shared<ClassicGradientDescent>(startPoint)};
	for (auto &method : methods)
		printStat(method, f, area, criteria, startPoint);
	std::shared_ptr<OptimizationMethod> randMethod = std::make_shared<RandomSearch>(startPoint, 0.9, 0.5, 0.1);
	std::shared_ptr<StopCriteria> randCriteria = std::make_shared<DifferenceNormStopCriteria>(1e-8, 1000000);
	printStat(randMethod, f, area, randCriteria, startPoint);
}
