#include "Area.h"

Area::Area(const std::vector<std::pair<double, double>> &bounds) : bounds(bounds), dimension(bounds.size()), isRandInitialized(false)
{
}

Area::~Area() {}

Area::Area(const Area &other) : bounds(other.bounds), dimension(other.dimension), isRandInitialized(false)
{
}

Area::Area(Area &&other) noexcept : bounds(std::move(other.bounds)), dimension(other.dimension), isRandInitialized(false)
{
    other.dimension = 0;
}

Neighborhood::Neighborhood(double delta, const VectorX &x) : delta(delta)
{
    change(delta, x);
}

Neighborhood::~Neighborhood()
{
}

Area &Area::operator=(const Area &other)
{
    if (this == &other)
        return *this;

    bounds = other.bounds;
    dimension = other.dimension;
    isRandInitialized = other.isRandInitialized;
    return *this;
}

Area &Area::operator=(Area &&other) noexcept
{
    if (this == &other)
        return *this;

    bounds = std::move(other.bounds);
    dimension = other.dimension;
    other.dimension = 0;
    isRandInitialized = other.isRandInitialized;
    other.isRandInitialized = false;
    return *this;
}

std::vector<std::pair<double, double>> Area::getBounds() const
{
    return bounds;
}

bool Area::inArea(const VectorX &x) const
{
    if (x.size() != dimension)
    {
        throw std::invalid_argument("Input vector must have exactly 2 elements.");
    }
    for (int i = 0; i < dimension; ++i)
    {
        if (x[i] < bounds[i].first || x[i] > bounds[i].second)
        {
            return false;
        }
    }
    return true;
}

void Area::genRandPoint(VectorX &x, std::mt19937 gen)
{
    if (!isRandInitialized)
    {
        for (int i = 0; i < dimension; ++i)
            dis.push_back(std::uniform_real_distribution<>(bounds[i].first, bounds[i].second));
        isRandInitialized = true;
    }
    for (int i = 0; i < dimension; ++i)
        x[i] = dis[i](gen);
}

void Area::change(const std::vector<std::pair<double, double>> &newBounds)
{
    bounds = newBounds;
    dimension = bounds.size();
    isRandInitialized = false;
}

void Neighborhood::change(double new_delta, const VectorX &x)
{
    std::vector<std::pair<double, double>> b(x.size());
    for (int i = 0; i < x.size(); ++i)
    {
        b[i].first = x[i] - new_delta;
        b[i].second = x[i] + new_delta;
    }
    Area::change(b);
}

std::pair<double, double> intersectIntervals(const std::pair<double, double> &a, const std::pair<double, double> &b)
{
    double left = std::max(a.first, b.first);
    double right = std::min(a.second, b.second);
    if (left < right)
        return {left, right};
    else
        return {0, 0};
}

Area intersect(const Area &area1, const Area &area2)
{
    size_t dim = area1.dimension;
    std::vector<std::pair<double, double>> b(dim);
    for (size_t i = 0; i < dim; ++i)
    {
        b[i] = intersectIntervals(area1.bounds[i], area2.bounds[i]);
        if (b[i].first >= b[i].second)
            return {};
    }
    return Area(b);
}
