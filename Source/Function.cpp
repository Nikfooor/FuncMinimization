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

double Function4::operator()(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 2 elements.");
	}
	return pow(1 - x[0], 2) + 100 * pow(x[1] - x[0] * x[0], 2);
}

VectorX Function4::grad(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 2 elements.");
	}
	VectorX grad(dimension);
	grad[0] = 2 * (200 * pow(x[0], 3) - 200 * x[0] * x[1] + x[0] - 1);
	grad[1] = 200 * (x[1] - pow(x[0], 2));
	return grad;
}

std::shared_ptr<Function> Function4::clone() const
{
	return std::make_shared<Function4>(*this);
}

double Function5::operator()(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 4 elements.");
	}
	return 100 * pow(x[0] * x[0] - x[1], 2) + pow(x[0] - 1, 2) + 100 * pow(x[2] * x[2] - x[3], 2) + pow(x[2] - 1, 2);
}

VectorX Function5::grad(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 4 elements.");
	}
	VectorX grad(dimension);
	grad[0] = 2 * (200 * x[0] * (x[0] * x[0] - x[1]) + x[0] - 1);
	grad[1] = 200 * (x[1] - pow(x[0], 2));
	grad[2] = 2 * (200 * x[2] * (x[2] * x[2] - x[3]) + x[2] - 1);
	grad[3] = 200 * (x[3] - x[2] * x[2]);
	return grad;
}

std::shared_ptr<Function> Function5::clone() const
{
	return std::make_shared<Function5>(*this);
}

double Function6::operator()(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 2 elements.");
	}
	return x[0] * x[0] + x[1] * x[1];
}

VectorX Function6::grad(const VectorX &x) const
{
	if (x.size() != dimension)
	{
		throw std::invalid_argument("Input vector must have exactly 2 elements.");
	}
	VectorX grad(dimension);
	grad[0] = 2 * x[0];
	grad[1] = 2 * x[1];
	return grad;
}

std::shared_ptr<Function> Function6::clone() const
{
	return std::make_shared<Function6>(*this);
}