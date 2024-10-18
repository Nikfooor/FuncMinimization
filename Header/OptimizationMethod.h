#pragma once
#include "Function.h"
#include "Area.h"
#include "StopCriteria.h"
#include <random>

/**
 * \class OptimizationMethod
 * \brief Abstract base class for optimization methods.
 *
 * This class serves as a base for different optimization algorithms.
 * It defines the interface for optimizing a function within a specified area.
 */
class OptimizationMethod
{
public:
	OptimizationMethod(const VectorX &startPoint);
	virtual ~OptimizationMethod();
	/**
	 * \brief Optimizes the given function within the specified area.
	 * \param area The area within which to optimize the function.
	 * \param f The function to be optimized.
	 * \param criteria The stopping criteria for the optimization.
	 */
	virtual void optimise(Area &area, const Function &f, const StopCriteria &criteria) = 0;
	/**
	 * \brief Retrieves the name of the optimization method.
	 * \return A string representing the name of the optimization method.
	 */
	virtual std::string getName() = 0;
	/**
	 * \brief Retrieves the best point found during optimization.
	 *
	 * \return The best point found as a VectorX.
	 */
	VectorX getBestPoint();
	/**
	 * \brief Retrieves the number of iterations performed during optimization.
	 *
	 * \return The number of iterations made as a size_t.
	 */
	size_t getIterNum();

protected:
	std::vector<VectorX> points; ///< Stores the points explored during optimization.
	size_t iterMade;			 ///< The number of iterations completed.
};

/**
 * \class AdamGradientDescent
 * \brief Implementation of the Adam gradient descent optimization method.
 *
 * This class implements the Adam optimization algorithm.
 */
class AdamGradientDescent : public OptimizationMethod
{
public:
	/**
	 * \brief Constructor for AdamGradientDescent.
	 *
	 * Initializes the Adam optimizer with specified parameters.
	 *
	 * \param startPoint The starting point for the optimization as a VectorX.
	 * \param alpha The learning rate.
	 * \param beta1 The exponential decay rate for the first moment estimates.
	 * \param beta2 The exponential decay rate for the second moment estimates.
	 * \param epsilon A small constant to prevent division by zero.
	 */
	AdamGradientDescent(const VectorX &startPoint, double alpha, double beta1, double beta2, double epsilon);
	~AdamGradientDescent();
	virtual void optimise(Area &area, const Function &f, const StopCriteria &criteria) override;
	virtual std::string getName() override;

private:
	double alpha;	///< The learning rate.
	double beta1;	///< The decay rate for the first moment.
	double beta2;	///< The decay rate for the second moment.
	double epsilon; ///< Small constant to prevent division by zero.
};

/**
 * \class RandomSearch
 * \brief Implementation of the Random Search optimization method.
 *
 * This class implements a random search optimization algorithm.
 */
class RandomSearch : public OptimizationMethod
{
public:
	/**
	 * \brief Constructor for RandomSearch.
	 *
	 * Initializes the random search optimizer with specified parameters.
	 *
	 * \param startPoint The starting point for the optimization as a VectorX.
	 * \param alpha The scaling factor for search steps.
	 * \param p The probability of selecting the entire area to generate a random point.
	 * \param delta Radius of the neighborhood.
	 */
	RandomSearch(const VectorX startPoint, double alpha, double p, double delta);
	~RandomSearch();
	virtual void optimise(Area &area, const Function &f, const StopCriteria &criteria) override;
	virtual std::string getName() override;

private:
	double alpha;	  ///< The scaling factor for search steps.
	double p;		  ///< The probability of selecting the entire area to generate a random point.
	double delta;	  ///< Radius of the neighborhood.
	std::mt19937 gen; ///< Random number generator.
};

/**
 * \class ClassicGradientDescent
 * \brief Implementation of the Classic Gradient Descent optimization method.
 *
 * This class implements the standard gradient descent optimization algorithm.
 */
class ClassicGradientDescent : public OptimizationMethod
{
public:
	/**
	 * \brief Constructor for ClassicGradientDescent.
	 *
	 * Initializes the classic gradient descent optimizer with a starting point.
	 *
	 * \param startPoint The starting point for the optimization as a VectorX.
	 */
	ClassicGradientDescent(const VectorX &startPoint);
	~ClassicGradientDescent();
	virtual void optimise(Area &area, const Function &f, const StopCriteria &criteria) override;
	virtual std::string getName() override;

private:
	/**
	 * \brief Calculates the optimal alpha for the function at the given point.
	 *
	 * \param func The function for which to calculate the optimal alpha.
	 * \param point The current point at which the alpha is calculated.
	 * \param maxAlpha The maximum alpha allowed.
	 * \return The optimal alpha.
	 */
	double alphaOptimization(const Function &func, const VectorX &point, const double maxAlpha);
	/**
	 * \brief Gets the maximum alpha allowed based on the area and function.
	 *
	 * \param area The area within which to optimize.
	 * \param func The function being optimized.
	 * \param point The current point at which the maximum alpha is calculated.
	 * \return The maximum alpha allowed.
	 */
	double getMaxAlpha(Area &area, const Function &func, const VectorX &point);

private:
	double alpha; ///< The step size for the gradient descent
};