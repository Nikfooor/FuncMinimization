#include "TransferData.h"

TransferData::TransferData() : currIter(0), func(nullptr), points(nullptr)
{
}

TransferData::~TransferData()
{
}

const VectorX &TransferData::getCurrPoint() const
{
    return (*points)[points->size() - 1];
}

const VectorX &TransferData::getPrevPoint() const
{
    return (*points)[points->size() - 2];
}

std::shared_ptr<Function> TransferData::getFunc() const
{
    return func;
}

size_t TransferData::getIterNum()
{
    return currIter;
}

std::shared_ptr<std::vector<VectorX>> TransferData::getPoints() const
{
    return points;
}

void TransferData::setPoints(const std::vector<VectorX> &points)
{
    this->points = std::make_shared<std::vector<VectorX>>(points);
}

void TransferData::setFunc(const Function &f)
{
    func = f.clone();
}

void TransferData::setIterNum(const size_t iter)
{
    currIter = iter;
}