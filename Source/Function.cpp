#include "Function.h"

double Function1::operator()(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 2 elements.");
	}
	return pow(x[0], 2) * sin(x[1]);
}

VectorX Function1::grad(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 2 elements.");
	}
	VectorX grad(dimension);
	grad[0] = 2 * x[0] * sin(x[1]);
	grad[1] = pow(x[0], 2) * cos(x[1]);
	return grad;
}

std::shared_ptr<Function> Function1::clone() const
{
	return std::make_shared<Function1>(*this);
}

double Function2::operator()(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 3 elements.");
	}
	return sin(x[0]) * cos(x[1]) * sin(x[2]);
}

VectorX Function2::grad(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 3 elements.");
	}
	VectorX grad(dimension);
	grad[0] = cos(x[0]) * cos(x[1]) * sin(x[2]);
	grad[1] = -sin(x[0]) * sin(x[1]) * sin(x[2]);
	grad[1] = sin(x[0]) * cos(x[1]) * cos(x[2]);
	return grad;
}

std::shared_ptr<Function> Function2::clone() const
{
	return std::make_shared<Function2>(*this);
}

double Function3::operator()(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 2 elements.");
	}
	return pow(0.1 * x[0] - x[1], 4) + pow(x[1], 2);
}

VectorX Function3::grad(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 2 elements.");
	}
	VectorX grad(dimension);
	grad[0] = 0.4 * pow(0.1 * x[0] - x[1], 3);
	grad[1] = -4 * pow(0.1 * x[0] - x[1], 3) + 2 * x[1];
	return grad;
}

std::shared_ptr<Function> Function3::clone() const
{
	return std::make_shared<Function3>(*this);
}