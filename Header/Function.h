#pragma once

#include <string>
#include "VectorX.h"
#include <cmath>
#include <stdexcept>
#include <memory>

/**
 * \class Function
 * \brief Abstract base class for mathematical functions.
 *
 * This class provides an interface for mathematical functions, including
 * methods to calculate the function value and its gradient.
 */
class Function
{
public:
	Function() : dimension(0), name("") {}
	virtual ~Function() {};
	/**
	 * \brief Get the dimension of the function.
	 *
	 * \return The dimension of the function.
	 */
	size_t getDim() const { return dimension; }
	/**
	 * \brief Get the name of the function.
	 *
	 * \return The name of the function.
	 */
	std::string getName() const { return name; }
	/**
	 * \brief Calculate the value of the function at a given point.
	 *
	 * This operator must be implemented by derived classes.
	 *
	 * \param x The point at which to evaluate the function.
	 * \return The value of the function at point x.
	 */
	virtual double operator()(const VectorX &x) const = 0;
	/**
	 * \brief Gradient of the function.
	 *
	 * This function calculates the gradient of the function at a given point.
	 *
	 * \param x The point at which the gradient is calculated.
	 * \return The gradient of the function at point x.
	 */
	virtual VectorX grad(const VectorX &x) const = 0;
	/**
	 * \brief Clone the function.
	 *
	 * This method creates a copy of the function and returns it as a shared pointer.
	 *
	 * \return A shared pointer to a new instance of the function.
	 */
	virtual std::shared_ptr<Function> clone() const = 0;

protected:
	size_t dimension; ///< The dimension of the function.
	std::string name; ///< The name of the function.
};

class Function1 : public Function
{

public:
	Function1()
	{
		dimension = 2;
		name = "x^2*sin(y)";
	}
	virtual ~Function1() {};
	virtual double operator()(const VectorX &x) const override;
	virtual VectorX grad(const VectorX &x) const override;
	virtual std::shared_ptr<Function> clone() const override;
};

class Function2 : public Function
{
public:
	Function2()
	{
		dimension = 3;
		name = "sin(x)cos(y)sin(z)";
	}
	virtual ~Function2() {};
	virtual double operator()(const VectorX &x) const override;
	virtual VectorX grad(const VectorX &x) const override;
	virtual std::shared_ptr<Function> clone() const override;
};

class Function3 : public Function
{

public:
	Function3()
	{
		dimension = 2;
		name = "(0.1x - y)^4 + y^2";
	}
	virtual ~Function3() {};
	virtual double operator()(const VectorX &x) const override;
	virtual VectorX grad(const VectorX &x) const override;
	virtual std::shared_ptr<Function> clone() const override;
};
