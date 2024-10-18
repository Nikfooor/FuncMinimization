#include "StopCriteria.h"

StopCriteria::StopCriteria(double eps, size_t max_iter) : eps(eps), max_iter(max_iter)
{
}

StopCriteria::~StopCriteria()
{
}

GradNormStopCriteria::GradNormStopCriteria(double eps, size_t max_iter) : StopCriteria(eps, max_iter)
{
}

GradNormStopCriteria::~GradNormStopCriteria()
{
}

DifferenceNormStopCriteria::DifferenceNormStopCriteria(double eps, size_t max_iter) : StopCriteria(eps, max_iter)
{
}

DifferenceNormStopCriteria::~DifferenceNormStopCriteria()
{
}

FuncDifferenceNormStopCriteria::FuncDifferenceNormStopCriteria(double eps, size_t max_iter) : StopCriteria(eps, max_iter)
{
}

FuncDifferenceNormStopCriteria::~FuncDifferenceNormStopCriteria()
{
}

bool GradNormStopCriteria::check(TransferData &data) const
{
	return data.getIterNum() >= max_iter || norm(data.getFunc()->grad(data.getCurrPoint())) < eps && data.getPoints()->size() != 1;
}

bool DifferenceNormStopCriteria::check(TransferData &data) const
{

	if (data.getPoints()->size() == 1)
		return false;
	return data.getIterNum() >= max_iter || norm(data.getCurrPoint() - data.getPrevPoint()) < eps;
}

bool FuncDifferenceNormStopCriteria::check(TransferData &data) const
{
	if (data.getPoints()->size() == 1)
		return false;
	std::shared_ptr<Function> f = data.getFunc();
	return data.getIterNum() >= max_iter || std::abs(((*f)(data.getCurrPoint()) - (*f)(data.getPrevPoint())) / (*f)(data.getCurrPoint())) < eps;
}
