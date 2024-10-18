#include "vectorX.h"

VectorX &VectorX::operator+=(const VectorX &other)
{
    if (this->size() != other.size())
        throw std::invalid_argument("Vectors must be of the same size.");

    for (size_t i = 0; i < this->size(); ++i)
        this->at(i) += other[i];

    return *this;
}

VectorX &VectorX::operator-=(const VectorX &other)
{
    if (this->size() != other.size())
        throw std::invalid_argument("Vectors must be of the same size.");

    for (size_t i = 0; i < this->size(); ++i)
        this->at(i) -= other[i];

    return *this;
}

VectorX &VectorX::operator*=(double scalar)
{
    for (size_t i = 0; i < this->size(); ++i)
        this->at(i) *= scalar;

    return *this;
}

std::ostream &operator<<(std::ostream &os, const VectorX &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

VectorX operator+(const VectorX &vec1, const VectorX &vec2)
{
    VectorX result = vec1;
    result += vec2;
    return result;
}

VectorX operator-(const VectorX &vec1, const VectorX &vec2)
{
    VectorX result = vec1;
    result -= vec2;
    return result;
}

VectorX operator*(const VectorX &vec, double scalar)
{
    VectorX result = vec;
    result *= scalar;
    return result;
}

VectorX operator*(double scalar, const VectorX &vec)
{
    return vec * scalar;
}

double norm(const VectorX &x)
{
    double norm = 0;
    for (auto &el : x)
        norm += el * el;
    return sqrt(norm);
}
