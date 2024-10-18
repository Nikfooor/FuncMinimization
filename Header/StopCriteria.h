#pragma once
#include <vector>
#include "Function.h"
#include "TransferData.h"

/**
 * \class StopCriteria
 * \brief Abstract base class for stopping criteria in optimization methods.
 *
 * This class serves as a base for different stopping criteria algorithms.
 * It defines the interface for checking if the optimization process should be stopped.
 */
class StopCriteria
{
public:
	/**
	 * \brief Constructor for StopCriteria.
	 *
	 * Initializes the stopping criteria with the given epsilon and maximum iterations.
	 *
	 * \param eps The epsilon value for the stopping criteria.
	 * \param max_iter The maximum number of iterations allowed.
	 */
	StopCriteria(double eps, size_t max_iter);
	~StopCriteria();
	/**
	 * \brief Checks if the optimization process should be stopped.
	 *
	 * This pure virtual function must be overridden by derived classes to
	 * implement specific stopping criteria.
	 *
	 * \param data The transfer data used in the optimization process.
	 * \return True if the optimization should be stopped, false otherwise.
	 */
	virtual bool check(TransferData &data) const = 0;

protected:
	size_t max_iter; ///< The maximum number of iterations allowed.
	double eps;		 ///< The epsilon value for the stopping criteria.
};

/**
 * \class GradNormStopCriteria
 * \brief Implementation of stopping criteria based on gradient norm.
 *
 * This class checks if the optimization process should be stopped based on the norm of the gradient.
 */
class GradNormStopCriteria : public StopCriteria
{
public:
	GradNormStopCriteria(double eps, size_t max_iter);
	~GradNormStopCriteria();
	virtual bool check(TransferData &data) const override;

private:
};

/**
 * \class DifferenceNormStopCriteria
 * \brief Implementation of stopping criteria based on difference norm.
 *
 * This class checks if the optimization process should be stopped based on the norm of the difference between points.
 */
class DifferenceNormStopCriteria : public StopCriteria
{
public:
	DifferenceNormStopCriteria(double eps, size_t max_iter);
	~DifferenceNormStopCriteria();
	virtual bool check(TransferData &data) const override;

private:
};

/**
 * \class FuncDifferenceNormStopCriteria
 * \brief Implementation of stopping criteria based on function difference norm.
 *
 * This class checks if the optimization process should be stopped based on the norm of the difference between function values.
 */
class FuncDifferenceNormStopCriteria : public StopCriteria
{
public:
	FuncDifferenceNormStopCriteria(double eps, size_t max_iter);
	~FuncDifferenceNormStopCriteria();
	virtual bool check(TransferData &data) const override;

private:
};
