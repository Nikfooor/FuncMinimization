#pragma once
#include "Function.h"
#include "VectorX.h"
#include <memory>

/**
 * \class TransferData
 * \brief Manages data transfer in StopCriteria during optimization processes.
 *
 * This class encapsulates data required for the optimization methods including
 * points, the function being optimized, and the iteration number.
 */
class TransferData
{
public:
    TransferData();
    ~TransferData();

    std::shared_ptr<std::vector<VectorX>> getPoints() const;
    const VectorX &getCurrPoint() const;
    const VectorX &getPrevPoint() const;
    std::shared_ptr<Function> getFunc() const;
    size_t getIterNum();

    void setPoints(const std::vector<VectorX> &points);
    void setFunc(const Function &f);
    void setIterNum(const size_t iter);

private:
    std::shared_ptr<std::vector<VectorX>> points;
    std::shared_ptr<Function> func;
    size_t currIter;
};
