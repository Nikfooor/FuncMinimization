#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

/**
 * \class VectorX
 * \brief A vector class for double values with additional operations.
 *
 * This class extends `std::vector<double>` to include vector arithmetic
 * operations such as addition, subtraction, and scalar multiplication.
 */
class VectorX : public std::vector<double>
{
public:
    using std::vector<double>::vector;

    VectorX &operator+=(const VectorX &other);

    VectorX &operator-=(const VectorX &other);

    VectorX &operator*=(double scalar);

    friend std::ostream &operator<<(std::ostream &os, const VectorX &vec);
};

VectorX operator+(const VectorX &vec1, const VectorX &vec2);

VectorX operator-(const VectorX &vec1, const VectorX &vec2);

VectorX operator*(const VectorX &vec, double scalar);

VectorX operator*(double scalar, const VectorX &vec);

double norm(const VectorX &x);
