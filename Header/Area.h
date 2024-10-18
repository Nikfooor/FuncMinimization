#pragma once
#include "VectorX.h"
#include <stdexcept>
#include <random>
/**
 * \class Area
 * \brief Class representing a multidimensional area defined by bounding intervals.
 *
 * The Area class provides methods for defining a multidimensional space,
 * checking if a point is within this area, generating random points,
 * and calculating intersections between areas.
 */
class Area
{
    friend Area intersect(const Area &area1, const Area &area2); ///< Friend function to calculate the intersection of two areas.

public:
    Area() = default;

    Area(const std::vector<std::pair<double, double>> &bounds);

    ~Area();

    Area(const Area &other);

    Area(Area &&other) noexcept;

    Area &operator=(const Area &other);

    Area &operator=(Area &&other) noexcept;
    /**
     * \brief Get the bounding intervals of the area.
     *
     * \return A vector of pairs representing the bounds of each dimension.
     */
    std::vector<std::pair<double, double>> getBounds() const;
    /**
     * \brief Check if a point is within the area.
     *
     * \param x A vector representing the point to check.
     * \return True if the point is within the area, false otherwise.
     */
    bool inArea(const VectorX &x) const;
    /**
     * \brief Generate a random point within the area.
     *
     * \param x A vector to store the generated point.
     * \param gen A random number generator.
     */
    void genRandPoint(VectorX &x, std::mt19937 gen);
    /**
     * \brief Change the bounds of the area.
     *
     * \param newBounds A vector of pairs representing the new bounds for each dimension.
     */
    void change(const std::vector<std::pair<double, double>> &newBounds);

protected:
    std::vector<std::uniform_real_distribution<>> dis; ///< Distributions for random point generation.
    std::vector<std::pair<double, double>> bounds;     ///< The bounds of the area.
    size_t dimension;                                  ///< The number of dimensions of the area.
    bool isRandInitialized;                            ///< Flag indicating if random distributions are initialized.

private:
    /**
     * \brief Calculate the intersection of two intervals.
     *
     * \param a The first interval.
     * \param b The second interval.
     * \return A pair representing the intersection of the two intervals.
     */
    std::pair<double, double> intersectIntervals(const std::pair<double, double> &a, const std::pair<double, double> &b);
};

/**
 * \brief Computes the intersection of two areas.
 *
 * This function calculates the intersection of two Area objects,
 * returning a new Area that represents the common space.
 *
 * \param area1 The first Area object.
 * \param area2 The second Area object.
 * \return An Area object representing the intersection of area1 and area2.
 */
Area intersect(const Area &area1, const Area &area2);
/**
 * \class Neighborhood
 * \brief Class representing a neighborhood around a point in a multidimensional area.
 *
 * The Neighborhood class inherits from Area and provides additional functionality
 * for defining a neighborhood around a specific point with a given radius (delta).
 */
class Neighborhood : public Area
{
public:
    Neighborhood(double delta, const VectorX &x);
    ~Neighborhood();
    /**
     * \brief Change the neighborhood's delta and center point.
     *
     * This method allows updating the radius and center of the neighborhood.
     *
     * \param new_delta The new radius for the neighborhood.
     * \param x The new center point of the neighborhood as a VectorX.
     */
    void change(double new_delta, const VectorX &x);

private:
    double delta; ///< The radius of the neighborhood.
    VectorX x;    ///< The center point of the neighborhood.
};
